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

enum type {
    QUOTES,
    RANDOM_WORDS,
};

enum menu_list_start {
    TOP_BAR,
    LANGUAGE_BUTTON,
    LANGUAGE_MENU,
    START_BUTTON,
    EXIT_BUTTON,
};

enum data_value {
    NB_ERRORS,
    INCORRECT,
    ACCURACY,
    WPM_FINAL,
    WPM_MAX,
    RAW_WPM_FINAL,
    TIME_TEST,
};

enum language_menu_event {
    SEARCH,
    EXIT,
};

typedef struct result_s {
    WINDOW *graph;
    long long time_start_test;
    long long time_start_word;
    long long *time_upto_word;
    int data[8];
    int *graph_point_col;
    int *graph_point_row;
    int *wpm_per_word;
    int *wpm_raw_per_word;
    int current_word;
    int current_button;
    char **result_button;
}result_t;

typedef struct gamemode_language_info_s {
    char *language;
    char *search;
    char **language_list;
    char **language_list_json;
    int language_highlight;
    int current_language;
    int start_showing;
    int search_offset;
}gamemode_language_info_t;

typedef struct language_s {
    WINDOW *language_menu;
    gamemode_language_info_t **info;
    int state;
    int current_type;
}language_t;

typedef struct ui_s {
    WINDOW *top_bar;
    int col;
    int row;
    char **top_bar_button;
    char ***top_bar_option;
    int top_bar_highlight;
    bool exit;
    int gamemode;
    int prev_gamemode;
    int variant;
    int menu;
    int lenght;
    char **sentence_arr;
    language_t *language;
    parser_t *parser;
    result_t *result;
}ui_t;

//ui_t function
void my_curses(void);
void free_ui(ui_t *ui);
void cut_sentence_for_display(ui_t *ui, char *sentence);
void print_sentence(player_t *player, ui_t *ui);


//start screen
void init_language_menu(ui_t *ui);
language_t *language_init(void);
void language_free(language_t *language);
void init_top_bar(ui_t *ui);
void start(player_t *player, ui_t *ui);
void manage_variant(ui_t *ui, player_t *player);

//test screen
void analyze_input(ui_t *ui, player_t *player);
void test_game(player_t *player, ui_t *ui);
void check_special_character(int row, int col, char to_check);
void reset_test(player_t *player, ui_t *ui);

//result screen
result_t *init_result(int sentence_length, int col, int row);
void reset_result(result_t *result, int sentence_length);
void free_result(result_t *result);
int get_raw_wpm(result_t *result, int input_lenght);
int get_wpm(result_t *result, int input_lenght);
int get_accuracy(result_t *result, int input_lenght);
int get_max_wpm(result_t *result);
void display_result(ui_t *ui, player_t *player);
long long get_time_millisecond(void);
void draw_point_temp(ui_t *ui);
void analyze_input_result(ui_t *ui, player_t *player);

#endif /* MY_CURSES_H_ */
