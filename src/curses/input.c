/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** input
*/

#include "../../include/include.h"

void input_top_bar(ui_t *ui, player_t *player, int input)
{
    player = player;
    if (ui->top_bar_highlight != 0 && input == KEY_LEFT)
        ui->top_bar_highlight--;
    if (ui->top_bar_highlight != 6 && input == KEY_RIGHT)
        ui->top_bar_highlight++;
    if (input == '\n' && ui->top_bar_highlight < 3)
        ui->gamemode = ui->top_bar_highlight;
    if (input == '\n' && ui->top_bar_highlight >= 3) {
        ui->variant = ui->top_bar_highlight - 3;
        manage_variant(ui, player);
    }
    if (input == '\t')
        ui->menu = LANGUAGE_BUTTON;
}

void input_language_button(ui_t *ui, player_t *player, int input)
{
    player = player;
    if (input == '\n')
        ui->menu = LANGUAGE_MENU;
    if (input == '\t')
        ui->menu = START_BUTTON;
}

void input_language_menu(ui_t *ui, player_t *player, int input)
{
    player = player;
    char input_str[2] = {input, 0};
    if (input == KEY_DOWN && ui->language->language_list[ui->language->language_highlight] != NULL) {
        if (ui->language->language_highlight - ui->language->start_showing <
            ui->row - 3)
            ui->language->language_highlight++;
        else {
            ui->language->language_highlight++;
            ui->language->start_showing++;
        }
    }
    if (input == KEY_UP && ui->language->language_highlight > 0) {
        if (ui->language->language_highlight != ui->language->start_showing)
            ui->language->language_highlight--;
        else {
            ui->language->language_highlight--;
            ui->language->start_showing--;
        }
    }
    if (input == '\n') {
        ui->language->current_language = ui->language->language_highlight;
        free_parser(ui->parser);
        ui->parser = parser_language(my_strcat("./asset/languages/",
                                               ui->language->language_list_json[ui->language->current_language]));
        ui->language->language = my_strcat("󰇧 ", ui->language->language_list[ui->language->current_language]);
        free_array(ui->sentence_arr);
        cut_sentence_for_display(ui, ui->parser->sentence);
    }
    if (input == 27) {
        ui->menu = LANGUAGE_BUTTON;
        ui->language->search = "\0";
    }
    if (input == 263 && strlen(ui->language->search) != 0)
        ui->language->search[strlen(ui->language->search) - 1] = 0;
    if (my_char_isalphanum(input) == true)
        ui->language->search = my_strcat(ui->language->search, input_str);
}

void input_start_button(ui_t *ui, player_t *player, int input)
{
    if (input == '\n') {
        clear();
        refresh();
        player->state = TEST;
        player->last_input = 0;
        curs_set(1);
        player->cursor_pos[1] = (ui->col - strlen(ui->sentence_arr[0])) / 2;
        alarm(player->playtime);
    }
    if (input == '\t')
        ui->menu = TOP_BAR;
}

void analyze_input(ui_t *ui, player_t *player)
{
    int input = getch();
    void (*input_menu[4])(ui_t *, player_t *, int) = {&input_top_bar, &input_language_button,
    &input_language_menu, &input_start_button};

    if (input == 'q' && ui->menu != LANGUAGE_MENU)
        ui->exit = true;
    input_menu[ui->menu](ui, player, input);
}

