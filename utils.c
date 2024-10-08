#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "monopoly.h"

void format_string(char *str, char *output)
{
	int len = strlen(str);
	if (len > 24)
	{
		strncpy(output, str, 24); // Crop à 24 caractères
		output[24] = '\0';		  // Ajouter le terminateur de chaîne
	}
	else
	{
		sprintf(output, "%-24s", str); // Padding jusqu'à 24 caractères
	}
}

// Fonction pour crop ou padd un prix avec un dollar avant
void format_price(int price, char *output)
{
	char price_str[30];
	sprintf(price_str, "$%d", price); // Ajouter le dollar au début du prix
	int len = strlen(price_str);
	if (len > 24)
	{
		strncpy(output, price_str, 24); // Crop si nécessaire
		output[24] = '\0';
	}
	else
	{
		sprintf(output, "%-24s", price_str); // Padding jusqu'à 24 caractères
	}
}

// Fonction d'affichage formatée d'une case du plateau
void show_card(MonopolyCase **board, int index)
{
	if (board[index] != NULL)
	{
		char formatted_name[25]; // 24 caractères + terminateur de chaîne
		char formatted_price[25];
		char formatted_rent[25];

		// Formater les chaînes
		format_string(board[index]->name, formatted_name);
		format_price(board[index]->price, formatted_price);
		format_price(board[index]->rent, formatted_rent);

		// Affichage formaté
		printf(DIM "╔══════════════════════════╗\n");
		printf("║" RESET " %-24s " DIM "║\n", formatted_name); // Nom du terrain
		printf("╠══════════════════════════╣\n");
		printf("║" RESET "           $%-13d " DIM "║\n", board[index]->price);				  // Prix du terrain
		printf("║" RESET " Rent: . . . . . . $%-5d " DIM "║\n", board[index]->rent);		  // Loyer standard
		printf("║" RESET " Rent with 🏠 x1:  $%-5d " DIM "║\n", board[index]->rent_1_house);  // Loyer 1 maison
		printf("║" RESET " Rent with 🏠 x2:  $%-5d " DIM "║\n", board[index]->rent_2_houses); // Loyer 2 maisons
		printf("║" RESET " Rent with 🏠 x3:  $%-5d " DIM "║\n", board[index]->rent_3_houses); // Loyer 3 maisons
		printf("║" RESET " Rent with 🏠 x4:  $%-5d " DIM "║\n", board[index]->rent_4_houses); // Loyer 4 maisons
		printf("║" RESET " Rent with 🏨   :  $%-5d " DIM "║\n", board[index]->rent_hotel);	  // Loyer avec hôtel
		printf("╠══════════════════════════╣\n");
		printf("║" RESET " House price:      $%-5d " DIM "║\n", board[index]->house_price);							   // Prix d'une maison
		printf("║" RESET " Hotel price:🏠x4+ $%-5d " DIM "║\n", board[index]->house_price, board[index]->house_price); // Prix d'un hôtel
		printf("╚══════════════════════════╝\n\n" RESET);
	}
	else
	{
		printf("No card exists at this position.\n");
	}
}

