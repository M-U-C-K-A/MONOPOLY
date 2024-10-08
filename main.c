#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <time.h>

#include "monopoly.h"

typedef struct Player {
	char name[50];
	char color[10]; // Couleur ANSI choisie
	int money;
	int position; // Position sur le plateau (0-39)
	int in_jail;
} Player;

// Fonction pour initialiser un joueur
Player create_player(int player_number) {
	Player player;
	printf("Nom du joueur %d: ", player_number + 1);
	scanf("%s", player.name);
	
	// Sélection de la couleur du joueur
	printf("Choisissez une couleur pour %s: (1) Rouge, (2) Vert, (3) Bleu, (4) Jaune, (5) Magenta, (6) Cyan\n", player.name);
	int color_choice;
	scanf("%d", &color_choice);
	
	switch(color_choice) {
		case 1: strcpy(player.color, RED); break;
		case 2: strcpy(player.color, GREEN); break;
		case 3: strcpy(player.color, BLUE); break;
		case 4: strcpy(player.color, YELLOW); break;
		case 5: strcpy(player.color, MAGENTA); break;
		case 6: strcpy(player.color, CYAN); break;
		default: strcpy(player.color, WHITE); break; // Blanc par défaut
	}

	player.money = 1500; // Montant de départ
	player.position = 0; // Commence sur la case "Départ"
	player.in_jail = 0;  // Par défaut, pas en prison

	return player;
}

// Fonction pour lancer les dés
int roll_dice()
{
	return (rand() % 6 + 1) + (rand() % 6 + 1); // Somme de 2 dés (1-6)
}

// Fonction pour afficher le menu principal
void display_menu() {
	printf("\nMenu:\n");
	printf("1. Lancer les dés\n");
	printf("2. Voir les cartes\n");
	printf("3. Paramètres\n");
	printf("4. Règles\n");
	printf("5. Quitter le jeu\n");
	printf("Choisissez une option: ");
}

void player_card(Player *players, int player_count)
{

	char *words[] = {
		"Départ", 
		"Boulevard de Belleville", 
		"Caisse de Communauté (1)", 
		"Impôts sur le revenue", 
		"Gare Montparnasse", 
		"Chance (1)", 
		"Rue de Courcelles", 
		"Avenue de la République", 
		"Simple visite / prison", 
		"Boulevard de la vilette",
		"Compagnie électrique",
		"Avenue de Neuilly",
		"Rue de Paradis",
		"Gare de Lyon",
		"Avenue Mozard",
		"Caisse de Communauté (2)",
		"Boulevard Saint-Michel",
		"Place Pigalle",
		"Parc Gratuit",
		"Avenue Matignon",
		"Chance (2)",
		"Boulevard Malesherbes",
		"Avenue Henri-Martin",
		"Gare du Nord",
		"Faubourg Saint-Honoré",
		"Place de la Bourse",
		"Compagnie des eaux",
		"Rue la Fayette",
		"Allez en prison",
		"Avenue de Breteuil",
		"Avenue Foch",
		"Caisse de Communauté (3)",
		"Boulevard des Capucines",
		"Gare Saint-Lazare",
		"Chance (3)",
		"Avenue des Champs-Elysees",
		"Taxe de Luxe",
		"Rue de la Paix"
	};
	for (int i = 0; i < player_count; i++) {
		Player *p = &players[i];
		char name[50];
		strncpy(name, p->name, 10);
		char color[10];
		strncpy(color, p->color, 10);
		int money = p->money;
		int position = p->position;
		int in_jail = p->in_jail;
		char position_str[26];
		strncpy(position_str, words[position], 25);

		printf(color);
		printf(DIM"╔═════════════════════════════════════════════╗\n");
		printf("║"RESET"%s  %-12s              %s%s"           DIM "║\n",
		       color, name, in_jail ? RED"PLAYER IN JAIL ! " : "                 ",color);
		printf("║"RESET"%s  $%-10d  case:%-25s "DIM"║\n", color, money, position_str);
		printf("╚═════════════════════════════════════════════╝\n");
		printf(RESET);
	}
}


