/*
** EPITECH PROJECT, 2023
** MY_CURSES_H_
** File description:
** my_curses
*/

#include "parser.h"
#include "player.h"
#include <curses.h>
#include <wchar.h>

#ifndef MY_CURSES_H_
    #define MY_CURSES_H_

enum state {
    START,
    TEST,
    RESULT,
};

enum gamemode {
    TIME,
    WORD,
    QUOTE,
};

enum variant {
    S,
    M,
    L,
    XL,
};

enum menu_list_start {
    TOP_BAR,
    LANGUAGE_BUTTON,
    LANGUAGE_MENU,
    START_BUTTON,
};

typedef struct language_s {
    char *language;
    char *search;
    WINDOW *language_menu;
    char **language_list;
    char **language_list_json;
    int language_highlight;
    int current_language;
    int start_showing;
    int search_offset;
}language_t;

typedef struct ui_s {
    int col;
    int row;
    WINDOW *top_bar;
    char **top_bar_button;
    char ***top_bar_option;
    int top_bar_highlight;
    bool exit;
    int gamemode;
    int variant;
    int menu;
    char **sentence_arr;
    language_t *language;
    parser_t *parser;
}ui_t;

void my_curses(void);
void free_ui(ui_t *ui);
void cut_sentence_for_display(ui_t *ui, char *sentence);
void print_sentence(player_t *player, ui_t *ui);
void test_game(player_t *player, ui_t *ui);
void start(player_t *player, ui_t *ui);
void init_top_bar(ui_t *ui);
language_t *language_init(void);
void analyze_input(ui_t *ui, player_t *player);
void manage_variant(ui_t *ui, player_t *player);
void check_special_character(int row, int col, char to_check);
void init_language_menu(ui_t *ui);
void init_top_bar(ui_t *ui);

#endif /* MY_CURSES_H_ */