void show_color_card(MonopolyCase **board, int index)
{
	if (board[index] != NULL)
	{
		int card_list[][4] = {
			{1, 3},
			{6, 8, 9},
			{11, 13, 14},
			{16, 18, 19},
			{21, 23, 24},
			{26, 27, 29},
			{31, 32, 34},
			{37, 39},
			{12, 28},
			{5, 15, 25, 35}};
		switch (index)
		{
		case 0:// Brown Property
			printf(BROWN DIM "╔══════════════════════════╗\n");
			printf("║" RESET BROWN BOLD "  Brown Property          " DIM "║\n");
			printf("╚══════════════════════════╝\n\n" RESET BROWN);

			printf(DIM "╔══════════════════════════╗\t╔══════════════════════════╗\n");
			printf("║" RESET BROWN" %-24s " DIM "║\t║" RESET BROWN" %-24s " DIM "║\n", 										board[card_list[0][0]]->name, 			board[card_list[0][1]]->name);
			printf("╠══════════════════════════╣\t╠══════════════════════════╣\n");
			printf("║" RESET BROWN"           $%-13d " DIM "║\t║" RESET BROWN"           $%-13d " DIM "║\n", 				board[card_list[0][0]]->price, 			board[card_list[0][1]]->price);
			printf("║" RESET BROWN" Rent: . . . . . . $%-5d " DIM "║\t║" RESET BROWN" Rent: . . . . . . $%-5d " DIM "║\n",	board[card_list[0][0]]->rent, 			board[card_list[0][1]]->rent);
			printf("║" RESET BROWN" Rent with 🏠 x1:  $%-5d " DIM "║\t║" RESET BROWN" Rent with 🏠 x1:  $%-5d " DIM "║\n", board[card_list[0][0]]->rent_1_house, 	board[card_list[0][1]]->rent_1_house);
			printf("║" RESET BROWN" Rent with 🏠 x2:  $%-5d " DIM "║\t║" RESET BROWN" Rent with 🏠 x2:  $%-5d " DIM "║\n", board[card_list[0][0]]->rent_2_houses, 	board[card_list[0][1]]->rent_2_houses);
			printf("║" RESET BROWN" Rent with 🏠 x3:  $%-5d " DIM "║\t║" RESET BROWN" Rent with 🏠 x3:  $%-5d " DIM "║\n", board[card_list[0][0]]->rent_3_houses, 	board[card_list[0][1]]->rent_3_houses);
			printf("║" RESET BROWN" Rent with 🏠 x4:  $%-5d " DIM "║\t║" RESET BROWN" Rent with 🏠 x4:  $%-5d " DIM "║\n", board[card_list[0][0]]->rent_4_houses, 	board[card_list[0][1]]->rent_4_houses);
			printf("║" RESET BROWN" Rent with 🏨   :  $%-5d " DIM "║\t║" RESET BROWN" Rent with 🏨   :  $%-5d " DIM "║\n", board[card_list[0][0]]->rent_hotel, 		board[card_list[0][1]]->rent_hotel);
			printf("╠══════════════════════════╣\t╠══════════════════════════╣\n");
			printf("║" RESET BROWN" House price:      $%-5d " DIM "║\t║" RESET BROWN" House price:      $%-5d " DIM "║\n", board[card_list[0][0]]->house_price, 	board[card_list[0][1]]->house_price);
			printf("║" RESET BROWN" Hotel price:🏠x4+ $%-5d " DIM "║\t║" RESET BROWN" Hotel price:🏠x4+ $%-5d " DIM "║\n", board[card_list[0][0]]->house_price, 	board[card_list[0][1]]->house_price);
			printf("╚══════════════════════════╝\t╚══════════════════════════╝\n\n" RESET);
			break;
		case 1:// Bright Blue Property
			printf(BRIGHT_CYAN DIM "╔══════════════════════════╗\n");
			printf("║" RESET BRIGHT_CYAN BOLD "  Bright Blue Property    " DIM "║\n");
			printf("╚══════════════════════════╝\n\n" RESET BRIGHT_CYAN);

			printf(DIM "╔══════════════════════════╗\t╔══════════════════════════╗\t╔══════════════════════════╗\n");
			printf("║" RESET BRIGHT_CYAN" %-24s " DIM "║\t║" RESET BRIGHT_CYAN" %-24s " DIM "║\t║" RESET BRIGHT_CYAN" %-24s " DIM "║\n", 														board[card_list[1][0]]->name, 			board[card_list[1][1]]->name,			board[card_list[1][2]]->name);
			printf("╠══════════════════════════╣\t╠══════════════════════════╣\t╠══════════════════════════╣\n");
			printf("║" RESET BRIGHT_CYAN"           $%-13d " DIM "║\t║" RESET BRIGHT_CYAN"           $%-13d " DIM "║\t║" RESET BRIGHT_CYAN"           $%-13d " DIM "║\n", 						board[card_list[1][0]]->price, 			board[card_list[1][1]]->price,			board[card_list[1][2]]->price);
			printf("║" RESET BRIGHT_CYAN" Rent: . . . . . . $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent: . . . . . . $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent: . . . . . . $%-5d " DIM "║\n",	board[card_list[1][0]]->rent, 			board[card_list[1][1]]->rent,			board[card_list[1][2]]->rent);
			printf("║" RESET BRIGHT_CYAN" Rent with 🏠 x1:  $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent with 🏠 x1:  $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent: . . . . . . $%-5d " DIM "║\n", 	board[card_list[1][0]]->rent_1_house, 	board[card_list[1][1]]->rent_1_house,	board[card_list[1][2]]->rent_1_house);
			printf("║" RESET BRIGHT_CYAN" Rent with 🏠 x2:  $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent with 🏠 x2:  $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent: . . . . . . $%-5d " DIM "║\n", 	board[card_list[1][0]]->rent_2_houses, 	board[card_list[1][1]]->rent_2_houses,	board[card_list[1][2]]->rent_2_houses);
			printf("║" RESET BRIGHT_CYAN" Rent with 🏠 x3:  $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent with 🏠 x3:  $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent: . . . . . . $%-5d " DIM "║\n", 	board[card_list[1][0]]->rent_3_houses, 	board[card_list[1][1]]->rent_3_houses,	board[card_list[1][2]]->rent_3_houses);
			printf("║" RESET BRIGHT_CYAN" Rent with 🏠 x4:  $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent with 🏠 x4:  $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent: . . . . . . $%-5d " DIM "║\n", 	board[card_list[1][0]]->rent_4_houses, 	board[card_list[1][1]]->rent_4_houses,	board[card_list[1][2]]->rent_4_houses);
			printf("║" RESET BRIGHT_CYAN" Rent with 🏨   :  $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent with 🏨   :  $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent: . . . . . . $%-5d " DIM "║\n", 	board[card_list[1][0]]->rent_hotel, 	board[card_list[1][1]]->rent_hotel,		board[card_list[1][2]]->rent_hotel);
			printf("╠══════════════════════════╣\t╠══════════════════════════╣\t╠══════════════════════════╣\n");
			printf("║" RESET BRIGHT_CYAN" House price:      $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" House price:      $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" House price:      $%-5d " DIM "║\n", 	board[card_list[1][0]]->house_price, 	board[card_list[1][1]]->house_price,	board[card_list[1][2]]->house_price);
			printf("║" RESET BRIGHT_CYAN" Hotel price:🏠x4+ $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Hotel price:🏠x4+ $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Hotel price:🏠x4+ $%-5d " DIM "║\n", 	board[card_list[1][0]]->house_price, 	board[card_list[1][1]]->house_price,	board[card_list[1][2]]->house_price);
			printf("╚══════════════════════════╝\t╚══════════════════════════╝\t╚══════════════════════════╝\n\n" RESET);
			break;
		case 2:// Magenta Property
		    printf(MAGENTA DIM "╔══════════════════════════╗\n");
		    printf("║" RESET MAGENTA BOLD "  Magenta Property          " DIM "║\n");
		    printf("╚══════════════════════════╝\n\n" RESET MAGENTA);

		    printf(DIM "╔══════════════════════════╗\t╔══════════════════════════╗\t╔══════════════════════════╗\n");
		    printf("║" RESET MAGENTA" %-24s " DIM "║\t║" RESET MAGENTA" %-24s " DIM "║\t║" RESET MAGENTA" %-24s " DIM "║\n", board[card_list[2][0]]->name, board[card_list[2][1]]->name, board[card_list[2][2]]->name);
		    printf("╠══════════════════════════╣\t╠══════════════════════════╣\t╠══════════════════════════╣\n");
		    printf("║" RESET MAGENTA"           $%-13d " DIM "║\t║" RESET MAGENTA"           $%-13d " DIM "║\t║" RESET MAGENTA"           $%-13d " DIM "║\n", board[card_list[2][0]]->price, board[card_list[2][1]]->price, board[card_list[2][2]]->price);
		    printf("║" RESET MAGENTA" Rent: . . . . . . $%-5d " DIM "║\t║" RESET MAGENTA" Rent: . . . . . . $%-5d " DIM "║\t║" RESET MAGENTA" Rent: . . . . . . $%-5d " DIM "║\n",  board[card_list[2][0]]->rent, board[card_list[2][1]]->rent, board[card_list[2][2]]->rent);
		    printf("║" RESET MAGENTA" Rent with 🏠 x1:  $%-5d " DIM "║\t║" RESET MAGENTA" Rent with 🏠 x1:  $%-5d " DIM "║\t║" RESET MAGENTA" Rent with 🏠 x1:  $%-5d " DIM "║\n", board[card_list[2][0]]->rent_1_house, board[card_list[2][1]]->rent_1_house, board[card_list[2][2]]->rent_1_house);
		    printf("║" RESET MAGENTA" Rent with 🏠 x2:  $%-5d " DIM "║\t║" RESET MAGENTA" Rent with 🏠 x2:  $%-5d " DIM "║\t║" RESET MAGENTA" Rent with 🏠 x2:  $%-5d " DIM "║\n", board[card_list[2][0]]->rent_2_houses, board[card_list[2][1]]->rent_2_houses, board[card_list[2][2]]->rent_2_houses);
		    printf("║" RESET MAGENTA" Rent with 🏠 x3:  $%-5d " DIM "║\t║" RESET MAGENTA" Rent with 🏠 x3:  $%-5d " DIM "║\t║" RESET MAGENTA" Rent with 🏠 x3:  $%-5d " DIM "║\n", board[card_list[2][0]]->rent_3_houses, board[card_list[2][1]]->rent_3_houses, board[card_list[2][2]]->rent_3_houses);
		    printf("║" RESET MAGENTA" Rent with 🏠 x4:  $%-5d " DIM "║\t║" RESET MAGENTA" Rent with 🏠 x4:  $%-5d " DIM "║\t║" RESET MAGENTA" Rent with 🏠 x4:  $%-5d " DIM "║\n", board[card_list[2][0]]->rent_4_houses, board[card_list[2][1]]->rent_4_houses, board[card_list[2][2]]->rent_4_houses);
		    printf("║" RESET MAGENTA" Rent with 🏨   :  $%-5d " DIM "║\t║" RESET MAGENTA" Rent with 🏨   :  $%-5d " DIM "║\t║" RESET MAGENTA" Rent with 🏨   :  $%-5d " DIM "║\n", board[card_list[2][0]]->rent_hotel, board[card_list[2][1]]->rent_hotel, board[card_list[2][2]]->rent_hotel);
		    printf("╠══════════════════════════╣\t╠══════════════════════════╣\t╠══════════════════════════╣\n");
		    printf("║" RESET MAGENTA" House price:      $%-5d " DIM "║\t║" RESET MAGENTA" House price:      $%-5d " DIM "║\t║" RESET MAGENTA" House price:      $%-5d " DIM "║\n", board[card_list[2][0]]->house_price, board[card_list[2][1]]->house_price, board[card_list[2][2]]->house_price);
		    printf("║" RESET MAGENTA" Hotel price:🏠x4+ $%-5d " DIM "║\t║" RESET MAGENTA" Hotel price:🏠x4+ $%-5d " DIM "║\t║" RESET MAGENTA" Hotel price:🏠x4+ $%-5d " DIM "║\n", board[card_list[2][0]]->house_price, board[card_list[2][1]]->house_price, board[card_list[2][2]]->house_price);
		    printf("╚══════════════════════════╝\t╚══════════════════════════╝\t╚══════════════════════════╝\n\n" RESET);
		    break;
		case 3:// Orange Property
		    printf(ORANGE DIM "╔══════════════════════════╗\n");
		    printf("║" RESET ORANGE BOLD "  Orange Property         " DIM "║\n");
		    printf("╚══════════════════════════╝\n\n" RESET ORANGE);
		
		    printf(DIM "╔══════════════════════════╗\t╔══════════════════════════╗\t╔══════════════════════════╗\n");
		    printf("║" RESET ORANGE" %-24s " DIM "║\t║" RESET ORANGE" %-24s " DIM "║\t║" RESET ORANGE" %-24s " DIM "║\n", board[card_list[3][0]]->name, board[card_list[3][1]]->name, board[card_list[3][2]]->name);
		    printf("╠══════════════════════════╣\t╠══════════════════════════╣\t╠══════════════════════════╣\n");
		    printf("║" RESET ORANGE"           $%-13d " DIM "║\t║" RESET ORANGE"           $%-13d " DIM "║\t║" RESET ORANGE"           $%-13d " DIM "║\n", board[card_list[3][0]]->price, board[card_list[3][1]]->price, board[card_list[3][2]]->price);
		    printf("║" RESET ORANGE" Rent: . . . . . . $%-5d " DIM "║\t║" RESET ORANGE" Rent: . . . . . . $%-5d " DIM "║\t║" RESET ORANGE" Rent: . . . . . . $%-5d " DIM "║\n", board[card_list[3][0]]->rent, board[card_list[3][1]]->rent, board[card_list[3][2]]->rent);
		    printf("║" RESET ORANGE" Rent with 🏠 x1:  $%-5d " DIM "║\t║" RESET ORANGE" Rent with 🏠 x1:  $%-5d " DIM "║\t║" RESET ORANGE" Rent with 🏠 x1:  $%-5d " DIM "║\n", board[card_list[3][0]]->rent_1_house, board[card_list[3][1]]->rent_1_house, board[card_list[3][2]]->rent_1_house);
		    printf("║" RESET ORANGE" Rent with 🏠 x2:  $%-5d " DIM "║\t║" RESET ORANGE" Rent with 🏠 x2:  $%-5d " DIM "║\t║" RESET ORANGE" Rent with 🏠 x2:  $%-5d " DIM "║\n", board[card_list[3][0]]->rent_2_houses, board[card_list[3][1]]->rent_2_houses, board[card_list[3][2]]->rent_2_houses);
		    printf("║" RESET ORANGE" Rent with 🏠 x3:  $%-5d " DIM "║\t║" RESET ORANGE" Rent with 🏠 x3:  $%-5d " DIM "║\t║" RESET ORANGE" Rent with 🏠 x3:  $%-5d " DIM "║\n", board[card_list[3][0]]->rent_3_houses, board[card_list[3][1]]->rent_3_houses, board[card_list[3][2]]->rent_3_houses);
		    printf("║" RESET ORANGE" Rent with 🏠 x4:  $%-5d " DIM "║\t║" RESET ORANGE" Rent with 🏠 x4:  $%-5d " DIM "║\t║" RESET ORANGE" Rent with 🏠 x4:  $%-5d " DIM "║\n", board[card_list[3][0]]->rent_4_houses, board[card_list[3][1]]->rent_4_houses, board[card_list[3][2]]->rent_4_houses);
		    printf("║" RESET ORANGE" Rent with 🏨   :  $%-5d " DIM "║\t║" RESET ORANGE" Rent with 🏨   :  $%-5d " DIM "║\t║" RESET ORANGE" Rent with 🏨   :  $%-5d " DIM "║\n", board[card_list[3][0]]->rent_hotel, board[card_list[3][1]]->rent_hotel, board[card_list[3][2]]->rent_hotel);
		    printf("╠══════════════════════════╣\t╠══════════════════════════╣\t╠══════════════════════════╣\n");
		    printf("║" RESET ORANGE" House price:      $%-5d " DIM "║\t║" RESET ORANGE" House price:      $%-5d " DIM "║\t║" RESET ORANGE" House price:      $%-5d " DIM "║\n", board[card_list[3][0]]->house_price, board[card_list[3][1]]->house_price, board[card_list[3][2]]->house_price);
		    printf("║" RESET ORANGE" Hotel price:🏠x4+ $%-5d " DIM "║\t║" RESET ORANGE" Hotel price:🏠x4+ $%-5d " DIM "║\t║" RESET ORANGE" Hotel price:🏠x4+ $%-5d " DIM "║\n", board[card_list[3][0]]->house_price, board[card_list[3][1]]->house_price, board[card_list[3][2]]->house_price);
		    printf("╚══════════════════════════╝\t╚══════════════════════════╝\t╚══════════════════════════╝\n\n" RESET);
			break;
		case 4:// Red Property
		    printf(RED DIM "╔══════════════════════════╗\n");
		    printf("║" RESET RED BOLD "  Red Property         " DIM "║\n");
		    printf("╚══════════════════════════╝\n\n" RESET RED);
		
		    printf(DIM "╔══════════════════════════╗\t╔══════════════════════════╗\t╔══════════════════════════╗\n");
		    printf("║" RESET RED" %-24s " DIM "║\t║" RESET RED" %-24s " DIM "║\t║" RESET RED" %-24s " DIM "║\n", board[card_list[4][0]]->name, board[card_list[4][1]]->name, board[card_list[4][2]]->name);
		    printf("╠══════════════════════════╣\t╠══════════════════════════╣\t╠══════════════════════════╣\n");
		    printf("║" RESET RED"           $%-13d " DIM "║\t║" RESET RED"           $%-13d " DIM "║\t║" RESET RED"           $%-13d " DIM "║\n", board[card_list[4][0]]->price, board[card_list[4][1]]->price, board[card_list[4][2]]->price);
		    printf("║" RESET RED" Rent: . . . . . . $%-5d " DIM "║\t║" RESET RED" Rent: . . . . . . $%-5d " DIM "║\t║" RESET RED" Rent: . . . . . . $%-5d " DIM "║\n", board[card_list[4][0]]->rent, board[card_list[4][1]]->rent, board[card_list[4][2]]->rent);
		    printf("║" RESET RED" Rent with x1:  $%-5d " DIM "║\t║" RESET RED" Rent with x1:  $%-5d " DIM "║\t║" RESET RED" Rent with x1:  $%-5d " DIM "║\n", board[card_list[4][0]]->rent_1_house, board[card_list[4][1]]->rent_1_house, board[card_list[4][2]]->rent_1_house);
		    printf("║" RESET RED" Rent with x2:  $%-5d " DIM "║\t║" RESET RED" Rent with x2:  $%-5d " DIM "║\t║" RESET RED" Rent with x2:  $%-5d " DIM "║\n", board[card_list[4][0]]->rent_2_houses, board[card_list[4][1]]->rent_2_houses, board[card_list[4][2]]->rent_2_houses);
		    printf("║" RESET RED" Rent with x3:  $%-5d " DIM "║\t║" RESET RED" Rent with x3:  $%-5d " DIM "║\t║" RESET RED" Rent with x3:  $%-5d " DIM "║\n", board[card_list[4][0]]->rent_3_houses, board[card_list[4][1]]->rent_3_houses, board[card_list[4][2]]->rent_3_houses);
		    printf("║" RESET RED" Rent with x4:  $%-5d " DIM "║\t║" RESET RED" Rent with x4:  $%-5d " DIM "║\t║" RESET RED" Rent with x4:  $%-5d " DIM "║\n", board[card_list[4][0]]->rent_4_houses, board[card_list[4][1]]->rent_4_houses, board[card_list[4][2]]->rent_4_houses);
		    printf("║" RESET RED" Rent with   :  $%-5d " DIM "║\t║" RESET RED" Rent with   :  $%-5d " DIM "║\t║" RESET RED" Rent with   :  $%-5d " DIM "║\n", board[card_list[4][0]]->rent_hotel, board[card_list[4][1]]->rent_hotel, board[card_list[4][2]]->rent_hotel);
		    printf("╠══════════════════════════╣\t╠══════════════════════════╣\t╠══════════════════════════╣\n");
		    printf("║" RESET RED" House price:      $%-5d " DIM "║\t║" RESET RED" House price:      $%-5d " DIM "║\t║" RESET RED" House price:      $%-5d " DIM "║\n", board[card_list[4][0]]->house_price, board[card_list[4][1]]->house_price, board[card_list[4][2]]->house_price);
		    printf("║" RESET RED" Hotel price: x4+ $%-5d " DIM "║\t║" RESET RED" Hotel price: x4+ $%-5d " DIM "║\t║" RESET RED" Hotel price: x4+ $%-5d " DIM "║\n", board[card_list[4][0]]->house_price, board[card_list[4][1]]->house_price, board[card_list[4][2]]->house_price);
		    printf("╚══════════════════════════╝\t╚══════════════════════════╝\t╚══════════════════════════╝\n\n" RESET);
			break;
		case 5:// Yellow Property
		    printf(YELLOW DIM "╔══════════════════════════╗\n");
		    printf("║" RESET YELLOW BOLD "  Yellow Property         " DIM "║\n");
		    printf("╚══════════════════════════╝\n\n" RESET YELLOW);
		
		    printf(DIM "╔══════════════════════════╗\t╔══════════════════════════╗\t╔══════════════════════════╗\n");
		    printf("║" RESET YELLOW" %-24s " DIM "║\t║" RESET YELLOW" %-24s " DIM "║\t║" RESET YELLOW" %-24s " DIM "║\n", board[card_list[5][0]]->name, board[card_list[5][1]]->name, board[card_list[5][2]]->name);
		    printf("╠══════════════════════════╣\t╠══════════════════════════╣\t╠══════════════════════════╣\n");
		    printf("║" RESET YELLOW"           $%-13d " DIM "║\t║" RESET YELLOW"           $%-13d " DIM "║\t║" RESET YELLOW"           $%-13d " DIM "║\n", board[card_list[5][0]]->price, board[card_list[5][1]]->price, board[card_list[5][2]]->price);
		    printf("║" RESET YELLOW" Rent: . . . . . . $%-5d " DIM "║\t║" RESET YELLOW" Rent: . . . . . . $%-5d " DIM "║\t║" RESET YELLOW" Rent: . . . . . . $%-5d " DIM "║\n", board[card_list[5][0]]->rent, board[card_list[5][1]]->rent, board[card_list[5][2]]->rent);
		    printf("║" RESET YELLOW" Rent with 🏠 x1:  $%-5d " DIM "║\t║" RESET YELLOW" Rent with 🏠 x1:  $%-5d " DIM "║\t║" RESET YELLOW" Rent with 🏠 x1:  $%-5d " DIM "║\n", board[card_list[5][0]]->rent_1_house, board[card_list[5][1]]->rent_1_house, board[card_list[5][2]]->rent_1_house);
		    printf("║" RESET YELLOW" Rent with 🏠 x2:  $%-5d " DIM "║\t║" RESET YELLOW" Rent with 🏠 x2:  $%-5d " DIM "║\t║" RESET YELLOW" Rent with 🏠 x2:  $%-5d " DIM "║\n", board[card_list[5][0]]->rent_2_houses, board[card_list[5][1]]->rent_2_houses, board[card_list[5][2]]->rent_2_houses);
		    printf("║" RESET YELLOW" Rent with 🏠 x3:  $%-5d " DIM "║\t║" RESET YELLOW" Rent with 🏠 x3:  $%-5d " DIM "║\t║" RESET YELLOW" Rent with 🏠 x3:  $%-5d " DIM "║\n", board[card_list[5][0]]->rent_3_houses, board[card_list[5][1]]->rent_3_houses, board[card_list[5][2]]->rent_3_houses);
		    printf("║" RESET YELLOW" Rent with 🏠 x4:  $%-5d " DIM "║\t║" RESET YELLOW" Rent with 🏠 x4:  $%-5d " DIM "║\t║" RESET YELLOW" Rent with 🏠 x4:  $%-5d " DIM "║\n", board[card_list[5][0]]->rent_4_houses, board[card_list[5][1]]->rent_4_houses, board[card_list[5][2]]->rent_4_houses);
		    printf("║" RESET YELLOW" Rent with 🏨   :  $%-5d " DIM "║\t║" RESET YELLOW" Rent with 🏨   :  $%-5d " DIM "║\t║" RESET YELLOW" Rent with 🏨   :  $%-5d " DIM "║\n", board[card_list[5][0]]->rent_hotel, board[card_list[5][1]]->rent_hotel, board[card_list[5][2]]->rent_hotel);
		    printf("╠══════════════════════════╣\t╠══════════════════════════╣\t╠══════════════════════════╣\n");
		    printf("║" RESET YELLOW" House price:      $%-5d " DIM "║\t║" RESET YELLOW" House price:      $%-5d " DIM "║\t║" RESET YELLOW" House price:      $%-5d " DIM "║\n", board[card_list[5][0]]->house_price, board[card_list[5][1]]->house_price, board[card_list[5][2]]->house_price);
		    printf("║" RESET YELLOW" Hotel price:🏠x4+ $%-5d " DIM "║\t║" RESET YELLOW" Hotel price:🏠x4+ $%-5d " DIM "║\t║" RESET YELLOW" Hotel price:🏠x4+ $%-5d " DIM "║\n", board[card_list[5][0]]->house_price, board[card_list[5][1]]->house_price, board[card_list[5][2]]->house_price);
		    printf("╚══════════════════════════╝\t╚══════════════════════════╝\t╚══════════════════════════╝\n\n" RESET);
			break;
		case 6: // Green Property
		    printf(GREEN DIM "╔══════════════════════════╗\n");
		    printf("║" RESET GREEN BOLD "  Green Property         " DIM "║\n");
		    printf("╚══════════════════════════╝\n\n" RESET GREEN);
		
		    printf(DIM "╔══════════════════════════╗\t╔══════════════════════════╗\t╔══════════════════════════╗\n");
		    printf("║" RESET GREEN" %-24s " DIM "║\t║" RESET GREEN" %-24s " DIM "║\t║" RESET GREEN" %-24s " DIM "║\n", board[card_list[6][0]]->name, board[card_list[6][1]]->name, board[card_list[6][2]]->name);
		    printf("╠══════════════════════════╣\t╠══════════════════════════╣\t╠══════════════════════════╣\n");
		    printf("║" RESET GREEN"           $%-13d " DIM "║\t║" RESET GREEN"           $%-13d " DIM "║\t║" RESET GREEN"           $%-13d " DIM "║\n", board[card_list[6][0]]->price, board[card_list[6][1]]->price, board[card_list[6][2]]->price);
		    printf("║" RESET GREEN" Rent: . . . . . . $%-5d " DIM "║\t║" RESET GREEN" Rent: . . . . . . $%-5d " DIM "║\t║" RESET GREEN" Rent: . . . . . . $%-5d " DIM "║\n", board[card_list[6][0]]->rent, board[card_list[6][1]]->rent, board[card_list[6][2]]->rent);
		    printf("║" RESET GREEN" Rent with 🏠 x1:  $%-5d " DIM "║\t║" RESET GREEN" Rent with 🏠 x1:  $%-5d " DIM "║\t║" RESET GREEN" Rent with 🏠 x1:  $%-5d " DIM "║\n", board[card_list[6][0]]->rent_1_house, board[card_list[6][1]]->rent_1_house, board[card_list[6][2]]->rent_1_house);
		    printf("║" RESET GREEN" Rent with 🏠 x2:  $%-5d " DIM "║\t║" RESET GREEN" Rent with 🏠 x2:  $%-5d " DIM "║\t║" RESET GREEN" Rent with 🏠 x2:  $%-5d " DIM "║\n", board[card_list[6][0]]->rent_2_houses, board[card_list[6][1]]->rent_2_houses, board[card_list[6][2]]->rent_2_houses);
		    printf("║" RESET GREEN" Rent with 🏠 x3:  $%-5d " DIM "║\t║" RESET GREEN" Rent with 🏠 x3:  $%-5d " DIM "║\t║" RESET GREEN" Rent with 🏠 x3:  $%-5d " DIM "║\n", board[card_list[6][0]]->rent_3_houses, board[card_list[6][1]]->rent_3_houses, board[card_list[6][2]]->rent_3_houses);
		    printf("║" RESET GREEN" Rent with 🏠 x4:  $%-5d " DIM "║\t║" RESET GREEN" Rent with 🏠 x4:  $%-5d " DIM "║\t║" RESET GREEN" Rent with 🏠 x4:  $%-5d " DIM "║\n", board[card_list[6][0]]->rent_4_houses, board[card_list[6][1]]->rent_4_houses, board[card_list[6][2]]->rent_4_houses);
		    printf("║" RESET GREEN" Rent with 🏨   :  $%-5d " DIM "║\t║" RESET GREEN" Rent with 🏨   :  $%-5d " DIM "║\t║" RESET GREEN" Rent with 🏨   :  $%-5d " DIM "║\n", board[card_list[6][0]]->rent_hotel, board[card_list[6][1]]->rent_hotel, board[card_list[6][2]]->rent_hotel);
		    printf("╠══════════════════════════╣\t╠══════════════════════════╣\t╠══════════════════════════╣\n");
		    printf("║" RESET GREEN" House price:      $%-5d " DIM "║\t║" RESET GREEN" House price:      $%-5d " DIM "║\t║" RESET GREEN" House price:      $%-5d " DIM "║\n", board[card_list[6][0]]->house_price, board[card_list[6][1]]->house_price, board[card_list[6][2]]->house_price);
		    printf("║" RESET GREEN" Hotel price:🏠x4+ $%-5d " DIM "║\t║" RESET GREEN" Hotel price:🏠x4+ $%-5d " DIM "║\t║" RESET GREEN" Hotel price:🏠x4+ $%-5d " DIM "║\n", board[card_list[6][0]]->house_price, board[card_list[6][1]]->house_price, board[card_list[6][2]]->house_price);
		    printf("╚══════════════════════════╝\t╚══════════════════════════╝\t╚══════════════════════════╝\n\n" RESET);
			break;		
		case 7:// Blue Property
			printf(BLUE DIM "╔══════════════════════════╗\n");
			printf("║" RESET BLUE BOLD "  Blue Property                 " DIM "║\n");
			printf("╚══════════════════════════╝\n\n" RESET BLUE);

			printf(DIM "╔══════════════════════════╗\t╔══════════════════════════╗\n");
			printf("║" RESET BLUE" %-24s " DIM "║\t║" RESET BLUE" %-24s " DIM "║\n", 										board[card_list[7][0]]->name, 			board[card_list[7][1]]->name);
			printf("╠══════════════════════════╣\t╠══════════════════════════╣\n");
			printf("║" RESET BLUE"           $%-13d " DIM "║\t║" RESET BLUE"           $%-13d " DIM "║\n", 				board[card_list[7][0]]->price, 			board[card_list[7][1]]->price);
			printf("║" RESET BLUE" Rent: . . . . . . $%-5d " DIM "║\t║" RESET BLUE" Rent: . . . . . . $%-5d " DIM "║\n",	board[card_list[7][0]]->rent, 			board[card_list[7][1]]->rent);
			printf("║" RESET BLUE" Rent with 🏠 x1:  $%-5d " DIM "║\t║" RESET BLUE" Rent with 🏠 x1:  $%-5d " DIM "║\n", board[card_list[7][0]]->rent_1_house, 	board[card_list[7][1]]->rent_1_house);
			printf("║" RESET BLUE" Rent with 🏠 x2:  $%-5d " DIM "║\t║" RESET BLUE" Rent with 🏠 x2:  $%-5d " DIM "║\n", board[card_list[7][0]]->rent_2_houses, 	board[card_list[7][1]]->rent_2_houses);
			printf("║" RESET BLUE" Rent with 🏠 x3:  $%-5d " DIM "║\t║" RESET BLUE" Rent with 🏠 x3:  $%-5d " DIM "║\n", board[card_list[7][0]]->rent_3_houses, 	board[card_list[7][1]]->rent_3_houses);
			printf("║" RESET BLUE" Rent with 🏠 x4:  $%-5d " DIM "║\t║" RESET BLUE" Rent with 🏠 x4:  $%-5d " DIM "║\n", board[card_list[7][0]]->rent_4_houses, 	board[card_list[7][1]]->rent_4_houses);
			printf("║" RESET BLUE" Rent with 🏨   :  $%-5d " DIM "║\t║" RESET BLUE" Rent with 🏨   :  $%-5d " DIM "║\n", board[card_list[7][0]]->rent_hotel, 		board[card_list[7][1]]->rent_hotel);
			printf("╠══════════════════════════╣\t╠══════════════════════════╣\n");
			printf("║" RESET BLUE" House price:      $%-5d " DIM "║\t║" RESET BLUE" House price:      $%-5d " DIM "║\n", board[card_list[7][0]]->house_price, 	board[card_list[7][1]]->house_price);
			printf("║" RESET BLUE" Hotel price:🏠x4+ $%-5d " DIM "║\t║" RESET BLUE" Hotel price:🏠x4+ $%-5d " DIM "║\n", board[card_list[7][0]]->house_price, 	board[card_list[7][1]]->house_price);
			printf("╚══════════════════════════╝\t╚══════════════════════════╝\n\n" RESET);
			break;
		case 8:// Company Property
			printf(BEIGE DIM "╔══════════════════════════╗\n");
			printf("║" RESET BEIGE BOLD "  Company Property        " DIM "║\n");
			printf("╚══════════════════════════╝\n\n" RESET BEIGE);

			printf(DIM "╔══════════════════════════╗\t╔══════════════════════════╗\n");
			printf("║" RESET BEIGE" %-24s " DIM "║\t║" RESET BEIGE" %-24s " DIM "║\n", 										board[card_list[8][0]]->name, 			board[card_list[8][1]]->name);
			printf("╠══════════════════════════╣\t╠══════════════════════════╣\n");
			printf("║" RESET BEIGE"           $%-13d " DIM "║\t║" RESET BEIGE"           $%-13d " DIM "║\n", 				board[card_list[8][0]]->price, 			board[card_list[8][1]]->price);
			printf("║" RESET BEIGE" Rent: . . . . . . $%-5d " DIM "║\t║" RESET BEIGE" Rent: . . . . . . $%-5d " DIM "║\n",	board[card_list[8][0]]->rent, 			board[card_list[8][1]]->rent);
			printf("║" RESET BEIGE" Rent with 🏠 x1:  $%-5d " DIM "║\t║" RESET BEIGE" Rent with 🏠 x1:  $%-5d " DIM "║\n", board[card_list[8][0]]->rent_1_house, 	board[card_list[8][1]]->rent_1_house);
			printf("║" RESET BEIGE" Rent with 🏠 x2:  $%-5d " DIM "║\t║" RESET BEIGE" Rent with 🏠 x2:  $%-5d " DIM "║\n", board[card_list[8][0]]->rent_2_houses, 	board[card_list[8][1]]->rent_2_houses);
			printf("║" RESET BEIGE" Rent with 🏠 x3:  $%-5d " DIM "║\t║" RESET BEIGE" Rent with 🏠 x3:  $%-5d " DIM "║\n", board[card_list[8][0]]->rent_3_houses, 	board[card_list[8][1]]->rent_3_houses);
			printf("║" RESET BEIGE" Rent with 🏠 x4:  $%-5d " DIM "║\t║" RESET BEIGE" Rent with 🏠 x4:  $%-5d " DIM "║\n", board[card_list[8][0]]->rent_4_houses, 	board[card_list[8][1]]->rent_4_houses);
			printf("║" RESET BEIGE" Rent with 🏨   :  $%-5d " DIM "║\t║" RESET BEIGE" Rent with 🏨   :  $%-5d " DIM "║\n", board[card_list[8][0]]->rent_hotel, 		board[card_list[8][1]]->rent_hotel);
			printf("╠══════════════════════════╣\t╠══════════════════════════╣\n");
			printf("║" RESET BEIGE" House price:      $%-5d " DIM "║\t║" RESET BEIGE" House price:      $%-5d " DIM "║\n", board[card_list[8][0]]->house_price, 	board[card_list[8][1]]->house_price);
			printf("║" RESET BEIGE" Hotel price:🏠x4+ $%-5d " DIM "║\t║" RESET BEIGE" Hotel price:🏠x4+ $%-5d " DIM "║\n", board[card_list[8][0]]->house_price, 	board[card_list[8][1]]->house_price);
			printf("╚══════════════════════════╝\t╚══════════════════════════╝\n\n" RESET);
			break;
		case 9: // Gare Property
			printf(LIGHT_GRAY DIM "╔══════════════════════════╗\n");
			printf("║" RESET LIGHT_GRAY BOLD "  Gare Property                 " DIM "║\n");
			printf("╚══════════════════════════╝\n\n" RESET LIGHT_GRAY);

			printf(DIM "╔══════════════════════════╗\t╔══════════════════════════╗\t╔══════════════════════════╗\t╔══════════════════════════╗\n");
			printf("║" RESET LIGHT_GRAY" %-24s " DIM "║\t║" RESET LIGHT_GRAY" %-24s " DIM "║\t║" RESET LIGHT_GRAY" %-24s " DIM "║\t║" RESET LIGHT_GRAY" %-24s " DIM "║\n", 																				board[card_list[9][0]]->name, 			board[card_list[9][1]]->name,			board[card_list[9][2]]->name, board[card_list[9][3]]->name);
			printf("╠══════════════════════════╣\t╠══════════════════════════╣\t╠══════════════════════════╣\t╠══════════════════════════╣\n");
			printf("║" RESET LIGHT_GRAY"           $%-13d " DIM "║\t║" RESET LIGHT_GRAY"           $%-13d " DIM "║\t║" RESET LIGHT_GRAY"           $%-13d " DIM "║\t║" RESET LIGHT_GRAY"           $%-13d " DIM "║\n", 									board[card_list[9][0]]->price, 			board[card_list[9][1]]->price,			board[card_list[9][2]]->price, board[card_list[9][3]]->price);
			printf("║" RESET LIGHT_GRAY" Rent: . . . . . . $%-5d " DIM "║\t║" RESET LIGHT_GRAY" Rent: . . . . . . $%-5d " DIM "║\t║" RESET LIGHT_GRAY" Rent: . . . . . . $%-5d " DIM "║\t║" RESET LIGHT_GRAY" Rent: . . . . . . $%-5d " DIM "║\n",		board[card_list[9][0]]->rent, 			board[card_list[9][1]]->rent,			board[card_list[9][2]]->rent, board[card_list[9][3]]->rent);
			printf("║" RESET LIGHT_GRAY" Rent with 🚂 x1:  $%-5d " DIM "║\t║" RESET LIGHT_GRAY" Rent with 🚂 x1:  $%-5d " DIM "║\t║" RESET LIGHT_GRAY" Rent with 🚂 x1:  $%-5d " DIM "║\t║" RESET LIGHT_GRAY" Rent with 🚂 x1:  $%-5d " DIM "║\n", 	board[card_list[9][0]]->rent_1_house, 	board[card_list[9][1]]->rent_1_house,	board[card_list[9][2]]->rent_1_house, board[card_list[9][3]]->rent_1_house);
			printf("║" RESET LIGHT_GRAY" Rent with 🚂 x2:  $%-5d " DIM "║\t║" RESET LIGHT_GRAY" Rent with 🚂 x2:  $%-5d " DIM "║\t║" RESET LIGHT_GRAY" Rent with 🚂 x2:  $%-5d " DIM "║\t║" RESET LIGHT_GRAY" Rent with 🚂 x2:  $%-5d " DIM "║\n", 	board[card_list[9][0]]->rent_2_houses, 	board[card_list[9][1]]->rent_2_houses,	board[card_list[9][2]]->rent_2_houses, board[card_list[9][3]]->rent_2_houses);
			printf("║" RESET LIGHT_GRAY" Rent with 🚂 x3:  $%-5d " DIM "║\t║" RESET LIGHT_GRAY" Rent with 🚂 x3:  $%-5d " DIM "║\t║" RESET LIGHT_GRAY" Rent with 🚂 x3:  $%-5d " DIM "║\t║" RESET LIGHT_GRAY" Rent with 🚂 x3:  $%-5d " DIM "║\n", 	board[card_list[9][0]]->rent_3_houses, 	board[card_list[9][1]]->rent_3_houses,	board[card_list[9][2]]->rent_3_houses, board[card_list[9][3]]->rent_3_houses);
			printf("║" RESET LIGHT_GRAY" Rent with 🚂 x4:  $%-5d " DIM "║\t║" RESET LIGHT_GRAY" Rent with 🚂 x4:  $%-5d " DIM "║\t║" RESET LIGHT_GRAY" Rent with 🚂 x4:  $%-5d " DIM "║\t║" RESET LIGHT_GRAY" Rent with 🚂 x4:  $%-5d " DIM "║\n", 	board[card_list[9][0]]->rent_4_houses, 	board[card_list[9][1]]->rent_4_houses,	board[card_list[9][2]]->rent_4_houses, board[card_list[9][3]]->rent_4_houses);
			printf("╚══════════════════════════╝\t╚══════════════════════════╝\t╚══════════════════════════╝\t╚══════════════════════════╝\n\n" RESET);
			break;
		default:
			printf("No card exists at this position.\n");
			break;
		}
	}
}

