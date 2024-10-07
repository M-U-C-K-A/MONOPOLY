#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "monopoly.h"

void format_string(char *str, char *output) {
	int len = strlen(str);
	if (len > 24) {
		strncpy(output, str, 24); // Crop à 24 caractères
		output[24] = '\0'; // Ajouter le terminateur de chaîne
	} else {
		sprintf(output, "%-24s", str); // Padding jusqu'à 24 caractères
	}
}

// Fonction pour crop ou padd un prix avec un dollar avant
void format_price(int price, char *output) {
	char price_str[30];
	sprintf(price_str, "$%d", price); // Ajouter le dollar au début du prix
	int len = strlen(price_str);
	if (len > 24) {
		strncpy(output, price_str, 24); // Crop si nécessaire
		output[24] = '\0';
	} else {
		sprintf(output, "%-24s", price_str); // Padding jusqu'à 24 caractères
	}
}

// Fonction d'affichage formatée d'une case du plateau
void show_card(MonopolyCase **board, int index) {
	if (board[index] != NULL) {
		char formatted_name[25];  // 24 caractères + terminateur de chaîne
		char formatted_price[25];
		char formatted_rent[25];

		// Formater les chaînes
		format_string(board[index]->name, formatted_name);
		format_price(board[index]->price, formatted_price);
		format_price(board[index]->rent, formatted_rent);

		// Affichage formaté
		printf(DIM"╔══════════════════════════╗\n");
		printf("║"RESET" %-24s "DIM"║\n", formatted_name);  // Nom du terrain
		printf("╠══════════════════════════╣\n");
		printf("║"RESET"           $%-13d "DIM"║\n", board[index]->price);  // Prix du terrain
		printf("║"RESET" Rent: . . . . . . $%-5d "DIM"║\n", board[index]->rent);  // Loyer standard
		printf("║"RESET" Rent with 🏠 x1:  $%-5d "DIM"║\n", board[index]->rent_1_house);  // Loyer 1 maison
		printf("║"RESET" Rent with 🏠 x2:  $%-5d "DIM"║\n", board[index]->rent_2_houses);  // Loyer 2 maisons
		printf("║"RESET" Rent with 🏠 x3:  $%-5d "DIM"║\n", board[index]->rent_3_houses);  // Loyer 3 maisons
		printf("║"RESET" Rent with 🏠 x4:  $%-5d "DIM"║\n", board[index]->rent_4_houses);  // Loyer 4 maisons
		printf("║"RESET" Rent with 🏨   :  $%-5d "DIM"║\n", board[index]->rent_hotel);  // Loyer avec hôtel
		printf("╠══════════════════════════╣\n");
		printf("║"RESET" House price:      $%-5d "DIM"║\n", board[index]->house_price);  // Prix d'une maison
		printf("║"RESET" Hotel price:🏠x4+ $%-5d "DIM"║\n", board[index]->house_price, board[index]->house_price);  // Prix d'un hôtel
		printf("╚══════════════════════════╝\n\n"RESET);
	} else {
		printf("No card exists at this position.\n");
	}
}

