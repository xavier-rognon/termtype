/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** init_curses
*/

#include "../../include/include.h"
#include <curses.h>

static void init_curses(void)
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    clear();
}

ui_t *init_ui(void)
{
    ui_t *ui = malloc(sizeof(ui_t));

    getmaxyx(stdscr, ui->row, ui->col);
    ui->top_bar_button = my_str_to_word_array("  󱑃 time  ,  󰘝 words  ,  󰝗 quote  ,|  ", ",");
    ui->top_bar_option = malloc(sizeof(char **) * 4);
    ui->top_bar_option[0] = my_str_to_word_array("   15   ,   30   ,   60   ,   120   ", ",");
    ui->top_bar_option[1] = my_str_to_word_array("   25   ,   50   ,   100   ,   200   ", ",");
    ui->top_bar_option[2] = my_str_to_word_array("    S    ,    M    ,    L    ,    XL    ", ",");
    ui->top_bar_option[3] = NULL;
    ui->top_bar_highlight = 0;
    ui->language = language_init();
    ui->gamemode = TIME;
    ui->prev_gamemode = TIME;
    ui->variant = M;
    ui->menu = TOP_BAR;
    ui->exit = false;
    return ui;
}

void cut_sentence_for_display(ui_t *ui, char *sentence)
{
    int col_third = ui->col / 3;
    int prev_stop = -1;
    int array_size = 1;

    ui->sentence_arr = malloc(sizeof(char *));
    ui->sentence_arr[0] = NULL;
    for (int i = 0; sentence[i] != 0; i++) {
        if (i - prev_stop == col_third * 2 || sentence[i] == '\n') {
            for (; sentence[i + 1] != 0 && (sentence[i] != ' ' && sentence[i] != '\n'); i++);
            ui->sentence_arr = my_realloc(ui->sentence_arr, array_size * sizeof(char *));
            if (prev_stop == 0)
                ui->sentence_arr[array_size - 1] = strndup(&sentence[prev_stop], i - prev_stop - 1);
            else
                ui->sentence_arr[array_size - 1] = strndup(&sentence[prev_stop + 1], i - prev_stop - 1);
            prev_stop = i;
            array_size++;
        }
    }
    if (prev_stop == -1)
        prev_stop = 0;
    ui->sentence_arr = my_realloc(ui->sentence_arr, array_size * sizeof(char *));
    ui->sentence_arr[array_size - 1] = strdup(&sentence[prev_stop]);
}

void print_sentence(player_t *player, ui_t *ui)
{
    mvprintw(ui->row / 2 - 1, (ui->col - strlen(ui->sentence_arr[player->current_row[0]])) / 2,
             "%s", ui->sentence_arr[player->current_row[0]]);
    if (ui->sentence_arr[player->current_row[1]] != NULL)
        mvprintw(ui->row / 2, (ui->col - strlen(ui->sentence_arr[player->current_row[1]])) / 2,
                 "%s", ui->sentence_arr[player->current_row[1]]);
    if (ui->sentence_arr[player->current_row[2]] != NULL)
        mvprintw(ui->row / 2 + 1, (ui->col - strlen(ui->sentence_arr[player->current_row[2]])) / 2,
                 "%s", ui->sentence_arr[player->current_row[2]]);
}

void my_curses(void)
{
    ui_t *ui;
    player_t *player;

    init_curses();
    ui = init_ui();
    init_language_menu(ui);
    init_top_bar(ui);
    ui->parser = parser_language("./asset/languages/english.json", 350);
    player = player_init(ui->parser);
    ui->result = init_result(ui->parser->nb_word, ui->col, ui->row);
    cut_sentence_for_display(ui, ui->parser->sentence);
    player->cursor_pos[0] = ui->row / 2 - 1;
    player->cursor_pos[1] = (ui->col - strlen(ui->sentence_arr[0])) / 2;
    player->pos_start_first_line = (ui->col - strlen(ui->sentence_arr[0])) / 2;
    ui->lenght = ui->parser->nb_word;
    while (ui->exit == false) {
        clear();
        start(player, ui);
        test_game(player, ui);
        display_result(ui, player);
        getmaxyx(stdscr, ui->row, ui->col);
    }
    endwin();
    free_ui(ui);
    free_player(player);
}