// Function to create a new case/card
MonopolyCase *create_case(int index, char *name, int price, int rent, int house_price, int rent_1_house, int rent_2_houses, int rent_3_houses, int rent_4_houses, int rent_hotel, int owner_id, int house_count)
{
	MonopolyCase *new_case = (MonopolyCase *)malloc(sizeof(MonopolyCase));
	new_case->index = index;
	new_case->name = name;
	new_case->price = price;
	new_case->rent = rent;
	new_case->house_price = house_price;
	new_case->rent_1_house = rent_1_house;
	new_case->rent_2_houses = rent_2_houses;
	new_case->rent_3_houses = rent_3_houses;
	new_case->rent_4_houses = rent_4_houses;
	new_case->rent_hotel = rent_hotel;
	new_case->owner_id = owner_id;
	new_case->house_count = house_count;

	return new_case;
}

MonopolyCase **init_board(void)
{
	MonopolyCase **board = (MonopolyCase **)malloc(40 * sizeof(MonopolyCase *));

	for (int i = 0; i < 40; i++)
	{
		board[i] = create_case(i, (char *)malloc(50 * sizeof(char)), 0, 0, 0, 0, 0, 0, 0, 0, 0, 4);
		sprintf(board[i]->name, "case %d", i);
	}

	return board;
}

