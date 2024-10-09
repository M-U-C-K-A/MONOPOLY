#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "monopoly.h"

int roll_dice(void)
{
	return (rand() % 6 + 1) + (rand() % 6 + 1);	// Roll two dice and add the results
}

void format_string(char *str, char *output)
{
	int len = strlen(str);						// Length of the string
	if (len > 24)								// If the string is longer than 24 characters
	{
		strncpy(output, str, 24); 				// Crop to 24 characters
		output[24] = '\0';		  				// Add the string terminator
	}
	else
		sprintf(output, "%-24s", str); 			// Pad to 24 characters
}

void format_price(int price, char *output)
{
	char price_str[30];							// String to store the price
	sprintf(price_str, "$%d", price); 			// Add a dollar sign to the price
	int len = strlen(price_str);				// Length of the string
	if (len > 24)
	{
		strncpy(output, price_str, 24); 		// Crop if necessary
		output[24] = '\0';						// Add the string terminator
	}
	else
		sprintf(output, "%-24s", price_str); 	// Pad to 24 characters
}

void display_menu(void)
{
	printf("\nMenu:\n");						// Display the menu
	printf("1. Roll the dice\n");				// Roll the dice
	printf("2. View cards/colors\n");			// View the cards
	printf("3. Settings\n");					// Settings
	printf("4. Rules\n");						// Rules
	printf("5. Quit the game\n");				// Quit the game
	printf("Choose an option: ");				// Choose an option
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
 * MonopolyCase structure. The name of each case is set to "case X" where X is
 * the index of the case. The price, rent, house price and other properties are
 * set according to the Monopoly rules.
 *
 * @return A pointer to the first element of the board, which is an array of
 *         40 MonopolyCase structures.
 */
MonopolyCase **init_board(void)
{
	MonopolyCase **board = (MonopolyCase **)malloc(40 * sizeof(MonopolyCase *));

	for (int i = 0; i < 40; i++)
	{
		int e = i / 8;													// temporary variable used to set the properties of each case
		board[i] = create_case(i, (char *)malloc(50 * sizeof(char)),
			20 + e * 10, 1 + e, 50 + e * 25, 2 + e * 2, 10 + e * 5, 
			20 + e * 10, 50 + e * 25, 100 + e * 50, -1, 4);				// Create a new case with the given parameters
		sprintf(board[i]->name, "case %d", i);							// Set the name of the case
	}

	return board;
}

/**
 * Return a string representing the houses and/or hotel on a MonopolyCase
 *
 * This function takes a pointer to a MonopolyCase structure and an integer
 * argument line. The line argument is used to determine which part of the
 * string to return. If line is 0, the string will start with the number of
 * houses (up to 4) and end with the number of hotels (0 or 1). If line is 1,
 * the string will only contain the number of hotels (0 or 1). The string
 * will be at most 10 characters long.
 *
 * @param case_ptr Pointer to a MonopolyCase structure
 * @param line     Integer argument to determine which part of the string to
 *                 return. 0 for the houses and 1 for the hotel.
 * @return A constant string representing the houses and/or hotel on a
 *         MonopolyCase.
 */
const char *check_house(MonopolyCase *case_ptr, int line)
{
	static char output[10];			// String to return

	switch (case_ptr->house_count)	// Determine which part of the string to return
	{
	case 0:
		return "  ";
	case 1:
		return line == 0 ? "🏠  " : "";
	case 2:
		return "🏠  ";
	case 3:
		return line == 0 ? "🏠🏠" : "🏠  ";	
	case 4:
		return "🏠🏠";
	case 5:
		return line == 0 ? "🏨  " : "";
	}
	return output;
}

/**
 * Print the Monopoly board with the given board.
 *
 * This function prints the Monopoly board with the given board. The board is
 * an array of 40 MonopolyCase structures. Each case is represented by its
 * name, price, rent, house price, rent with 1, 2, 3 or 4 houses and rent with
 * a hotel. The houses and hotel are represented by " " and " ".
 *
 * @param board The Monopoly board to print.
 */
void show_board(MonopolyCase **board)
{
	printf(" Parc             ║   Avenue     ║    chance    ║  Boulevard   ║    Avenue    ║   Gare du    ║ Faubourg     ║  Place de    ║  Compagnie   ║   Rue la     ║    Allez en     \n");
	printf("Gratuit           ║   Matignon   ║      🍀      ║  Malesherbes ║ Henri-Martin ║   Nord  🚅   ║ Saint-Honoré ║  la bourse   ║   des eaux   ║   fayette    ║    prison       \n");
	printf("══════════════════╬" BG_RED RED "══════════════" RESET "╩══════════════╩" BG_RED RED "══════════════" RESET "╩" BG_RED RED "══════════════" RESET "╩══════════════╩" BG_YELLOW YELLOW "══════════════" RESET "╩" BG_YELLOW YELLOW "══════════════" RESET "╩══════════════╩" BG_YELLOW YELLOW "══════════════" RESET "╬══════════════════   \n");
	printf("place         %-4s" BG_ORANGE ORANGE"║" RESET " \t\t\t                                                                                                   \t\t " BG_GREEN GREEN "║" RESET "%-4s Avenue		\n", check_house(board[19], 1), check_house(board[31], 0));
	printf("Pigalle       %-4s" BG_ORANGE ORANGE"║" RESET " \t\t\t                                                                                                   \t\t " BG_GREEN GREEN "║" RESET "%-4s de breteuil	\n", check_house(board[19], 0), check_house(board[31], 1));
	printf("══════════════════╣ \t\t\t                                                                                                   \t\t ╠══════════════════	\n");
	printf("Boulevard     %-4s" BG_ORANGE ORANGE"║" RESET " \t\t\t                                                                                                   \t\t " BG_GREEN GREEN "║" RESET "%-4s avenue		\n", check_house(board[18], 1), check_house(board[32], 0));
	printf("Saint-Michel  %-4s" BG_ORANGE ORANGE"║" RESET " \t\t\t                                                                                                   \t\t " BG_GREEN GREEN "║" RESET "%-4s Foch			\n", check_house(board[18], 0), check_house(board[32], 1));
	printf("══════════════════╣ \t\t\t                                                                                                   \t\t ╠══════════════════ 	\n");
	printf("caisse de         ║ \t\t\t                                                                                                   \t\t ║     caisse de		\n");
	printf("communauté        ║ \t\t       	 	◘ Achetez. Vendez. Négociez. Gagnez ! ◘		 						 	 ║     communauté	\n");
	printf("══════════════════╣ \t\t\t       __       __   ______   __    __   ______   _______    ______   __    __      __             \t\t ╠══════════════════	\n");
	printf("avenue        %-4s" BG_ORANGE ORANGE"║" RESET " \t\t\t      /  \\     /  | /      \\ /  \\  /  | /      \\ /       \\  /      \\ /  |  /  \\    /  |     \t\t\t " BG_GREEN GREEN "║" RESET "%-4s Boulevard		\n", check_house(board[16], 1), check_house(board[34], 0));
	printf("Mozard        %-4s" BG_ORANGE ORANGE"║" RESET " \t\t\t      $$  \\   /$$ |/$$$$$$  |$$  \\ $$ |/$$$$$$  |$$$$$$$  |/$$$$$$  |$$ |  $$  \\  /$$/          \t\t " BG_GREEN GREEN "║" RESET "%-4s des capucines	\n", check_house(board[16], 0), check_house(board[34], 1));
	printf("══════════════════╣ \t\t\t      $$$  \\ /$$$ |$$ |  $$ |$$$  \\$$ |$$ |  $$ |$$ |__$$ |$$ |  $$ |$$ |   $$  \\/$$/           \t\t ╠══════════════════	\n");
	printf("Gare de           ║ \t\t\t      $$$$  /$$$$ |$$ |  $$ |$$$$  $$ |$$ |  $$ |$$    $$/ $$ |  $$ |$$ |    $$  $$\\              \t\t ║     gare 🚅	\n");
	printf("Lyon 🚅           ║ \t\t\t      $$ $$ $$/$$ |$$ |  $$ |$$ $$ $$ |$$ |  $$ |$$$$$$$/  $$ |  $$ |$$ |     $$$$/                \t\t ║     Saint-Lazare	\n");
	printf("══════════════════╣ \t\t\t      $$ |$$$/ $$ |$$ \\__$$ |$$ |$$$$ |$$ \\__$$ |$$ |      $$ \\__$$ |$$ |_____ $$ |             \t\t ╠══════════════════	\n");
	printf("Rue de        %-4s" BG_BRIGHT_MAGENTA BRIGHT_MAGENTA"║" RESET " \t\t\t      $$ | $/  $$ |$$    $$/ $$ | $$$ |$$    $$/ $$ |      $$    $$/ $$       |$$ |                \t\t ║     chance		\n", check_house(board[14], 1));
	printf("Paradis       %-4s" BG_BRIGHT_MAGENTA BRIGHT_MAGENTA"║" RESET " \t\t\t      $$/      $$/  $$$$$$/  $$/   $$/  $$$$$$/  $$/        $$$$$$/  $$$$$$$$/ $$/                 \t\t ║	 🍀		\n", check_house(board[14], 0));
	printf("══════════════════╣ \t\t\t                                                                                                   \t\t ╠══════════════════	\n");
	printf("Avenue de     %-4s" BG_BRIGHT_MAGENTA BRIGHT_MAGENTA"║" RESET " \t\t\t                                                                                                   \t\t " BG_BLUE BLUE "║" RESET "%-4s Avenue des	\n", check_house(board[13], 1), check_house(board[37], 0));
	printf("Neuilly       %-4s" BG_BRIGHT_MAGENTA BRIGHT_MAGENTA"║" RESET " \t\t\t  " DIM "     _                      _             _            _ _ _   _               _               " RESET "  \t\t " BG_BLUE BLUE "║" RESET "%-4s champs-élysées\n", check_house(board[13], 0), check_house(board[37], 1));
	printf("══════════════════╣ \t\t\t  " DIM "    | |_ ___ _ __ _ __ ___ (_)_ __   __ _| |   ___  __| (_) |_(_) ___  _ __   | |              " RESET "  \t\t ╠══════════════════	\n");
	printf("compagnie         ║ \t\t\t  " DIM "    | __/ _ \\ '__| '_ ` _ \\| | '_ \\ / _` | |  / _ \\/ _` | | __| |/ _ \\| '_ \\  | |        " RESET "  \t\t\t ║     Taxe de   	\n");
	printf("électrique        ║ \t\t\t  " DIM "    | ||  __/ |  | | | | | | | | | | (_| | | |  __/ (_| | | |_| | (_) | | | | |_|              " RESET "  \t\t ║     Luxe 💍    	\n");
	printf("══════════════════╣ \t\t\t  " DIM "     \\__\\___|_|  |_| |_| |_|_|_| |_|\\__,_|_|  \\___|\\__,_|_|\\__|_|\\___/|_| |_| (_)       " RESET "  \t\t\t ╠══════════════════	\n");
	printf("Boulevard de  %-4s" BG_BRIGHT_MAGENTA BRIGHT_MAGENTA"║" RESET " \t\t\t                                                                                                   \t\t " BG_BLUE BLUE "║" RESET "%-4s Rue de    	\n", check_house(board[11], 1), check_house(board[39], 0));
	printf("la villette   %-4s" BG_BRIGHT_MAGENTA BRIGHT_MAGENTA"║" RESET " \t\t\t                                                                                                   \t\t " BG_BLUE BLUE "║" RESET "%-4s la Paix   	\n", check_house(board[11], 0), check_house(board[39], 1));
	printf("══════════════════╬" BG_BRIGHT_CYAN BRIGHT_CYAN "══════════════" RESET "╦" BG_BRIGHT_CYAN BRIGHT_CYAN "══════════════" RESET "╦══════════════╦" BG_BRIGHT_CYAN BRIGHT_CYAN "══════════════" RESET "╦══════════════╦══════════════╦" BG_BROWN BROWN "══════════════" RESET "╦══════════════╦" BG_BROWN BROWN "══════════════" RESET "╬══════════════════ \n");
	printf(" Simple           ║ Avenue de la ║  Rue de      ║    chance    ║ Rue de       ║ Gare  🚅     ║  Impôts sur  ║  Rue         ║  Caisse de   ║ Boulevard de ║     Case         \n");
	printf(" visite           ║ République   ║  Courcelles  ║      🍀      ║ Vaugirard    ║ Montparnasse ║  le revenue  ║  Lecourbe    ║  Communauté  ║ Belleville   ║     Départ       \n");
}

/**
 * @brief Clears the terminal to display a cleaner Monopoly game screen.
 *
 * @details Function that clears the terminal by using the "cls" command for
 *          Windows. Other systems are not supported.
 */
void clear_terminal(void)
{
	system("cls");
}
