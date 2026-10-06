#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "monopoly.h"

/**
 * Displays a Monopoly card in the console.
 *
 * This function displays a Monopoly card in the console, with information about
 * the property, such as the name, price, standard rent, rents with houses and
 * hotels, and the prices of houses and hotels.
 *
 * @param board The Monopoly board structure.
 * @param index The index of the card to display in the board structure.
 */
void show_card(MonopolyCase **board, int index)
{
	if (index >= 0 && index < 40 && board[index] != NULL)
	{
		char formatted_name[25];
		char formatted_price[25];
		char formatted_rent[25];

		// Format the strings to 24 characters
		format_string(board[index]->name, formatted_name);
		format_price(board[index]->price, formatted_price);
		format_price(board[index]->rent, formatted_rent);

		// Formatted display of the card
		printf(DIM);
		printf("╔══════════════════════════╗\n");
		printf("║" RESET " %-24s " DIM "║\n", formatted_name); 								  	// Property name
		printf("╠══════════════════════════╣\n");
		printf("║" RESET "           $%-13d " DIM "║\n", board[index]->price);				  	// Property price
		printf("║" RESET " Rent: . . . . . . $%-5d " DIM "║\n", board[index]->rent);		  	// Standard rent
		printf("║" RESET " Rent with 🏠 x1:  $%-5d " DIM "║\n", board[index]->rent_1_house);  	// Rent with 1 house
		printf("║" RESET " Rent with 🏠 x2:  $%-5d " DIM "║\n", board[index]->rent_2_houses); 	// Rent with 2 houses
		printf("║" RESET " Rent with 🏠 x3:  $%-5d " DIM "║\n", board[index]->rent_3_houses); 	// Rent with 3 houses
		printf("║" RESET " Rent with 🏠 x4:  $%-5d " DIM "║\n", board[index]->rent_4_houses); 	// Rent with 4 houses
		printf("║" RESET " Rent with 🏨   :  $%-5d " DIM "║\n", board[index]->rent_hotel);	  	// Rent with a hotel
		printf("╠══════════════════════════╣\n");
		printf("║" RESET " House price:      $%-5d " DIM "║\n", board[index]->house_price);		// House price
		printf("║" RESET " Hotel price:🏠x4+ $%-5d " DIM "║\n", board[index]->house_price); 	// Hotel price
		printf("╚══════════════════════════╝\n\n");
		printf(RESET);
	}
	else
		printf("No card exists at this position.\n");	// if the card doesn't exist, display this message
}

/**
 * @brief Displays the color property corresponding to the index.
 *
 * @details The properties are displayed in a table format with the basic
 *          information of the property (name, price, rent, etc.).
 *
 * @param board The array of properties.
 * @param index The index of the property to display.
 */
