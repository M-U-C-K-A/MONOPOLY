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
	
	board[0] = create_case(0, "no house", 0, 0, 0, 0, 0, 0, 0, 0,0 ,0);
	board[1] = create_case(1, "one house", 0, 0, 0, 0, 0, 0, 0, 0, 0 ,1);
	board[2] = create_case(2, "two house", 0, 0, 0, 0, 0, 0, 0, 0, 0 ,2);
	board[3] = create_case(3, "tree house", 0, 0, 0, 0, 0, 0, 0, 0, 0 ,3);
	board[4] = create_case(4, "four house", 0, 0, 0, 0, 0, 0, 0, 0, 0 ,4);
	board[5] = create_case(5, "five house", 0, 0, 0, 0, 0, 0, 0, 0, 0 ,5);

	return board;
}

// Fonction check_house
const char* check_house(MonopolyCase* case_ptr, int line)
{
    static char output[10];

    switch (case_ptr->house_count) {
    case 0:
        return "  ";
    case 1:
        return line == 0 ? "🏠" : "";
    case 2:
        return "🏠";
    case 3:
        return line == 0 ? "🏠🏠" : "🏠";
    case 4:
        return "🏠🏠";
    case 5:
        return line == 0 ? "🏨" : "";
    }
    return output;
}

void show_board(MonopolyCase **board)
{
	printf("no house : \n");
	printf("|%-2s| \n",check_house(board[0],0));
	printf("|%-2s| \n",check_house(board[0],1));
	printf("one house : \n");
	printf("|%-2s| \n",check_house(board[1],0));
	printf("|%-2s| \n",check_house(board[1],1));
	printf("two house : \n");
	printf("|%-2s| \n",check_house(board[2],0));
	printf("|%-2s| \n",check_house(board[2],1));
	printf("tree house : \n");
	printf("|%-2s| \n",check_house(board[3],0));
	printf("|%-2s| \n",check_house(board[3],1));
	printf("four house : \n");
	printf("|%-2s| \n",check_house(board[4],0));
	printf("|%-2s| \n",check_house(board[4],1));
	printf("five house : \n");
	printf("|%-2s| \n",check_house(board[5],0));
	printf("|%-2s| \n",check_house(board[5],1));


	printf("\n\n");
/*
	printf("            ║              ║              ║              ║              ║              ║              ║             ║ Compagnie de ║              ║               \n");
	printf(" Parc       ║   Avenue     ║    chance    ║  Boulevard   ║    Avenue    ║   Gare du    ║ Faubourg     ║  Place de   ║ distribution ║   Rue la     ║  Allez en     \n");
	printf("Gratuit     ║   Matignon   ║      🍀      ║  Malesherbes ║ Henri-Martin ║   Nord  🚅   ║ Saint-Honoré ║  la bourse  ║   des eaux   ║   fayette    ║  prison       \n");
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
	printf(" Simple     ║ Avenue de la ║  Rue de      ║    chance    ║ Rue de       ║ Gare  🚅     ║  Impôts sur  ║  Rue       ║  Caisse de   ║ Boulevard de  ║  Case         \n");
	printf(" visite     ║ République   ║  Courcelles  ║      🍀      ║ Vaugirard    ║ Montparnasse ║  le revenue  ║  Lecourbe  ║  Communauté  ║ Belleville    ║  Départ       \n");
	*/
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


void	show_rules(void)
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