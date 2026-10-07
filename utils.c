#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "monopoly.h"

int roll_dice(void)
{
	return rand() % 6 + 1;						// Roll one die (called twice to know if it's a double)
}

/**
 * Read a number typed by the player.
 *
 * If the player types letters, scanf fails and the letters stay in the
 * buffer: we empty the buffer and ask again, otherwise the game loops forever.
 *
 * @return The number typed by the player.
 */
int read_number(void)
{
	int number;
	int result = scanf("%d", &number);

	while (result != 1)
	{
		if (result == EOF)						// No more input (Ctrl+D)
			exit(0);
		int c = getchar();
		while (c != '\n' && c != EOF)			// Empty the buffer
			c = getchar();
		printf("Entrez un nombre : ");
		result = scanf("%d", &number);
	}
	return number;
}

/**
 * Number of characters seen on the screen.
 *
 * strlen counts bytes, but in UTF-8 an accent (é, è...) or a box character
 * (─, █...) takes 2 or 3 bytes. Only the first byte of a character is not
 * of the form 10xxxxxx, so we count only those.
 */
int visible_length(char *text)
{
	int length = 0;

	for (int i = 0; text[i] != '\0'; i++)
	{
		if ((text[i] & 0xC0) != 0x80)
			length++;
	}
	return length;
}

/**
 * Print a text followed by spaces, to take exactly `width` columns.
 * (printf("%-10s") counts the bytes, so it is wrong with accents.)
 */
void print_padded(char *text, int width)
{
	printf("%s", text);
	for (int i = visible_length(text); i < width; i++)
		printf(" ");
}

/**
 * Print a text in the middle of `width` columns.
 */
void print_centered(char *text, int width)
{
	int left = (width - visible_length(text)) / 2;

	for (int i = 0; i < left; i++)
		printf(" ");
	print_padded(text, width - left);
}

void display_menu(void)
{
	printf("\n");
	printf("  " BOLD "1" RESET "  Lancer les dés        " BOLD "2" RESET "  Voir une carte        " BOLD "3" RESET "  Paramètres\n");
	printf("  " BOLD "4" RESET "  Règles du jeu         " BOLD "5" RESET "  Quitter               " BOLD "6" RESET "  Construire une maison\n");
	printf("\n  Votre choix : ");
}




MonopolyCase *create_case(int index, char *name, int price, int rent, int house_price, int rent_1_house, int rent_2_houses, int rent_3_houses, int rent_4_houses, int rent_hotel, int owner_id, int house_count)
{
	MonopolyCase *new_case = (MonopolyCase *)malloc(sizeof(MonopolyCase));	// Create a new MonopolyCase structure.
	new_case->index = index;					// The index of the case on the board.
	new_case->name = name;						// The name of the case.
	new_case->price = price;					// The price of the case.
	new_case->rent = rent;						// The rent of the case.
	new_case->house_price = house_price;		// The price of building houses on the case.
	new_case->rent_1_house = rent_1_house;		// The rent with 1 house.
	new_case->rent_2_houses = rent_2_houses;	// The rent with 2 houses.
	new_case->rent_3_houses = rent_3_houses;	// The rent with 3 houses.
	new_case->rent_4_houses = rent_4_houses;	// The rent with 4 houses.
	new_case->rent_hotel = rent_hotel;			// The rent with a hotel.
	new_case->owner_id = owner_id;				// The ID of the player who owns the case.
	new_case->house_count = house_count;		// The number of houses on the case.

	return new_case;		// Return the newly created MonopolyCase structure.
}

/**
 * Initialize the Monopoly board with 40 cases.
 *
 * This function creates a Monopoly board with 40 cases, each case being a
 * MonopolyCase structure. The name, price and rent of each case come from the
 * real board. A case with a price of 0 cannot be bought (Depart, Chance,
 * taxes, prison...). The rents with houses are a multiple of the rent.
 *
 * @return A pointer to the first element of the board, which is an array of
 *         40 MonopolyCase structures.
 */