// Fonction check_house
const char *check_house(MonopolyCase *case_ptr, int line)
{
	static char output[10];

	switch (case_ptr->house_count)
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

void show_board(MonopolyCase **board)
{
	printf(" Parc             ║   Avenue     ║    chance    ║  Boulevard   ║    Avenue    ║   Gare du    ║ Faubourg     ║  Place de    ║  Compagnie   ║   Rue la     ║  Allez en     \n");
	printf("Gratuit           ║   Matignon   ║      🍀      ║  Malesherbes ║ Henri-Martin ║   Nord  🚅   ║ Saint-Honoré ║  la bourse   ║   des eaux   ║   fayette    ║  prison       \n");
	printf("══════════════════╬" BG_RED RED "══════════════" RESET "╩══════════════╩" BG_RED RED "══════════════" RESET "╩" BG_RED RED "══════════════" RESET "╩══════════════╩" BG_YELLOW YELLOW "══════════════" RESET "╩" BG_YELLOW YELLOW "══════════════" RESET "╩══════════════╩" BG_YELLOW YELLOW "══════════════" RESET "╬══════════════════   \n");
	printf("place         %-4s" BG_ORANGE ORANGE"║" RESET " \t\t\t                                                                                                   \t\t " BG_GREEN GREEN "║" RESET "%-4s Avenue		\n", check_house(board[19], 1), check_house(board[31], 0));
	printf("Pigalle       %-4s" BG_ORANGE ORANGE"║" RESET " \t\t\t                                                                                                   \t\t " BG_GREEN GREEN "║" RESET "%-4s de breteuil	\n", check_house(board[19], 0), check_house(board[31], 1));
	printf("══════════════════╣ \t\t\t                                                                                                   \t\t ╠══════════════════	\n");
	printf("Boulevard     %-4s" BG_ORANGE ORANGE"║" RESET " \t\t\t                                                                                                   \t\t " BG_GREEN GREEN "║" RESET "%-4s avenue		\n", check_house(board[18], 1), check_house(board[32], 0));
	printf("Saint-Michel  %-4s" BG_ORANGE ORANGE"║" RESET " \t\t\t                                                                                                   \t\t " BG_GREEN GREEN "║" RESET "%-4s Foch			\n", check_house(board[18], 0), check_house(board[32], 1));
	printf("══════════════════╣ \t\t\t                                                                                                   \t\t ╠══════════════════ 	\n");
	printf("caisse de         ║ \t\t\t                                                                                                   \t\t ║ caisse de		\n");
	printf("communauté        ║ \t\t       	 	◘ Achetez. Vendez. Négociez. Gagnez ! ◘		 						 	  ║ communauté	\n");
	printf("══════════════════╣ \t\t\t       __       __   ______   __    __   ______   _______    ______   __    __      __             \t\t ╠══════════════════	\n");
	printf("avenue        %-4s" BG_ORANGE ORANGE"║" RESET " \t\t\t      /  \\     /  | /      \\ /  \\  /  | /      \\ /       \\  /      \\ /  |  /  \\    /  |     \t\t\t " BG_GREEN GREEN "║" RESET "%-4s Boulevard		\n", check_house(board[16], 1), check_house(board[34], 0));
	printf("Mozard        %-4s" BG_ORANGE ORANGE"║" RESET " \t\t\t      $$  \\   /$$ |/$$$$$$  |$$  \\ $$ |/$$$$$$  |$$$$$$$  |/$$$$$$  |$$ |  $$  \\  /$$/          \t\t " BG_GREEN GREEN "║" RESET "%-4s des capucines	\n", check_house(board[16], 0), check_house(board[34], 1));
	printf("══════════════════╣ \t\t\t      $$$  \\ /$$$ |$$ |  $$ |$$$  \\$$ |$$ |  $$ |$$ |__$$ |$$ |  $$ |$$ |   $$  \\/$$/           \t\t ╠══════════════════	\n");
	printf("Gare de           ║ \t\t\t      $$$$  /$$$$ |$$ |  $$ |$$$$  $$ |$$ |  $$ |$$    $$/ $$ |  $$ |$$ |    $$  $$\\              \t\t ║ gare 🚅	\n");
	printf("Lyon 🚅           ║ \t\t\t      $$ $$ $$/$$ |$$ |  $$ |$$ $$ $$ |$$ |  $$ |$$$$$$$/  $$ |  $$ |$$ |     $$$$/                \t\t ║ Saint-Lazare	\n");
	printf("══════════════════╣ \t\t\t      $$ |$$$/ $$ |$$ \\__$$ |$$ |$$$$ |$$ \\__$$ |$$ |      $$ \\__$$ |$$ |_____ $$ |             \t\t ╠══════════════════	\n");
	printf("Rue de        %-4s" BG_BRIGHT_MAGENTA BRIGHT_MAGENTA"║" RESET " \t\t\t      $$ | $/  $$ |$$    $$/ $$ | $$$ |$$    $$/ $$ |      $$    $$/ $$       |$$ |                \t\t ║    chance		\n", check_house(board[14], 1));
	printf("Paradis       %-4s" BG_BRIGHT_MAGENTA BRIGHT_MAGENTA"║" RESET " \t\t\t      $$/      $$/  $$$$$$/  $$/   $$/  $$$$$$/  $$/        $$$$$$/  $$$$$$$$/ $$/                 \t\t ║	 🍀		\n", check_house(board[14], 0));
	printf("══════════════════╣ \t\t\t                                                                                                   \t\t ╠══════════════════	\n");
	printf("Avenue de     %-4s" BG_BRIGHT_MAGENTA BRIGHT_MAGENTA"║" RESET " \t\t\t                                                                                                   \t\t " BG_BLUE BLUE "║" RESET "%-4s Avenue des	\n", check_house(board[13], 1), check_house(board[37], 0));
	printf("Neuilly       %-4s" BG_BRIGHT_MAGENTA BRIGHT_MAGENTA"║" RESET " \t\t\t  " DIM "     _                      _             _            _ _ _   _               _               " RESET "  \t\t " BG_BLUE BLUE "║" RESET "%-4s champs-élysées\n", check_house(board[13], 0), check_house(board[37], 1));
	printf("══════════════════╣ \t\t\t  " DIM "    | |_ ___ _ __ _ __ ___ (_)_ __   __ _| |   ___  __| (_) |_(_) ___  _ __   | |              " RESET "  \t\t ╠══════════════════	\n");
	printf("compagnie         ║ \t\t\t  " DIM "    | __/ _ \\ '__| '_ ` _ \\| | '_ \\ / _` | |  / _ \\/ _` | | __| |/ _ \\| '_ \\  | |        " RESET "  \t\t\t ║ Taxe de   	\n");
	printf("électrique        ║ \t\t\t  " DIM "    | ||  __/ |  | | | | | | | | | | (_| | | |  __/ (_| | | |_| | (_) | | | | |_|              " RESET "  \t\t ║ Luxe 💍    	\n");
	printf("══════════════════╣ \t\t\t  " DIM "     \\__\\___|_|  |_| |_| |_|_|_| |_|\\__,_|_|  \\___|\\__,_|_|\\__|_|\\___/|_| |_| (_)       " RESET "  \t\t\t ╠══════════════════	\n");
	printf("Boulevard de  %-4s" BG_BRIGHT_MAGENTA BRIGHT_MAGENTA"║" RESET " \t\t\t                                                                                                   \t\t " BG_BLUE BLUE "║" RESET "%-4s Rue de    	\n", check_house(board[11], 1), check_house(board[39], 0));
	printf("la villette   %-4s" BG_BRIGHT_MAGENTA BRIGHT_MAGENTA"║" RESET " \t\t\t                                                                                                   \t\t " BG_BLUE BLUE "║" RESET "%-4s la Paix   	\n", check_house(board[11], 0), check_house(board[39], 1));
	printf("══════════════════╬" BG_BRIGHT_CYAN BRIGHT_CYAN "══════════════" RESET "╦" BG_BRIGHT_CYAN BRIGHT_CYAN "══════════════" RESET "╦══════════════╦" BG_BRIGHT_CYAN BRIGHT_CYAN "══════════════" RESET "╦══════════════╦══════════════╦" BG_BROWN BROWN "══════════════" RESET "╦══════════════╦" BG_BROWN BROWN "══════════════" RESET "╬══════════════════ \n");
	printf(" Simple           ║ Avenue de la ║  Rue de      ║    chance    ║ Rue de       ║ Gare  🚅     ║  Impôts sur  ║  Rue         ║  Caisse de   ║ Boulevard de ║  Case         \n");
	printf(" visite           ║ République   ║  Courcelles  ║      🍀      ║ Vaugirard    ║ Montparnasse ║  le revenue  ║  Lecourbe    ║  Communauté  ║ Belleville   ║  Départ       \n");
}

void clear_terminal(void)
{
	system("cls");
}

void show_rules(void)
{
	// Encadrement du titre des règles
	printf(DIM BOLD "======================================================\n");
	printf("=             ⭐️ RÈGLES DU MONOPOLY ⭐️             =\n");
	printf("======================================================\n\n" RESET);

	printf(BOLD UNDERLINE "1. OBJECTIF DU JEU\n" RESET);
	printf("   L'objectif du Monopoly est de ruiner les autres joueurs en acquérant des propriétés,\n");
	printf("   construisant des maisons et hôtels, et en leur faisant payer des loyers élevés.\n\n");

	printf(BOLD UNDERLINE "2. CONFIGURATION DU JEU\n" RESET);
	printf("   - Le jeu se joue de 2 à 8 joueurs.\n");
	printf("   - Chaque joueur commence avec 1500 unités de monnaie.\n");
	printf("   - Les joueurs choisissent une couleur et un pion. Les pions sont placés sur la case \"Départ\".\n\n");

	printf(BOLD UNDERLINE "3. DÉROULEMENT DU JEU\n" RESET);
	printf("   - Les joueurs lancent les dés à tour de rôle pour avancer sur le plateau.\n");
	printf("   - En fonction de la case sur laquelle ils atterrissent, ils peuvent :\n");
	printf("     1. Acheter une propriété\n");
	printf("     2. Payer un loyer\n");
	printf("     3. Tirer une carte Chance ou Caisse de Communauté\n");
	printf("     4. Payer des taxes\n");
	printf("     5. Aller en prison\n\n");

	printf(BOLD UNDERLINE "4. LANCER DES DÉS\n" RESET);
	printf("	- Lors de leur tour, les joueurs lancent deux dés.\n");
	printf("	- Si un joueur fait un double, il joue à nouveau. Trois doubles consécutifs\n");
	printf("     envoient le joueur directement en prison.\n\n");

	printf(BOLD UNDERLINE "5. PROPRIÉTÉS\n" RESET);
	printf("	- Lorsqu'un joueur atterrit sur une propriété non possédée, il peut l'acheter.\n");
	printf("	- Si le joueur choisit de ne pas acheter, la propriété est mise aux enchères.\n");
	printf("	- Les propriétés peuvent être hypothéquées pour lever des fonds.\n\n");

	printf(BOLD UNDERLINE "6. LOYERS\n" RESET);
	printf("	- Les loyers sont payés lorsque des joueurs atterrissent sur des propriétés.\n");
	printf("	- Les loyers varient en fonction du nombre de maisons ou d'hôtels sur la propriété.\n");
	printf("	- Les loyers sont doublés si le propriétaire possède tous les terrains d'une même couleur.\n\n");

	printf(BOLD UNDERLINE "7. MAISONS ET HÔTELS\n" RESET);
	printf("	- Un joueur peut construire des maisons sur ses propriétés lorsqu'il possède\n");
	printf("     tous les terrains d'une couleur.\n");
	printf("	- Les maisons doivent être construites uniformément : on ne peut pas construire\n");
	printf("     une deuxième maison sur une propriété avant que chaque propriété de l'ensemble\n");
	printf("     n'ait une maison.\n");
	printf("	- Une fois que le joueur a quatre maisons sur une propriété, il peut construire un hôtel.\n\n");

	printf(BOLD UNDERLINE "8. CARDS CHANCE ET CAISSE DE COMMUNAUTÉ\n" RESET);
	printf("	- Les cartes Chance et Caisse de Communauté contiennent des instructions variées :\n");
	printf("	- Gagner de l'argent\n");
	printf("	- Payer une amende\n");
	printf("	- Se déplacer sur le plateau\n");
	printf("	- Un joueur doit suivre les instructions de la carte tirée.\n\n");

	printf(BOLD UNDERLINE "9. IMPÔTS ET TAXES\n" RESET);
	printf("	- Les joueurs doivent payer des taxes lorsqu'ils atterrissent sur certaines cases.\n");
	printf("	- Impôt sur le revenu : 200 unités de monnaie\n");
	printf("	- Taxe de luxe : 75 unités de monnaie\n");
	printf("	- Les taxes doivent être payées immédiatement.\n\n");

	printf(BOLD UNDERLINE "10. PRISON\n" RESET);
	printf("	- Un joueur peut être envoyé en prison de plusieurs manières :\n");
	printf("     	1. En tombant sur la case \"Allez en Prison\".\n");
	printf("     	2. En tirant une carte indiquant de se rendre en prison.\n");
	printf("	- Pour sortir de prison, un joueur peut :\n");
	printf("	- Payer une amende de 50 unités de monnaie.\n");
	printf("	- Utiliser une carte «Sortie de Prison». \n");
	printf("	- Lancer un double (dans ce cas, il avance du montant du double et joue à nouveau).\n");
	printf("	- Si le joueur n'a pas obtenu de double après trois lancers, il doit payer l'amende et sortir.\n\n");

	printf(BOLD UNDERLINE "11. FAILLITE\n" RESET);
	printf("	- Si un joueur ne peut pas payer une dette, il doit vendre des propriétés ou\n");
	printf("     hypothéquer des terrains pour obtenir des fonds.\n");
	printf("	- Un joueur est déclaré en faillite s'il doit de l'argent à un autre joueur et\n");
	printf("     n'a pas de fonds disponibles. Il doit alors donner toutes ses propriétés et\n");
	printf("     son argent au créancier.\n\n");

	printf(BOLD UNDERLINE "12. FIN DU JEU\n" RESET);
	printf("	- Le jeu se termine lorsqu'un joueur a fait faillite et qu'il ne reste qu'un joueur.\n");
	printf("	- Ce joueur est déclaré vainqueur et remporte la partie.\n\n");

	printf(DIM BOLD "======================================================\n");
	printf("=         Merci d'avoir consulté les règles!         =\n");
	printf("======================================================\n\n" RESET);
}