// Function to create a new case/card
MonopolyCase* create_case(int index, char *name, int price, int rent, int house_price, int rent_1_house, int rent_2_houses, int rent_3_houses, int rent_4_houses, int rent_hotel, int owner_id, int house_count) {
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

MonopolyCase** init_board(void)
{
	MonopolyCase **board = (MonopolyCase **)malloc(40 * sizeof(MonopolyCase *));
	
	board[0] = create_case(0, "Start", 0, 0, 0, 0, 0, 0, 0, 0,0 ,0);
	board[1] = create_case(1, "Boulevard de Belleville", 60, 2, 50, 10, 30, 90, 160, 250,0 ,1);
	board[2] = create_case(2, "Community Chest", 0, 0, 0, 0, 0, 0, 0, 0,0 ,0);
	board[3] = create_case(3, "Rue Lecourbe", 60, 4, 50, 20, 60, 180, 320, 450,0 ,3);
	board[4] = create_case(4, "Income Tax", 0, 200, 0, 0, 0, 0, 0, 0,0 ,0);
	board[5] = create_case(5, "Montparnasse Station", 200, 25, 0, 0, 0, 0, 0, 0,0 ,0);
	board[6] = create_case(6, "Rue de Vaugirard", 100, 6, 50, 30, 90, 270, 400, 550,0 ,2);
	board[7] = create_case(7, "Chance", 0, 0, 0, 0, 0, 0, 0, 0,0 ,0);
	board[8] = create_case(8, "Rue de Courcelles", 100, 6, 50, 30, 90, 270, 400, 550,0 ,4);
	board[9] = create_case(9, "Avenue de la Republique", 120, 8, 50, 40, 100, 300, 450, 600,0 ,5);
	board[10] = create_case(10, "Just Visiting / Jail", 0, 0, 0, 0, 0, 0, 0, 0,0 ,0);
	board[11] = create_case(11, "Boulevard de la Villette", 140, 10, 100, 50, 150, 450, 625, 750,0 ,5);
	board[12] = create_case(12, "Water Works", 150, 0, 0, 0, 0, 0, 0, 0,0 ,0);
	board[13] = create_case(13, "Rue de la Paix", 140, 10, 100, 50, 150, 450, 625, 750,0 ,0);
	board[14] = create_case(14, "Avenue de Neuilly", 160, 12, 100, 50, 150, 450, 625, 750,0 ,0);
	board[15] = create_case(15, "Lyon Station", 200, 25, 0, 0, 0, 0, 0, 0,0 ,0);
	board[16] = create_case(16, "Avenue de la Republique", 200, 25, 0, 0, 0, 0, 0, 0,0 ,0);
	board[17] = create_case(17, "Community Chest", 0, 0, 0, 0, 0, 0, 0, 0,0 ,0);
	board[18] = create_case(18, "Avenue des Champs-elysees", 350, 35, 200, 175, 500, 1100, 1300, 1500,0 ,0);
	board[19] = create_case(19, "Luxury Tax", 0, 100, 0, 0, 0, 0, 0, 0,0 ,0);
	board[20] = create_case(20, "Rue de la Victoire", 400, 50, 200, 200, 600, 1400, 1700, 2000,0 ,0);
	board[21] = create_case(21, "Saint-Lazare Station", 200, 25, 0, 0, 0, 0, 0, 0,0 ,0);
	board[22] = create_case(22, "Chance", 0, 0, 0, 0, 0, 0, 0, 0,0 ,0);
	board[23] = create_case(23, "Avenue de Breteuil", 300, 26, 200, 130, 390, 900, 1100, 1275,0 ,0);
	board[24] = create_case(24, "Avenue Foch", 300, 26, 200, 130, 390, 900, 1100, 1275,0 ,0);
	board[25] = create_case(25, "Community Chest", 0, 0, 0, 0, 0, 0, 0, 0,0 ,0);
	board[26] = create_case(26, "Boulevard des Capucines", 320, 28, 200, 150, 450, 1000, 1200, 1400,0 ,0);
	board[27] = create_case(27, "Saint-Lazare Station", 200, 25, 0, 0, 0, 0, 0, 0,0 ,0);
	board[28] = create_case(28, "Chance", 0, 0, 0, 0, 0, 0, 0, 0,0 ,0);
	board[29] = create_case(29, "Rue la Fayette", 280, 24, 150, 120, 360, 850, 1025, 1200,0 ,0);
	board[30] = create_case(30, "Go to Jail", 0, 0, 0, 0, 0, 0, 0, 0,0 ,0);
	board[31] = create_case(31, "Avenue de la Bourdonnais", 300, 32, 200, 140, 410, 950, 1200, 1450,0 ,0);
	board[32] = create_case(32, "Bastille Station", 200, 25, 0, 0, 0, 0, 0, 0,0 ,0);
	board[33] = create_case(33, "Avenue de Trocadero", 350, 35, 200, 175, 500, 1100, 1300, 1500,0 ,0);
	board[34] = create_case(34, "Community Chest", 0, 0, 0, 0, 0, 0, 0, 0,0 ,0);
	board[35] = create_case(35, "Park Lane", 350, 35, 200, 175, 500, 1100, 1300, 1500,0 ,0);
	board[36] = create_case(36, "Mayfair", 400, 50, 200, 200, 600, 1400, 1700, 2000,0 ,0);

	return board;
}



const char* HOUSE_EMOJI = "🏠";  // Emoji de la maison
const char* HOTEL_EMOJI = "🏨";  // Emoji de l'hôtel
const char* HOUSE_CHAR = "H";    // Repli en cas de problème avec les emojis
const char* HOTEL_CHAR = "O";    // Repli pour l'hôtel

// Fonction pour afficher les maisons ou l'hôtel en fonction du house_count
char* house(MonopolyCase *property) {
    static char output[64]; // Chaîne suffisamment grande pour stocker plusieurs maisons/hôtel et des espaces
    int house_count = property->house_count;
    
    // On initialise la chaîne avec 14 espaces
    memset(output, ' ', 14);
    output[14] = '\0'; // Assure que la chaîne est bien terminée

    // Si house_count == 5, on met un hôtel
    if (house_count == 5) {
        strcpy(output, "🏨"); // Copie l'emoji hôtel au début
    }
    // Si house_count est entre 1 et 4, on affiche des maisons
    else if (house_count >= 1 && house_count <= 4) {
        output[0] = '\0'; // Vide la chaîne avant d'ajouter les maisons
        for (int i = 0; i < house_count; i++) {
            strcat(output, "🏠"); // Concatène les emojis maison
        }
    }

    // La chaîne est complétée avec des espaces jusqu'à 14 caractères si nécessaire
    int len = strlen(output);
    for (int i = len; i < 14; i++) {
        output[i] = ' '; // Ajoute des espaces après les maisons ou l'hôtel
    }
    output[14] = '\0'; // Terminateur de chaîne

    return output;
}


void show_board(MonopolyCase **board)
{
	printf("            ║              ║              ║              ║              ║              ║              ║             ║ Compagnie de ║              ║               \n");
	printf(" Parc       ║   Avenue     ║    chance    ║  Boulevard   ║    Avenue    ║   Gare du    ║ Faubourg     ║  Place de   ║ distribution ║   Rue la     ║  Allez en     \n");
	printf("Gratuit     ║   Matignon   ║      🍀      ║  Malesherbes ║ Henri-Martin ║   Nord  🚅   ║ Saint-Honoré ║  la bourse  ║   des eaux   ║   fayette    ║  prison       \n");
	printf("%s║%s║%s║%s║%s║%s║%s║%s║%s║%s \n",
	house(board[20]),house(board[21]),house(board[22]),house(board[23]),house(board[24]),house(board[25]),house(board[26]),house(board[27]),house(board[28]),house(board[29]),house(board[30]));
	printf("════════════╬"BG_RED"══════════════"RESET"╩══════════════╩"BG_RED"══════════════"RESET"╩"BG_RED"══════════════"RESET"╩══════════════╩"BG_YELLOW"══════════════"RESET"╩"BG_YELLOW"═════════════"RESET"╩══════════════╩"BG_YELLOW"══════════════"RESET"╬═══════════════   \n");
	printf("place       "BG_ORANGE"║"RESET" \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  "BG_GREEN"║"RESET" Avenue		\n");
	printf("Pigalle     "BG_ORANGE"║"RESET" \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  "BG_GREEN"║"RESET" de breteuil	\n");
	printf("════════════╣ \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  ╠═══════════════	\n");
	printf("Boulevard   "BG_ORANGE"║"RESET" \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  "BG_GREEN"║"RESET" avenue		\n");
	printf("Saint-Michel"BG_ORANGE"║"RESET" \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  "BG_GREEN"║"RESET" Foch			\n");
	printf("════════════╣ \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  ╠══════════════ 	\n");
	printf("caisse de   ║ \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  ║ caisse de		\n");
	printf("communauté  ║ \t\t       	 	◘ Achetez. Vendez. Négociez. Gagnez ! ◘		 						 	  ║ communauté	\n");
	printf("════════════╣ \t\t\t       __       __   ______   __    __   ______   _______    ______   __    __      __             \t\t  ╠═══════════════	\n");    
	printf("avenue      "BG_ORANGE"║"RESET" \t\t\t      /  \\     /  | /      \\ /  \\  /  | /      \\ /       \\  /      \\ /  |  /  \\    /  |     \t\t\t  "BG_GREEN"║"RESET" Boulevard		\n");
	printf("Mozard      "BG_ORANGE"║"RESET" \t\t\t      $$  \\   /$$ |/$$$$$$  |$$  \\ $$ |/$$$$$$  |$$$$$$$  |/$$$$$$  |$$ |  $$  \\  /$$/          \t\t  "BG_GREEN"║"RESET" des capucines	\n");
	printf("════════════╣ \t\t\t      $$$  \\ /$$$ |$$ |  $$ |$$$  \\$$ |$$ |  $$ |$$ |__$$ |$$ |  $$ |$$ |   $$  \\/$$/           \t\t  ╠═══════════════	\n");
	printf("Gare de     ║ \t\t\t      $$$$  /$$$$ |$$ |  $$ |$$$$  $$ |$$ |  $$ |$$    $$/ $$ |  $$ |$$ |    $$  $$\\              \t\t  ║ gare 🚅	\n");
	printf("Lyon 🚅     ║ \t\t\t      $$ $$ $$/$$ |$$ |  $$ |$$ $$ $$ |$$ |  $$ |$$$$$$$/  $$ |  $$ |$$ |     $$$$/                \t\t  ║ Saint-Lazare	\n");
	printf("════════════╣ \t\t\t      $$ |$$$/ $$ |$$ \\__$$ |$$ |$$$$ |$$ \\__$$ |$$ |      $$ \\__$$ |$$ |_____ $$ |             \t\t  ╠═══════════════	\n"); 
	printf("Rue de      "BG_BRIGHT_MAGENTA"║"RESET" \t\t\t      $$ | $/  $$ |$$    $$/ $$ | $$$ |$$    $$/ $$ |      $$    $$/ $$       |$$ |                \t\t  ║    chance		\n");
	printf("Paradis     "BG_BRIGHT_MAGENTA"║"RESET" \t\t\t      $$/      $$/  $$$$$$/  $$/   $$/  $$$$$$/  $$/        $$$$$$/  $$$$$$$$/ $$/                 \t\t  ║	 🍀		\n");
	printf("════════════╣ \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t   \t\t  ╠═══════════════	\n");
	printf("Avenue de   "BG_BRIGHT_MAGENTA"║"RESET" \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t   \t\t  "BG_BLUE"║"RESET" Avenue des	\n");
	printf("Neuilly     "BG_BRIGHT_MAGENTA"║"RESET" \t\t\t  "DIM"     _                      _             _            _ _ _   _               _               "RESET"  \t\t  "BG_BLUE"║"RESET" champs-élysées\n");
	printf("════════════╣ \t\t\t  "DIM"    | |_ ___ _ __ _ __ ___ (_)_ __   __ _| |   ___  __| (_) |_(_) ___  _ __   | |              "RESET"  \t\t  ╠═══════════════	\n");
	printf("compagnie   ║ \t\t\t  "DIM"    | __/ _ \\ '__| '_ ` _ \\| | '_ \\ / _` | |  / _ \\/ _` | | __| |/ _ \\| '_ \\  | |        "RESET"  \t\t\t  ║ Taxe de   	\n");
	printf("électrique  ║ \t\t\t  "DIM"    | ||  __/ |  | | | | | | | | | | (_| | | |  __/ (_| | | |_| | (_) | | | | |_|              "RESET"  \t\t  ║ Luxe 💍    	\n");
	printf("════════════╣ \t\t\t  "DIM"     \\__\\___|_|  |_| |_| |_|_|_| |_|\\__,_|_|  \\___|\\__,_|_|\\__|_|\\___/|_| |_| (_)       "RESET"  \t\t\t  ╠═══════════════	\n");
	printf("Boulevard de"BG_BRIGHT_MAGENTA"║"RESET" \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  "BG_BLUE"║"RESET" Rue de    	\n");
	printf("la villette "BG_BRIGHT_MAGENTA"║"RESET" \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t  "BG_BLUE"║"RESET" la Paix   	\n");
	printf("════════════╬"BG_BRIGHT_CYAN"══════════════"RESET"╦"BG_BRIGHT_CYAN"══════════════"RESET"╦══════════════╦"BG_BRIGHT_CYAN"══════════════"RESET"╦══════════════╦══════════════╦"BG_BROWN"════════════"RESET"╦══════════════╦"BG_BROWN"═══════════════"RESET"╬═══════════════ \n");
    printf("%-14s║%-14s║%-14s║%-14s║%-14s║%-14s║%-14s║%-14s║%-14s║%-14s\n",
           house(board[10]), house(board[9]), house(board[8]), house(board[7]), 
           house(board[6]), house(board[5]), house(board[4]), house(board[3]), 
           house(board[2]), house(board[1]), house(board[0]));
	printf(" Simple     ║ Avenue de la ║  Rue de      ║    chance    ║ Rue de       ║ Gare  🚅     ║  Impôts sur  ║  Rue       ║  Caisse de   ║ Boulevard de  ║  Case         \n");
	printf(" visite     ║ République   ║  Courcelles  ║      🍀      ║ Vaugirard    ║ Montparnasse ║  le revenue  ║  Lecourbe  ║  Communauté  ║ Belleville    ║  Départ       \n");
}

void clear_terminal(void)
{
	system("cls");
}
/* OLD with " "
void show_board(MonopolyCase **board)
{
	printf("            ║              ║              ║              ║              ║              ║              ║             ║ Compagnie de ║              ║               \n");
	printf(" Parc       ║   Avenue     ║    chance    ║  Boulevard   ║    Avenue    ║   Gare du    ║ Faubourg     ║  Place de   ║ distribution ║   Rue la     ║  Allez en     \n");
	printf("Gratuit     ║   Matignon   ║      🍀      ║  Malesherbes ║ Henri-Martin ║   Nord  🚅   ║ Saint-Honoré ║  la bourse  ║   des eaux   ║   fayette    ║  prison       \n");
	printf("════════════╬"BG_RED"══════════════"RESET"╩══════════════╩"BG_RED"══════════════"RESET"╩"BG_RED"══════════════"RESET"╩══════════════╩"BG_YELLOW"══════════════"RESET"╩"BG_YELLOW"═════════════"RESET"╩══════════════╩"BG_YELLOW"══════════════"RESET"╬═══════════════   \n");
	printf("place       "BG_ORANGE"║"RESET" \t\t\t                                                                                                   \t\t  "BG_GREEN"║"RESET" Avenue		\n");
	printf("Pigalle     "BG_ORANGE"║"RESET" \t\t\t                                                                                                   \t\t  "BG_GREEN"║"RESET" de breteuil	\n");
	printf("════════════╣ \t\t\t                                                                                                   \t\t  ╠═══════════════	\n");
	printf("Boulevard   "BG_ORANGE"║"RESET" \t\t\t                                                                                                   \t\t  "BG_GREEN"║"RESET" avenue		\n");
	printf("Saint-Michel"BG_ORANGE"║"RESET" \t\t\t                                                                                                   \t\t  "BG_GREEN"║"RESET" Foch			\n");
	printf("════════════╣ \t\t\t                                                                                                   \t\t  ╠══════════════ 	\n");
	printf("caisse de   ║ \t\t\t                                                                                                   \t\t  ║ caisse de		\n");
	printf("communauté  ║ \t\t       	 	◘ Achetez. Vendez. Négociez. Gagnez ! ◘		 						 	  ║ communauté	\n");
	printf("════════════╣ \t\t\t       __       __   ______   __    __   ______   _______    ______   __    __      __             \t\t  ╠═══════════════	\n");    
	printf("avenue      "BG_ORANGE"║"RESET" \t\t\t      /  \\     /  | /      \\ /  \\  /  | /      \\ /       \\  /      \\ /  |  /  \\    /  |     \t\t\t  "BG_GREEN"║"RESET" Boulevard		\n");
	printf("Mozard      "BG_ORANGE"║"RESET" \t\t\t      $$  \\   /$$ |/$$$$$$  |$$  \\ $$ |/$$$$$$  |$$$$$$$  |/$$$$$$  |$$ |  $$  \\  /$$/          \t\t  "BG_GREEN"║"RESET" des capucines	\n");
	printf("════════════╣ \t\t\t      $$$  \\ /$$$ |$$ |  $$ |$$$  \\$$ |$$ |  $$ |$$ |__$$ |$$ |  $$ |$$ |   $$  \\/$$/           \t\t  ╠═══════════════	\n");
	printf("Gare de     ║ \t\t\t      $$$$  /$$$$ |$$ |  $$ |$$$$  $$ |$$ |  $$ |$$    $$/ $$ |  $$ |$$ |    $$  $$\\              \t\t  ║ gare 🚅	\n");
	printf("Lyon 🚅     ║ \t\t\t      $$ $$ $$/$$ |$$ |  $$ |$$ $$ $$ |$$ |  $$ |$$$$$$$/  $$ |  $$ |$$ |     $$$$/                \t\t  ║ Saint-Lazare	\n");
	printf("════════════╣ \t\t\t      $$ |$$$/ $$ |$$ \\__$$ |$$ |$$$$ |$$ \\__$$ |$$ |      $$ \\__$$ |$$ |_____ $$ |             \t\t  ╠═══════════════	\n"); 
	printf("Rue de      "BG_BRIGHT_MAGENTA"║"RESET" \t\t\t      $$ | $/  $$ |$$    $$/ $$ | $$$ |$$    $$/ $$ |      $$    $$/ $$       |$$ |                \t\t  ║    chance		\n");
	printf("Paradis     "BG_BRIGHT_MAGENTA"║"RESET" \t\t\t      $$/      $$/  $$$$$$/  $$/   $$/  $$$$$$/  $$/        $$$$$$/  $$$$$$$$/ $$/                 \t\t  ║	 🍀		\n");
	printf("════════════╣ \t\t\t                                                                                                   \t\t  ╠═══════════════	\n");
	printf("Avenue de   "BG_BRIGHT_MAGENTA"║"RESET" \t\t\t                                                                                                   \t\t  "BG_BLUE"║"RESET" Avenue des	\n");
	printf("Neuilly     "BG_BRIGHT_MAGENTA"║"RESET" \t\t\t  "DIM"     _                      _             _            _ _ _   _               _               "RESET"  \t\t  "BG_BLUE"║"RESET" champs-élysées\n");
	printf("════════════╣ \t\t\t  "DIM"    | |_ ___ _ __ _ __ ___ (_)_ __   __ _| |   ___  __| (_) |_(_) ___  _ __   | |              "RESET"  \t\t  ╠═══════════════	\n");
	printf("compagnie   ║ \t\t\t  "DIM"    | __/ _ \\ '__| '_ ` _ \\| | '_ \\ / _` | |  / _ \\/ _` | | __| |/ _ \\| '_ \\  | |        "RESET"  \t\t\t  ║ Taxe de   	\n");
	printf("électrique  ║ \t\t\t  "DIM"    | ||  __/ |  | | | | | | | | | | (_| | | |  __/ (_| | | |_| | (_) | | | | |_|              "RESET"  \t\t  ║ Luxe 💍    	\n");
	printf("════════════╣ \t\t\t  "DIM"     \\__\\___|_|  |_| |_| |_|_|_| |_|\\__,_|_|  \\___|\\__,_|_|\\__|_|\\___/|_| |_| (_)       "RESET"  \t\t\t  ╠═══════════════	\n");
	printf("Boulevard de"BG_BRIGHT_MAGENTA"║"RESET" \t\t\t                                                                                                   \t\t  "BG_BLUE"║"RESET" Rue de    	\n");
	printf("la villette "BG_BRIGHT_MAGENTA"║"RESET" \t\t\t                                                                                                   \t\t  "BG_BLUE"║"RESET" la Paix   	\n");
	printf("════════════╬"BG_BRIGHT_CYAN"══════════════"RESET"╦"BG_BRIGHT_CYAN"══════════════"RESET"╦══════════════╦"BG_BRIGHT_CYAN"══════════════"RESET"╦══════════════╦══════════════╦"BG_BROWN"════════════"RESET"╦══════════════╦"BG_BROWN"═══════════════"RESET"╬═══════════════ \n");
	printf(" Simple     ║ Avenue de la ║  Rue de      ║    chance    ║ Rue de       ║ Gare  🚅     ║  Impôts sur  ║  Rue       ║  Caisse de   ║ Boulevard de  ║  Case         \n");
	printf(" visite     ║ République   ║  Courcelles  ║      🍀      ║ Vaugirard    ║ Montparnasse ║  le revenue  ║  Lecourbe  ║  Communauté  ║ Belleville    ║  Départ       \n");
}
*/