void show_color_card(MonopolyCase **board, int index)
{
	if (index >= 0 && index <= 9 && board[index] != NULL)
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
			{5, 15, 25, 35}};	// List of cards positions for each color
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
			printf("║" RESET BRIGHT_CYAN" Rent with 🏠 x1:  $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent with 🏠 x1:  $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent with 🏠 x1:  $%-5d " DIM "║\n", 	board[card_list[1][0]]->rent_1_house, 	board[card_list[1][1]]->rent_1_house,	board[card_list[1][2]]->rent_1_house);
			printf("║" RESET BRIGHT_CYAN" Rent with 🏠 x2:  $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent with 🏠 x2:  $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent with 🏠 x2:  $%-5d " DIM "║\n", 	board[card_list[1][0]]->rent_2_houses, 	board[card_list[1][1]]->rent_2_houses,	board[card_list[1][2]]->rent_2_houses);
			printf("║" RESET BRIGHT_CYAN" Rent with 🏠 x3:  $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent with 🏠 x3:  $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent with 🏠 x3:  $%-5d " DIM "║\n", 	board[card_list[1][0]]->rent_3_houses, 	board[card_list[1][1]]->rent_3_houses,	board[card_list[1][2]]->rent_3_houses);
			printf("║" RESET BRIGHT_CYAN" Rent with 🏠 x4:  $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent with 🏠 x4:  $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent with 🏠 x4:  $%-5d " DIM "║\n", 	board[card_list[1][0]]->rent_4_houses, 	board[card_list[1][1]]->rent_4_houses,	board[card_list[1][2]]->rent_4_houses);
			printf("║" RESET BRIGHT_CYAN" Rent with 🏨   :  $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent with 🏨   :  $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Rent with 🏨   :  $%-5d " DIM "║\n", 	board[card_list[1][0]]->rent_hotel, 	board[card_list[1][1]]->rent_hotel,		board[card_list[1][2]]->rent_hotel);
			printf("╠══════════════════════════╣\t╠══════════════════════════╣\t╠══════════════════════════╣\n");
			printf("║" RESET BRIGHT_CYAN" House price:      $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" House price:      $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" House price:      $%-5d " DIM "║\n", 	board[card_list[1][0]]->house_price, 	board[card_list[1][1]]->house_price,	board[card_list[1][2]]->house_price);
			printf("║" RESET BRIGHT_CYAN" Hotel price:🏠x4+ $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Hotel price:🏠x4+ $%-5d " DIM "║\t║" RESET BRIGHT_CYAN" Hotel price:🏠x4+ $%-5d " DIM "║\n", 	board[card_list[1][0]]->house_price, 	board[card_list[1][1]]->house_price,	board[card_list[1][2]]->house_price);
			printf("╚══════════════════════════╝\t╚══════════════════════════╝\t╚══════════════════════════╝\n\n" RESET);
			break;
		case 2:// Magenta Property
		    printf(MAGENTA DIM "╔══════════════════════════╗\n");
		    printf("║" RESET MAGENTA BOLD "  Magenta Property        " DIM "║\n");
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
		    printf("║" RESET RED BOLD "  Red Property            " DIM "║\n");
		    printf("╚══════════════════════════╝\n\n" RESET RED);
		
		    printf(DIM "╔══════════════════════════╗\t╔══════════════════════════╗\t╔══════════════════════════╗\n");
		    printf("║" RESET RED" %-24s " DIM "║\t║" RESET RED" %-24s " DIM "║\t║" RESET RED" %-24s " DIM "║\n", board[card_list[4][0]]->name, board[card_list[4][1]]->name, board[card_list[4][2]]->name);
		    printf("╠══════════════════════════╣\t╠══════════════════════════╣\t╠══════════════════════════╣\n");
		    printf("║" RESET RED"           $%-13d " DIM "║\t║" RESET RED"           $%-13d " DIM "║\t║" RESET RED"           $%-13d " DIM "║\n", board[card_list[4][0]]->price, board[card_list[4][1]]->price, board[card_list[4][2]]->price);
		    printf("║" RESET RED" Rent: . . . . . . $%-5d " DIM "║\t║" RESET RED" Rent: . . . . . . $%-5d " DIM "║\t║" RESET RED" Rent: . . . . . . $%-5d " DIM "║\n", board[card_list[4][0]]->rent, board[card_list[4][1]]->rent, board[card_list[4][2]]->rent);
		    printf("║" RESET RED" Rent with 🏠 x1:  $%-5d " DIM "║\t║" RESET RED" Rent with 🏠 x1:  $%-5d " DIM "║\t║" RESET RED" Rent with 🏠 x1:  $%-5d " DIM "║\n", board[card_list[4][0]]->rent_1_house, board[card_list[4][1]]->rent_1_house, board[card_list[4][2]]->rent_1_house);
		    printf("║" RESET RED" Rent with 🏠 x2:  $%-5d " DIM "║\t║" RESET RED" Rent with 🏠 x2:  $%-5d " DIM "║\t║" RESET RED" Rent with 🏠 x2:  $%-5d " DIM "║\n", board[card_list[4][0]]->rent_2_houses, board[card_list[4][1]]->rent_2_houses, board[card_list[4][2]]->rent_2_houses);
		    printf("║" RESET RED" Rent with 🏠 x3:  $%-5d " DIM "║\t║" RESET RED" Rent with 🏠 x3:  $%-5d " DIM "║\t║" RESET RED" Rent with 🏠 x3:  $%-5d " DIM "║\n", board[card_list[4][0]]->rent_3_houses, board[card_list[4][1]]->rent_3_houses, board[card_list[4][2]]->rent_3_houses);
		    printf("║" RESET RED" Rent with 🏠 x4:  $%-5d " DIM "║\t║" RESET RED" Rent with 🏠 x4:  $%-5d " DIM "║\t║" RESET RED" Rent with 🏠 x4:  $%-5d " DIM "║\n", board[card_list[4][0]]->rent_4_houses, board[card_list[4][1]]->rent_4_houses, board[card_list[4][2]]->rent_4_houses);
		    printf("║" RESET RED" Rent with 🏨   :  $%-5d " DIM "║\t║" RESET RED" Rent with 🏨   :  $%-5d " DIM "║\t║" RESET RED" Rent with 🏨   :  $%-5d " DIM "║\n", board[card_list[4][0]]->rent_hotel, board[card_list[4][1]]->rent_hotel, board[card_list[4][2]]->rent_hotel);
		    printf("╠══════════════════════════╣\t╠══════════════════════════╣\t╠══════════════════════════╣\n");
		    printf("║" RESET RED" House price:      $%-5d " DIM "║\t║" RESET RED" House price:      $%-5d " DIM "║\t║" RESET RED" House price:      $%-5d " DIM "║\n", board[card_list[4][0]]->house_price, board[card_list[4][1]]->house_price, board[card_list[4][2]]->house_price);
		    printf("║" RESET RED" Hotel price:🏠x4+ $%-5d " DIM "║\t║" RESET RED" Hotel price:🏠x4+ $%-5d " DIM "║\t║" RESET RED" Hotel price:🏠x4+ $%-5d " DIM "║\n", board[card_list[4][0]]->house_price, board[card_list[4][1]]->house_price, board[card_list[4][2]]->house_price);
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
		    printf("║" RESET GREEN BOLD "  Green Property          " DIM "║\n");
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
			printf("║" RESET BLUE BOLD "  Blue Property           " DIM "║\n");
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
			printf("║" RESET LIGHT_GRAY BOLD "  Gare Property           " DIM "║\n");
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