MonopolyCase **init_board(void)
{
	MonopolyCase **board = (MonopolyCase **)malloc(40 * sizeof(MonopolyCase *));
	char *names[40] = {
		"Départ", "Boulevard de Belleville", "Caisse de communauté", "Rue Lecourbe", "Impôts sur le revenu",
		"Gare Montparnasse", "Rue de Vaugirard", "Chance", "Rue de Courcelles", "Avenue de la République",
		"Prison / Simple visite", "Boulevard de la Villette", "Compagnie d'électricité", "Avenue de Neuilly", "Rue de Paradis",
		"Gare de Lyon", "Avenue Mozart", "Caisse de communauté", "Boulevard Saint-Michel", "Place Pigalle",
		"Parc Gratuit", "Avenue Matignon", "Chance", "Boulevard Malesherbes", "Avenue Henri-Martin",
		"Gare du Nord", "Faubourg Saint-Honoré", "Place de la Bourse", "Compagnie des eaux", "Rue La Fayette",
		"Allez en prison", "Avenue de Breteuil", "Avenue Foch", "Caisse de communauté", "Boulevard des Capucines",
		"Gare Saint-Lazare", "Chance", "Avenue des Champs-Élysées", "Taxe de luxe", "Rue de la Paix"
	};
	int prices[40] = {
		0, 60, 0, 60, 0, 200, 100, 0, 100, 120,
		0, 140, 150, 140, 160, 200, 180, 0, 180, 200,
		0, 220, 0, 220, 240, 200, 260, 260, 150, 280,
		0, 300, 300, 0, 320, 200, 0, 350, 0, 400
	};
	int rents[40] = {
		0, 2, 0, 4, 0, 25, 6, 0, 6, 8,
		0, 10, 0, 10, 12, 25, 14, 0, 14, 16,
		0, 18, 0, 18, 20, 25, 22, 22, 0, 24,
		0, 26, 26, 0, 28, 25, 0, 35, 0, 50
	};
	// color of each case: 0 = brown ... 7 = dark blue, 8 = company, 9 = station, -1 = other (chance, prison...)
	int groups[40] = {
		-1, 0, -1, 0, -1, 9, 1, -1, 1, 1,
		-1, 2, 8, 2, 2, 9, 3, -1, 3, 3,
		-1, 4, -1, 4, 4, 9, 5, 5, 8, 5,
		-1, 6, 6, -1, 6, 9, -1, 7, -1, 7
	};

	for (int i = 0; i < 40; i++)
	{
		int house_price = 50 * (i / 10 + 1);							// 50, 100, 150 or 200 depending on the side of the board
		int r = rents[i];
		board[i] = create_case(i, names[i], prices[i], r, house_price,
			r * 5, r * 15, r * 30, r * 40, r * 50, -1, 0);				// Create a new case with the given parameters
		board[i]->group = groups[i];
	}
	for (int i = 5; i < 40; i += 10)									// The 4 stations: 25, 50, 100 or 200 with 1 to 4 stations
	{
		board[i]->rent_1_house = 25;
		board[i]->rent_2_houses = 50;
		board[i]->rent_3_houses = 100;
		board[i]->rent_4_houses = 200;
	}

	return board;
}

/**
 * Check if a player owns all the properties of a color.
 *
 * @param board     The Monopoly board.
 * @param player_id The player.
 * @param index     A case of the color to check.
 * @return 1 if the player owns the whole color, 0 otherwise (and always 0 for
 *         the stations and the companies, where you can't build).
 */
int own_color(MonopolyCase **board, int player_id, int index)
{
	int group = board[index]->group;

	if (group < 0 || group > 7)					// station, company, chance... : no houses here
		return 0;
	for (int i = 0; i < 40; i++)
	{
		if (board[i]->group == group && board[i]->owner_id != player_id)
			return 0;
	}
	return 1;
}

/**
 * @brief Clears the terminal to display a cleaner Monopoly game screen.
 *
 * @details Function that clears the terminal by using the "cls" command for
 *          Windows and the "clear" command for Mac and Linux.
 */
void clear_terminal(void)
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}
