#pragma once
																																										   
 //      __  __  ___  _   _  ___  ____   ___  _  __   __                                            
 //     |  \/  |/ _ \| \ | |/ _ \|  _ \ / _ \| | \ \ / /                                            
 //     | |\/| | | | |  \| | | | | |_) | | | | |  \ V /                                             
 //     | |  | | |_| | |\  | |_| |  __/| |_| | |___| |                                              
 //     |_|  |_|\___/|_| \_|\___/|_|    \___/|_____|_|  
 //
 //    ████████╗███████╗██████╗ ███╗   ███╗██╗███╗   ██╗ █████╗ ██╗         ███████╗██████╗ ██╗████████╗██╗ ██████╗ ███╗   ██╗    ██╗
 //    ╚══██╔══╝██╔════╝██╔══██╗████╗ ████║██║████╗  ██║██╔══██╗██║         ██╔════╝██╔══██╗██║╚══██╔══╝██║██╔═══██╗████╗  ██║    ██║
 //       ██║   █████╗  ██████╔╝██╔████╔██║██║██╔██╗ ██║███████║██║         █████╗  ██║  ██║██║   ██║   ██║██║   ██║██╔██╗ ██║    ██║
 //       ██║   ██╔══╝  ██╔══██╗██║╚██╔╝██║██║██║╚██╗██║██╔══██║██║         ██╔══╝  ██║  ██║██║   ██║   ██║██║   ██║██║╚██╗██║    ╚═╝
 //       ██║   ███████╗██║  ██║██║ ╚═╝ ██║██║██║ ╚████║██║  ██║███████╗    ███████╗██████╔╝██║   ██║   ██║╚██████╔╝██║ ╚████║    ██╗     


// ANSI color codes for terminal output
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define DIM         "\033[2m"
#define ITALIC      "\033[3m"
#define UNDERLINE   "\033[4m"
#define BLINK       "\033[5m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define BRIGHT_RED    "\033[91m"
#define BRIGHT_GREEN  "\033[92m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_BLUE   "\033[94m"
#define BRIGHT_MAGENTA "\033[95m"
#define BRIGHT_CYAN   "\033[96m"
#define BRIGHT_WHITE  "\033[97m"
#define BG_RED          "\033[41m"
#define BG_GREEN        "\033[42m"
#define BG_YELLOW       "\033[43m"
#define BG_BLUE         "\033[44m"
#define BG_MAGENTA      "\033[45m"
#define BG_CYAN         "\033[46m"
#define BG_WHITE        "\033[47m"
#define BG_BRIGHT_RED     "\033[101m"
#define BG_BRIGHT_GREEN   "\033[102m"
#define BG_BRIGHT_YELLOW  "\033[103m"
#define BG_BRIGHT_BLUE    "\033[104m"
#define BG_BRIGHT_MAGENTA "\033[105m"
#define BG_BRIGHT_CYAN    "\033[106m"
#define BG_BRIGHT_WHITE   "\033[107m"
#define ORANGE           "\033[38;5;208m"   // Orange text
#define BROWN            "\033[38;5;130m"   // Brown text
#define BG_ORANGE        "\033[48;5;208m"   // Orange background
#define BG_BROWN         "\033[48;5;130m"   // Brown background

// Structure pour chaque case du Monopoly
typedef struct MonopolyCase {
	int index;              // Case number
	char *name;             // Name of the case
	int price;              // Price of the case
	int rent;               // Rent on the case
	int house_price;        // Cost of building houses
	int rent_1_house;       // Rent with 1 house
	int rent_2_houses;      // Rent with 2 houses
	int rent_3_houses;      // Rent with 3 houses
	int rent_4_houses;      // Rent with 4 houses
	int rent_hotel;         // Rent with a hotel
	int owner_id;           // ID of the player who owns the case
	int house_count;        // Number of houses on the case
} MonopolyCase;

// Prototype de la fonction de création d'une case
MonopolyCase*       create_case(int index, char *name, int price, int rent, int house_price, int rent_1_house, int rent_2_houses, int rent_3_houses, int rent_4_houses, int rent_hotel, int owner_id, int house_count);
MonopolyCase**      init_board(void);
void                clear_terminal(void);
void                show_card(MonopolyCase **board, int index);
void                show_board(MonopolyCase **board);
void                format_string(char *str, char *output);
void                format_price(int price, char *output);
char*               house(MonopolyCase *property);
void                show_rules(void);
const char*         check_house(MonopolyCase* case_ptr, int line);
