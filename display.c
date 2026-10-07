#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "monopoly.h"

// Names written on the board: 10 characters max, it's the width of a case
char *short_names[40] = {
	"DÉPART", "Belleville", "Caisse", "Lecourbe", "Impôts", "Montparn.", "Vaugirard", "Chance", "Courcelles", "République",
	"PRISON", "Villette", "Cie élec.", "Neuilly", "Paradis", "Gare Lyon", "Mozart", "Caisse", "St-Michel", "Pigalle",
	"PARC", "Matignon", "Chance", "Malesherb.", "H.-Martin", "Gare Nord", "St-Honoré", "Bourse", "Cie eaux", "La Fayette",
	"ALLEZ EN", "Breteuil", "Foch", "Caisse", "Capucines", "St-Lazare", "Chance", "Champs-Él.", "Taxe luxe", "Paix"
};

// Second line of the cases that can't be bought
char *special_infos[40] = {
	"+200$", "", "", "", "-200$", "", "", "", "", "",
	"", "", "", "", "", "", "", "", "", "",
	"GRATUIT", "", "", "", "", "", "", "", "", "",
	"PRISON", "", "", "", "", "", "", "", "-100$", ""
};

// The MONOPOLY logo in the middle of the board
char *title[6] = {
	"███╗   ███╗ ██████╗ ███╗   ██╗ ██████╗ ██████╗  ██████╗ ██╗     ██╗   ██╗",
	"████╗ ████║██╔═══██╗████╗  ██║██╔═══██╗██╔══██╗██╔═══██╗██║     ╚██╗ ██╔╝",
	"██╔████╔██║██║   ██║██╔██╗ ██║██║   ██║██████╔╝██║   ██║██║      ╚████╔╝ ",
	"██║╚██╔╝██║██║   ██║██║╚██╗██║██║   ██║██╔═══╝ ██║   ██║██║       ╚██╔╝  ",
	"██║ ╚═╝ ██║╚██████╔╝██║ ╚████║╚██████╔╝██║     ╚██████╔╝███████╗   ██║   ",
	"╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚═╝      ╚═════╝ ╚══════╝   ╚═╝   "
};

/**
 * Colors of each group: 0 = brown ... 7 = dark blue, 8 = companies, 9 = stations.
 */
char *group_color(int group)		// text color (borders of the cards)
{
	char *colors[10] = { BROWN, BRIGHT_CYAN, BRIGHT_MAGENTA, ORANGE, RED, YELLOW, GREEN, BLUE, LIGHT_GRAY, LIGHT_GRAY };

	if (group < 0 || group > 9)
		return DIM;
	return colors[group];
}

char *group_background(int group)	// background color (the color band)
{
	char *backgrounds[10] = { BG_BROWN, BG_BRIGHT_CYAN, BG_BRIGHT_MAGENTA, BG_ORANGE, BG_RED, BG_YELLOW, BG_GREEN, BG_BLUE, BG_LIGHT_GRAY, BG_LIGHT_GRAY };

	return backgrounds[group];
}

char *group_text(int group)			// text written on the color band: black on light colors, white on dark ones
{
	char *texts[10] = { BRIGHT_WHITE, BLACK, BLACK, BLACK, BRIGHT_WHITE, BLACK, BRIGHT_WHITE, BRIGHT_WHITE, BLACK, BLACK };

	return texts[group];
}

/* ************************************************************************** */
/*                                 THE BOARD                                  */
/* ************************************************************************** */

/**
 * First line of a case: its name, on the color band for the properties.
 */
void print_case_name(MonopolyCase *c)
{
	if (c->group >= 0)
		printf("%s%s" BOLD, group_background(c->group), group_text(c->group));
	else
		printf(BOLD);
	print_centered(short_names[c->index], 10);
	printf(RESET);
}

/**
 * Second line of a case: the price if nobody owns it, the houses (in the color
 * of the owner) if somebody does, and on the right the players on the case.
 */