int main(void)
{
	SetConsoleOutputCP(CP_UTF8);
	srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

	// Initialiser le plateau
	MonopolyCase **board = init_board();

	// Initialiser les joueurs
	int player_count;
	printf("Combien de joueurs ? ");
	scanf("%d", &player_count);

	Player players[player_count];
	for (int i = 0; i < player_count && i < 8; i++) {
		players[i] = create_player(i);
	}

	// Boucle de jeu principale
	int running = 1;
	int current_player = 0;
	
	while (running) {
		clear_terminal();
		show_board(board);
		player_card(players, player_count);
		Player *player = &players[current_player];
		printf("%s%s%s, c'est votre tour !\n", player->color, player->name, RESET);

		display_menu();

		int choice;
		scanf("%d", &choice);

		switch (choice) {
			case 1: {
				// Lancer les dés
				int dice_result = roll_dice();
				printf("Vous avez lancé un %d\n", dice_result);

				// Mettre à jour la position du joueur
				player->position = (player->position + dice_result) % 40;
				printf("Vous êtes maintenant sur la case %d: %s\n", player->position, board[player->position]->name);
				break;
			}

			case 2: {
				// Voir une carte ou une zone
				int card_choice;
				printf("1. Voir une carte\n2. Voir une zone\nchoix (1-2): ");
				scanf("%d", &card_choice);
				if (card_choice == 1) {
					// Voir une carte
					int card_index;
					printf("Quelle carte souhaitez-vous voir ? (0-39) ");
					scanf("%d", &card_index);
					show_card(board, card_index);
				} else if (card_choice == 2) {
					// Voir une zone
					int zone_index;
					clear_terminal();
					printf(BOLD UNDERLINE"Quelle zone souhaitez-vous voir ? (0-9)\n"RESET);
					printf(BROWN"0 = Marron\n");
					printf(BRIGHT_CYAN"1 = bleu ciel\n");
					printf(MAGENTA"2 = rose\n");
					printf(ORANGE"3 = orange\n");
					printf(RED"4 = rouge\n");
					printf(YELLOW"5 = jaune\n");
					printf(GREEN"6 = vert\n");
					printf(BLUE"7 = bleu foncé\n");
					printf(BEIGE"8 = compagnies\n");
					printf(LIGHT_GRAY"9 = gares\n"RESET);
					scanf("%d", &zone_index);
					show_color_card(board, zone_index);
				}
				break;
			}
			case 3: {
				// Paramètres
				printf("Modifier les paramètres:\n");
				printf("1. Changer l'ordre des joueurs\n");
				printf("2. Modifier les montants d'argent\n");
				printf("3. Revenir au menu principal\n");
				int setting_choice;
				scanf("%d", &setting_choice);
				// Ajout de réglages selon les besoins
				if (setting_choice == 1) {
					printf("Fonctionnalité à implémenter...\n");
				} else if (setting_choice == 2) {
					printf("Modifier l'argent de quel joueur ? ");
					int player_num;
					scanf("%d", &player_num);
					printf("Nouveau montant pour %s: ", players[player_num - 1].name);
					scanf("%d", &players[player_num - 1].money);
					printf("Montant modifié avec succès.\n");
				}
				break;
			}
			case 4: 
			{
				clear_terminal();
				show_rules();
    			break;
			}
			case 5: {
				// Quitter le jeu
				running = 0;
				break;
			}

			default:
				printf("Option non valide. Veuillez choisir à nouveau.\n");
				break;
		}

		// Passer au joueur suivant
		current_player = (current_player + 1) % player_count;
		printf("\nAppuyez sur Entrée pour continuer...\n");
		getchar(); 
		getchar(); // Pause
	}

	// Libérer la mémoire du plateau
	for (int i = 0; i < 40; i++)
		free(board[i]);
	free(board);

	return 0;
}
