#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>	// only exists on Windows (for the accents in the console)
#endif

#include "monopoly.h"



/**
 * Crée un joueur avec un nom et une couleur.
 *
 * Demande le nom et la couleur du joueur en entrée.
 * Le joueur commence avec 1500 euros et est placé sur la case "Départ".
 * Le joueur n'est pas en prison.
 *
 * @param player_number Numéro du joueur (1, 2, 3, ...)
 * @return Joueur créé
 */
Player create_player(int player_number)
{
	Player player;
	printf("Nom du joueur %d: ", player_number + 1);
	scanf("%49s", player.name);		// 49 max so we don't go over name[50]

	printf("Choisissez une couleur pour %s: ", player.name);
	printf(RED"(1) Rouge,"GREEN" (2) Vert,"BLUE" (3) Bleu,"YELLOW" (4) Jaune,"MAGENTA" (5) Magenta,"CYAN" (6) Cyan\n"RESET);
	int color_choice = read_number();
	
	switch(color_choice) {
		case 1: strcpy(player.color, RED); break;		// if case 1 is chosen, it will be Red
		case 2: strcpy(player.color, GREEN); break;		// if case 2 is chosen, it will be Green
		case 3: strcpy(player.color, BLUE); break;		// if case 3 is chosen, it will be Blue
		case 4: strcpy(player.color, YELLOW); break;	// if case 4 is chosen, it will be Yellow
		case 5: strcpy(player.color, MAGENTA); break;	// if case 5 is chosen, it will be Magenta
		case 6: strcpy(player.color, CYAN); break;		// if case 6 is chosen, it will be Cyan
		default: strcpy(player.color, WHITE); break; 	// by default, it will be White
	}

	player.money = 1500; // Montant de départ
	player.position = 0; // Commence sur la case "Départ"
	player.in_jail = 0;  // Par défaut, pas en prison
	player.bankrupt = 0; // Le joueur est encore en jeu

	return player;
}




void player_card(Player *players, int player_count)
{
	char *places[] = {
		"Depart", 
		"Boulevard de Belleville", 
		"Caisse de Communaute (1)",
		"Rue Lecourbe",
		"Impots sur le revenue",
		"Gare Montparnasse",
		"Rue de Vaugirard",
		"Chance (1)",
		"Rue de Courcelles",
		"Avenue de la Republique", 
		"Simple visite / prison", 
		"Boulevard de la vilette",
		"Compagnie electrique",
		"Avenue de Neuilly",
		"Rue de Paradis",
		"Gare de Lyon",
		"Avenue Mozard",
		"Caisse de Communaute (2)",
		"Boulevard Saint-Michel",
		"Place Pigalle",
		"Parc Gratuit",
		"Avenue Matignon",
		"Chance (2)",
		"Boulevard Malesherbes",
		"Avenue Henri-Martin",
		"Gare du Nord",
		"Faubourg Saint-Honore",
		"Place de la Bourse",
		"Compagnie des eaux",
		"Rue la Fayette",
		"Allez en prison",
		"Avenue de Breteuil",
		"Avenue Foch",
		"Caisse de Communaute (3)",
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
		name[10] = '\0';	// strncpy doesn't add the \0 when the name is too long
		char color[30];
		strcpy(color, p->color);
		int money = p->money;
		int position = p->position;
		int in_jail = p->in_jail;
		char position_str[27];
		strncpy(position_str, places[position], 27);

		char *status = "                 ";
		if (p->bankrupt)
			status = RED"PLAYER BANKRUPT !";
		else if (in_jail)
			status = RED"PLAYER IN JAIL ! ";

		printf("%s", color);
		printf("\n");
		printf( DIM "╔════════════════════════════════════════════════╗\n");
		printf("║"RESET"%s  %-12s              %s%s" DIM "   ║\n",
		       color, name, status, color);
		printf("║"RESET"%s  $%-10d  case:%-27s "DIM"║\n", color, money, position_str);
		printf("╚════════════════════════════════════════════════╝\n");
		printf(RESET);
	}
}

/**
 * Calcule le loyer a payer sur une case qui appartient a un joueur.
 *
 * - Gare : 25$, 50$, 100$ ou 200$ selon le nombre de gares du proprietaire.
 * - Compagnie : 4 x les des (10 x les des si il a les deux compagnies).
 * - Terrain : le loyer depend du nombre de maisons. Sans maison, le loyer
 *   est double si le proprietaire a toute la couleur.
 */