void print_case_status(MonopolyCase *c, Player *players, int player_count)
{
	char info[30] = "";
	char *style = DIM;
	int here = 0;

	for (int i = 0; i < player_count; i++)
	{
		if (!players[i].bankrupt && players[i].position == c->index && here < 4)
			here++;
	}

	if (c->price > 0 && c->owner_id == -1)		// for sale: the price
		sprintf(info, "%d$", c->price);
	else if (c->price > 0)						// bought: the houses, in the color of the owner
	{
		style = players[c->owner_id].color;
		if (c->house_count == 5)
			strcpy(info, "HÔTEL");
		else if (c->house_count == 0)
			strcpy(info, "●");
		else
		{
			for (int h = 0; h < c->house_count; h++)
				strcat(info, "▪");
		}
	}
	else										// Départ, taxes, prison...
	{
		strcpy(info, special_infos[c->index]);
		if (c->index % 10 == 0)					// the 4 corners
			style = BOLD;
	}

	if (here > 10 - visible_length(info))
		here = 10 - visible_length(info);
	printf("%s", style);
	print_centered(info, 10 - here);
	printf(RESET);

	// the players: their number, in their color
	int shown = 0;
	for (int i = 0; i < player_count && shown < here; i++)
	{
		if (!players[i].bankrupt && players[i].position == c->index)
		{
			printf("%s\033[7m%d" RESET, players[i].color, i + 1);
			shown++;
		}
	}
}

void print_case(MonopolyCase **board, Player *players, int player_count, int index, int line)
{
	if (line == 0)
		print_case_name(board[index]);
	else
		print_case_status(board[index], players, player_count);
}

/**
 * One line of a player in the middle of the board.
 */
void print_player_line(MonopolyCase **board, Player *players, int i, int current_player)
{
	Player *p = &players[i];
	char name[13];
	char *status = "";

	strncpy(name, p->name, 12);
	name[12] = '\0';
	if (p->bankrupt)
		status = "a perdu";
	else if (p->in_jail)
		status = "en prison";

	printf("            ");												// 12 columns
	if (i == current_player)
		printf(BOLD "▶ " RESET);											// 2
	else
		printf("  ");
	printf("%s\033[7m%d" RESET "  ", p->color, i + 1);					// 3
	printf("%s" BOLD, p->color);
	print_padded(name, 14);												// 14
	printf(RESET "%6d $    ", p->money);								// 12
	print_padded(board[p->position]->name, 26);							// 26
	printf(RED);
	print_padded(status, 11);											// 11
	printf(RESET);
	print_padded("", 18);												// 18 -> 98 in total
}

/**
 * One line (out of 26) of the middle of the board: the logo, then the players.
 */
void print_center(MonopolyCase **board, Player *players, int player_count, int current_player, int line)
{
	if (line >= 4 && line <= 9)
	{
		printf(RED BOLD);
		print_centered(title[line - 4], 98);
		printf(RESET);
	}
	else if (line == 11)
	{
		printf(DIM);
		print_centered("Achetez · Vendez · Négociez · Gagnez !", 98);
		printf(RESET);
	}
	else if (line >= 14 && line < 14 + player_count)
		print_player_line(board, players, line - 14, current_player);
	else if (line == 15 + player_count)
	{
		printf(DIM);
		print_centered("●  acheté       ▪  maison       HÔTEL  hôtel", 98);
		printf(RESET);
	}
	else
		print_padded("", 98);
}

/**
 * Print the Monopoly board.
 *
 * The board is a grid of 11 x 11 cases of 10 characters: the cases 20 to 30 on
 * the top, 19 to 11 on the left, 31 to 39 on the right and 10 to 0 on the
 * bottom. Each case has 2 lines: its name, then the price / houses and the
 * players. The middle shows the logo and the players.
 *
 * @param board          The Monopoly board.
 * @param players        The players.
 * @param player_count   The number of players.
 * @param current_player The player whose turn it is.
 */
void show_board(MonopolyCase **board, Player *players, int player_count, int current_player)
{
	int top[11] = { 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 };
	int bottom[11] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

	// top border
	printf("┌");
	for (int i = 0; i < 11; i++)
		printf(i < 10 ? "──────────┬" : "──────────┐\n");

	// top row
	for (int line = 0; line < 2; line++)
	{
		printf("│");
		for (int i = 0; i < 11; i++)
		{
			print_case(board, players, player_count, top[i], line);
			printf("│");
		}
		printf("\n");
	}
	printf("├──────────┼");
	for (int i = 1; i < 10; i++)
		printf(i < 9 ? "──────────┴" : "──────────┼");
	printf("──────────┤\n");

	// left column (19 to 11), the middle, right column (31 to 39)
	for (int row = 0; row < 9; row++)
	{
		for (int line = 0; line < 2; line++)
		{
			printf("│");
			print_case(board, players, player_count, 19 - row, line);
			printf("│");
			print_center(board, players, player_count, current_player, row * 3 + line);
			printf("│");
			print_case(board, players, player_count, 31 + row, line);
			printf("│\n");
		}
		if (row < 8)
		{
			printf("├──────────┤");
			print_center(board, players, player_count, current_player, row * 3 + 2);
			printf("├──────────┤\n");
		}
	}

	// bottom row
	printf("├──────────┼");
	for (int i = 1; i < 10; i++)
		printf(i < 9 ? "──────────┬" : "──────────┼");
	printf("──────────┤\n");
	for (int line = 0; line < 2; line++)
	{
		printf("│");
		for (int i = 0; i < 11; i++)
		{
			print_case(board, players, player_count, bottom[i], line);
			printf("│");
		}
		printf("\n");
	}
	printf("└");
	for (int i = 0; i < 11; i++)
		printf(i < 10 ? "──────────┴" : "──────────┘\n");
}