/**
 * @brief Displays the rules of Monopoly.
 *
 * @details Function that displays the rules of Monopoly in text mode.
 *          The rules are displayed in ANSI mode, with different colors and
 *          fonts to facilitate reading.
 */
void show_rules(void)
{
	printf(DIM BOLD "======================================================\n");
	printf("=             ⭐️ RÈGLES DU MONOPOLY ⭐️             =\n");
	printf("======================================================\n\n" RESET);
	// OBJECTIFE DU JEU
	printf(BOLD UNDERLINE "1. OBJECTIF DU JEU\n" RESET);
	printf("   L'objectif du Monopoly est de ruiner les autres joueurs en acquérant des propriétés,\n");
	printf("   construisant des maisons et hôtels, et en leur faisant payer des loyers élevés.\n\n");
	// CONFIGURATION DU JEU
	printf(BOLD UNDERLINE "2. CONFIGURATION DU JEU\n" RESET);
	printf("   - Le jeu se joue de 2 à 8 joueurs.\n");
	printf("   - Chaque joueur commence avec 1500 unités de monnaie.\n");
	printf("   - Les joueurs choisissent une couleur et un pion. Les pions sont placés sur la case \"Départ\".\n\n");
	// DÉROULEMENT DU JEU
	printf(BOLD UNDERLINE "3. DÉROULEMENT DU JEU\n" RESET);
	printf("   - Les joueurs lancent les dés à tour de rôle pour avancer sur le plateau.\n");
	printf("   - En fonction de la case sur laquelle ils atterrissent, ils peuvent :\n");
	printf("     1. Acheter une propriété\n");
	printf("     2. Payer un loyer\n");
	printf("     3. Tirer une carte Chance ou Caisse de Communauté\n");
	printf("     4. Payer des taxes\n");
	printf("     5. Aller en prison\n\n");
	// LANCER DES DÉS
	printf(BOLD UNDERLINE "4. LANCER DES DÉS\n" RESET);
	printf("	- Lors de leur tour, les joueurs lancent deux dés.\n");
	printf("	- Si un joueur fait un double, il joue à nouveau. Trois doubles consécutifs\n");
	printf("     envoient le joueur directement en prison.\n\n");
	// PROPRIÉTÉS
	printf(BOLD UNDERLINE "5. PROPRIÉTÉS\n" RESET);
	printf("	- Lorsqu'un joueur atterrit sur une propriété non possédée, il peut l'acheter.\n");
	printf("	- Si le joueur choisit de ne pas acheter, la propriété est mise aux enchères.\n");
	printf("	- Les propriétés peuvent être hypothéquées pour lever des fonds.\n\n");
	// LOYERS
	printf(BOLD UNDERLINE "6. LOYERS\n" RESET);
	printf("	- Les loyers sont payés lorsque des joueurs atterrissent sur des propriétés.\n");
	printf("	- Les loyers varient en fonction du nombre de maisons ou d'hôtels sur la propriété.\n");
	printf("	- Les loyers sont doublés si le propriétaire possède tous les terrains d'une même couleur.\n\n");
	// MAISONS ET HÔTELS
	printf(BOLD UNDERLINE "7. MAISONS ET HÔTELS\n" RESET);
	printf("	- Un joueur peut construire des maisons sur ses propriétés lorsqu'il possède\n");
	printf("     tous les terrains d'une couleur.\n");
	printf("	- Les maisons doivent être construites uniformément : on ne peut pas construire\n");
	printf("     une deuxième maison sur une propriété avant que chaque propriété de l'ensemble\n");
	printf("     n'ait une maison.\n");
	printf("	- Une fois que le joueur a quatre maisons sur une propriété, il peut construire un hôtel.\n\n");
	// CARTES CHANCE ET CAISSE DE COMMUNAUTÉS
	printf(BOLD UNDERLINE "8. CARTES CHANCE ET CAISSE DE COMMUNAUTÉ\n" RESET);
	printf("	- Les cartes Chance et Caisse de Communauté contiennent des instructions variées :\n");
	printf("	- Gagner de l'argent\n");
	printf("	- Payer une amende\n");
	printf("	- Se déplacer sur le plateau\n");
	printf("	- Un joueur doit suivre les instructions de la carte tirée.\n\n");
	// IMPOTS ET TAXES
	printf(BOLD UNDERLINE "9. IMPÔTS ET TAXES\n" RESET);
	printf("	- Les joueurs doivent payer des taxes lorsqu'ils atterrissent sur certaines cases.\n");
	printf("	- Impôt sur le revenu : 200 unités de monnaie\n");
	printf("	- Taxe de luxe : 75 unités de monnaie\n");
	printf("	- Les taxes doivent être payées immédiatement.\n\n");
	// PRISON
	printf(BOLD UNDERLINE "10. PRISON\n" RESET);
	printf("	- Un joueur peut être envoyé en prison de plusieurs manières :\n");
	printf("     	1. En tombant sur la case \"Allez en Prison\".\n");
	printf("     	2. En tirant une carte indiquant de se rendre en prison.\n");
	printf("	- Pour sortir de prison, un joueur peut :\n");
	printf("	- Payer une amende de 50 unités de monnaie.\n");
	printf("	- Utiliser une carte «Sortie de Prison». \n");
	printf("	- Lancer un double (dans ce cas, il avance du montant du double et joue à nouveau).\n");
	printf("	- Si le joueur n'a pas obtenu de double après trois lancers, il doit payer l'amende et sortir.\n\n");
	// FAILLITE
	printf(BOLD UNDERLINE "11. FAILLITE\n" RESET);
	printf("	- Si un joueur ne peut pas payer une dette, il doit vendre des propriétés ou\n");
	printf("     hypothéquer des terrains pour obtenir des fonds.\n");
	printf("	- Un joueur est déclaré en faillite s'il doit de l'argent à un autre joueur et\n");
	printf("     n'a pas de fonds disponibles. Il doit alors donner toutes ses propriétés et\n");
	printf("     son argent au créancier.\n\n");
	// FIN DU JEU
	printf(BOLD UNDERLINE "12. FIN DU JEU\n" RESET);
	printf("	- Le jeu se termine lorsqu'un joueur a fait faillite et qu'il ne reste qu'un joueur.\n");
	printf("	- Ce joueur est déclaré vainqueur et remporte la partie.\n\n");
	// CONSEILS
	printf(BOLD UNDERLINE "13. CONSEILS\n" RESET);
	printf("	- N'oubliez pas de vous assurer que vous avez suffisamment d'argent pour\n");
	printf("     payer les loyers lorsque vous achetez des propriétés.\n");
	printf("	- Essayez de vous débarrasser des propriétés les moins rentables pour vous\n");
	printf("     concentrer sur les plus profitables.\n");
	printf("	- Utilisez vos cartes Chance et Caisse de Communauté judicieusement.\n");
	printf("	- N'ayez pas peur de prendre des risques, mais assurez-vous de ne pas\n");
	printf("     mettre en danger vos finances.\n\n");
	// AVANTAGES
	printf(BOLD UNDERLINE "14. AVANTAGES\n" RESET);
	printf("	- Les avantages sont des bonus que vous pouvez obtenir en achetant certaines\n");
	printf("     propriétés, comme les sociétés de services publics ou les gares.\n");
	printf("	- Les avantages vous permettent de gagner plus d'argent lorsque vous possédez\n");
	printf("     certaines propriétés.\n");

	printf(DIM BOLD "======================================================\n");
	printf("=         Merci d'avoir consulté les règles!         =\n");
	printf("======================================================\n\n" RESET);
}