int calcul_loyer(MonopolyCase **board, int index, int dice_result)
{
	MonopolyCase *c = board[index];

	if (index % 10 == 5) {	// Les gares sont sur les cases 5, 15, 25 et 35
		int loyer = 25;
		for (int i = 5; i < 40; i += 10) {
			if (i != index && board[i]->owner_id == c->owner_id)
				loyer = loyer * 2;
		}
		return loyer;
	}
	if (index == 12 || index == 28) {	// Les compagnies
		if (board[12]->owner_id == board[28]->owner_id)
			return dice_result * 10;
		return dice_result * 4;
	}
	switch (c->house_count) {
		case 0:
			if (own_color(board, c->owner_id, index))
				return c->rent * 2;
			return c->rent;
		case 1: return c->rent_1_house;
		case 2: return c->rent_2_houses;
		case 3: return c->rent_3_houses;
		case 4: return c->rent_4_houses;
		default: return c->rent_hotel;
	}
}

/**
 * Tire une carte Chance ou Caisse de Communaute au hasard.
 */
void tirer_carte(Player *player)
{
	int carte = rand() % 6;

	printf(BOLD "Vous tirez une carte : " RESET);
	switch (carte) {
		case 0:
			printf("La banque vous verse un dividende de 50$.\n");
			player->money += 50;
			break;
		case 1:
			printf("Payez la note du medecin : 50$.\n");
			player->money -= 50;
			break;
		case 2:
			printf("Avancez jusqu'a la case Depart, recevez 200$.\n");
			player->position = 0;
			player->money += 200;
			break;
		case 3:
			printf("Allez en prison !\n");
			player->position = 10;
			player->in_jail = 1;
			break;
		case 4:
			printf("Vous heritez de 100$.\n");
			player->money += 100;
			break;
		case 5:
			printf("Payez vos frais de scolarite : 150$.\n");
			player->money -= 150;
			break;
	}
}

/**
 * Ce qui se passe quand un joueur arrive sur une case : acheter, payer un
 * loyer, payer une taxe, tirer une carte ou aller en prison.
 */
void arrive_sur_case(MonopolyCase **board, Player *players, int current_player, int dice_result)
{
	Player *player = &players[current_player];
	MonopolyCase *c = board[player->position];

	if (player->position == 30) {	// Allez en prison
		printf(RED "Allez en prison !\n" RESET);
		player->position = 10;
		player->in_jail = 1;
	}
	else if (player->position == 4) {	// Impots sur le revenu
		printf("Vous payez 200$ d'impots.\n");
		player->money -= 200;
	}
	else if (player->position == 38) {	// Taxe de luxe
		printf("Vous payez 100$ de taxe de luxe.\n");
		player->money -= 100;
	}
	else if (player->position == 2 || player->position == 7 || player->position == 17
		|| player->position == 22 || player->position == 33 || player->position == 36) {
		// Chance (7, 22, 36) et Caisse de Communaute (2, 17, 33)
		tirer_carte(player);
	}
	else if (c->price > 0) {	// Une case qu'on peut acheter
		if (c->owner_id == -1) {
			if (player->money >= c->price) {
				printf("%s n'appartient a personne. L'acheter pour %d$ ? (1 = oui, 0 = non) ", c->name, c->price);
				if (read_number() == 1) {
					player->money -= c->price;
					c->owner_id = current_player;
					printf(GREEN "Vous avez achete %s !\n" RESET, c->name);
				}
			}
			else
				printf("Vous n'avez pas assez d'argent pour acheter %s.\n", c->name);
		}
		else if (c->owner_id != current_player) {
			int loyer = calcul_loyer(board, player->position, dice_result);
			printf(RED "%s appartient a %s : vous payez %d$ de loyer.\n" RESET, c->name, players[c->owner_id].name, loyer);
			player->money -= loyer;
			players[c->owner_id].money += loyer;
		}
	}
}