/* ************************************************************************** */
/*                                 THE CARDS                                  */
/* ************************************************************************** */

void card_border(char *border, char *left, char *right)
{
	printf("%s%s────────────────────────────%s" RESET, border, left, right);
}

void card_header(MonopolyCase *c, char *text, char *style)
{
	char *border = group_color(c->group);

	printf("%s│%s%s%s", border, group_background(c->group), group_text(c->group), style);
	print_centered(text, 28);
	printf(RESET "%s│" RESET, border);
}

// "│ Loyer terrain nu      50 $  │"
void card_money(char *border, char *label, int value)
{
	printf("%s│" RESET " ", border);
	print_padded(label, 18);
	printf(BOLD "%5d $" RESET "  %s│" RESET, value, border);
}

// "│ Propriétaire         Alice  │"
void card_text(char *border, char *label, char *value, char *color)
{
	printf("%s│" RESET " ", border);
	print_padded(label, 12);
	for (int i = visible_length(value); i < 13; i++)
		printf(" ");
	printf("%s" BOLD "%s" RESET "  %s│" RESET, color, value, border);
}

/**
 * Number of lines of a card, depending on the kind of case.
 */
int card_height(MonopolyCase *c)
{
	if (c->group >= 0 && c->group <= 7)		// property
		return 16;
	if (c->group == 9)						// station
		return 12;
	if (c->group == 8)						// company
		return 10;
	return 5;								// Départ, Chance, prison...
}

/**
 * Print one line of a card (30 columns), like a real title deed.
 */
void print_card_line(MonopolyCase *c, Player *players, int line)
{
	char *border = group_color(c->group);
	char owner[30] = "Banque";
	char *owner_color = "";
	char houses[30] = "aucune";

	if (c->owner_id >= 0)
	{
		strncpy(owner, players[c->owner_id].name, 13);
		owner[13] = '\0';
		owner_color = players[c->owner_id].color;
	}
	if (c->house_count == 5)
		strcpy(houses, "HÔTEL");
	else if (c->house_count > 0)
	{
		houses[0] = '\0';
		for (int h = 0; h < c->house_count; h++)
			strcat(houses, "▪ ");				// "▪ ▪ ▪ "
		houses[strlen(houses) - 1] = '\0';		// remove the last space
	}

	if (c->group >= 0 && c->group <= 7)		// property
	{
		switch (line)
		{
			case 0: card_border(border, "╭", "╮"); break;
			case 1: card_header(c, "TITRE DE PROPRIÉTÉ", ""); break;
			case 2: card_header(c, c->name, BOLD); break;
			case 3: card_border(border, "├", "┤"); break;
			case 4: card_money(border, "Loyer terrain nu", c->rent); break;
			case 5: card_money(border, "Avec 1 maison", c->rent_1_house); break;
			case 6: card_money(border, "Avec 2 maisons", c->rent_2_houses); break;
			case 7: card_money(border, "Avec 3 maisons", c->rent_3_houses); break;
			case 8: card_money(border, "Avec 4 maisons", c->rent_4_houses); break;
			case 9: card_money(border, "Avec un hôtel", c->rent_hotel); break;
			case 10: card_border(border, "├", "┤"); break;
			case 11: card_money(border, "Prix d'achat", c->price); break;
			case 12: card_money(border, "Prix d'une maison", c->house_price); break;
			case 13: card_text(border, "Propriétaire", owner, owner_color); break;
			case 14: card_text(border, "Construit", houses, owner_color); break;
			case 15: card_border(border, "╰", "╯"); break;
		}
	}
	else if (c->group == 9)					// station
	{
		switch (line)
		{
			case 0: card_border(border, "╭", "╮"); break;
			case 1: card_header(c, "GARE", ""); break;
			case 2: card_header(c, c->name, BOLD); break;
			case 3: card_border(border, "├", "┤"); break;
			case 4: card_money(border, "Loyer", c->rent_1_house); break;
			case 5: card_money(border, "Avec 2 gares", c->rent_2_houses); break;
			case 6: card_money(border, "Avec 3 gares", c->rent_3_houses); break;
			case 7: card_money(border, "Avec 4 gares", c->rent_4_houses); break;
			case 8: card_border(border, "├", "┤"); break;
			case 9: card_money(border, "Prix d'achat", c->price); break;
			case 10: card_text(border, "Propriétaire", owner, owner_color); break;
			case 11: card_border(border, "╰", "╯"); break;
		}
	}
	else if (c->group == 8)					// company
	{
		switch (line)
		{
			case 0: card_border(border, "╭", "╮"); break;
			case 1: card_header(c, "COMPAGNIE", ""); break;
			case 2: card_header(c, c->name, BOLD); break;
			case 3: card_border(border, "├", "┤"); break;
			case 4: card_text(border, "Loyer", "4 × les dés", ""); break;
			case 5: card_text(border, "Avec les 2", "10 × les dés", ""); break;
			case 6: card_border(border, "├", "┤"); break;
			case 7: card_money(border, "Prix d'achat", c->price); break;
			case 8: card_text(border, "Propriétaire", owner, owner_color); break;
			case 9: card_border(border, "╰", "╯"); break;
		}
	}
	else									// Départ, Chance, prison...
	{
		char *description = "Tirez une carte";

		if (c->index == 0)
			description = "Recevez 200 $ en passant";
		else if (c->index == 4)
			description = "Payez 200 $";
		else if (c->index == 38)
			description = "Payez 100 $";
		else if (c->index == 10)
			description = "Simple visite";
		else if (c->index == 20)
			description = "Rien ne se passe ici";
		else if (c->index == 30)
			description = "Direction la prison !";

		switch (line)
		{
			case 0: card_border(border, "╭", "╮"); break;
			case 1: printf("%s│" RESET BOLD, border); print_centered(c->name, 28); printf(RESET "%s│" RESET, border); break;
			case 2: card_border(border, "├", "┤"); break;
			case 3: printf("%s│" RESET, border); print_centered(description, 28); printf("%s│" RESET, border); break;
			case 4: card_border(border, "╰", "╯"); break;
		}
	}
}

/**
 * Displays the card of one case.
 *
 * @param board   The Monopoly board.
 * @param players The players (to write the name of the owner).
 * @param index   The index of the case to display (0-39).
 */
void show_card(MonopolyCase **board, Player *players, int index)
{
	if (index < 0 || index > 39)
	{
		printf("Cette case n'existe pas.\n");
		return;
	}
	printf("\n");
	for (int line = 0; line < card_height(board[index]); line++)
	{
		printf("  ");
		print_card_line(board[index], players, line);
		printf("\n");
	}
}

/**
 * @brief Displays all the cards of a color, side by side.
 *
 * @param board   The Monopoly board.
 * @param players The players (to write the name of the owners).
 * @param index   The color: 0 = brown ... 7 = dark blue, 8 = companies, 9 = stations.
 */
void show_color_card(MonopolyCase **board, Player *players, int index)
{
	char *titles[10] = {
		"Terrains marron", "Terrains bleu ciel", "Terrains roses", "Terrains orange", "Terrains rouges",
		"Terrains jaunes", "Terrains verts", "Terrains bleu foncé", "Les compagnies", "Les gares"
	};
	int cards[4];
	int count = 0;

	if (index < 0 || index > 9)
	{
		printf("Cette couleur n'existe pas.\n");
		return;
	}
	for (int i = 0; i < 40; i++)
	{
		if (board[i]->group == index)
			cards[count++] = i;
	}

	printf("\n  %s" BOLD "%s" RESET "\n\n", group_color(index), titles[index]);
	for (int line = 0; line < card_height(board[cards[0]]); line++)
	{
		printf("  ");
		for (int k = 0; k < count; k++)
		{
			print_card_line(board[cards[k]], players, line);
			printf("  ");
		}
		printf("\n");
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