int main(void)
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
#endif
	srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

	// Initialiser le plateau
	MonopolyCase **board = init_board();

	// Initialiser les joueurs (entre 2 et 8)
	int player_count = 0;
	while (player_count < 2 || player_count > 8) {
		printf("Combien de joueurs ? (2-8) ");
		player_count = read_number();
	}

	Player players[player_count];
	for (int i = 0; i < player_count; i++) {
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

		int choice = read_number();

		switch (choice) {
			case 1: {
				// Lancer les dés
				int de1 = roll_dice();
				int de2 = roll_dice();
				int dice_result = de1 + de2;
				int etait_en_prison = player->in_jail;
				printf("Vous avez lancé %d + %d = %d\n", de1, de2, dice_result);

				// En prison : il faut faire un double, ou payer 50$ au 3eme tour
				if (player->in_jail > 0) {
					if (de1 == de2) {
						printf("Double ! Vous sortez de prison.\n");
						player->in_jail = 0;
					} else if (player->in_jail == 3) {
						printf("3eme tour en prison : vous payez 50$ et vous sortez.\n");
						player->money -= 50;
						player->in_jail = 0;
					} else {
						printf("Pas de double, vous restez en prison.\n");
						player->in_jail++;
					}
				}

				if (player->in_jail == 0) {
					// Mettre à jour la position du joueur
					player->position = player->position + dice_result;
					if (player->position >= 40) {	// Il a fait le tour du plateau
						player->position = player->position - 40;
						player->money += 200;
						printf(GREEN "Vous passez par la case Depart : +200$\n" RESET);
					}
					printf("Vous êtes maintenant sur la case %d: %s\n", player->position, board[player->position]->name);
					arrive_sur_case(board, players, current_player, dice_result);
				}

				// Plus d'argent : le joueur a perdu, ses cases retournent a la banque
				if (player->money < 0) {
					printf(RED "%s n'a plus d'argent : il a perdu !\n" RESET, player->name);
					player->bankrupt = 1;
					for (int i = 0; i < 40; i++) {
						if (board[i]->owner_id == current_player) {
							board[i]->owner_id = -1;
							board[i]->house_count = 0;
						}
					}
				}

				// Passer au joueur suivant, sauf s'il a fait un double (il rejoue)
				if (de1 != de2 || etait_en_prison || player->in_jail || player->bankrupt) {
					do {
						current_player = (current_player + 1) % player_count;
					} while (players[current_player].bankrupt);
				}
				break;
			}

			case 2: {
				// Voir une carte ou une zone
				int card_choice;
				printf("1. Voir une carte\n2. Voir une zone\nchoix (1-2): ");
				card_choice = read_number();
				if (card_choice == 1) {
					// Voir une carte
					int card_index;
					printf("Quelle carte souhaitez-vous voir ? (0-39) ");
					card_index = read_number();
					show_card(board, card_index);
					if (card_index >= 0 && card_index < 40 && board[card_index]->owner_id >= 0)
						printf("Proprietaire : %s\n", players[board[card_index]->owner_id].name);
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
					zone_index = read_number();
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
				int setting_choice = read_number();
				// Ajout de réglages selon les besoins
				if (setting_choice == 1) {
					printf("Fonctionnalité à implémenter...\n");
				} else if (setting_choice == 2) {
					printf("Modifier l'argent de quel joueur ? (1-%d) ", player_count);
					int player_num = read_number();
					if (player_num < 1 || player_num > player_count) {
						printf("Ce joueur n'existe pas.\n");
					} else {
						printf("Nouveau montant pour %s: ", players[player_num - 1].name);
						players[player_num - 1].money = read_number();
						printf("Montant modifié avec succès.\n");
					}
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
			case 6: {
				// Construire une maison (5 maisons = un hôtel)
				printf("Sur quelle case voulez-vous construire ? (0-39) ");
				int index = read_number();
				if (index < 0 || index > 39 || board[index]->owner_id != current_player)
					printf("Cette case ne vous appartient pas.\n");
				else if (!own_color(board, current_player, index))
					printf("Il faut avoir tous les terrains de la couleur pour construire.\n");
				else if (board[index]->house_count == 5)
					printf("Il y a deja un hotel sur cette case.\n");
				else if (player->money < board[index]->house_price)
					printf("Vous n'avez pas assez d'argent (%d$).\n", board[index]->house_price);
				else {
					player->money -= board[index]->house_price;
					board[index]->house_count++;
					if (board[index]->house_count == 5)
						printf(GREEN "Hotel construit sur %s !\n" RESET, board[index]->name);
					else
						printf(GREEN "Maison construite sur %s (%d maison(s)).\n" RESET, board[index]->name, board[index]->house_count);
				}
				break;
			}

			default:
				printf("Option non valide. Veuillez choisir à nouveau.\n");
				break;
		}

		// Fin de la partie quand il ne reste qu'un seul joueur
		int players_left = 0;
		for (int i = 0; i < player_count; i++) {
			if (!players[i].bankrupt)
				players_left++;
		}
		if (players_left == 1) {
			printf(BOLD GREEN "\n%s a gagne la partie !\n" RESET, players[current_player].name);
			running = 0;
		}

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
