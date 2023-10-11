/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** input
*/

#include "../../include/include.h"
#include <stdio.h>

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

void update_offset(ui_t *ui)
{
    ui->language->search_offset = 0;
    ui->language->start_showing = 0;

    if (strlen(ui->language->search) == 0)
        return;
    for(int i = 0; strncmp(ui->language->language_list[i], ui->language->search,
                           strlen(ui->language->search)) != 0;
        i++, ui->language->search_offset++)
        if (ui->language->language_list[i + 1] == NULL)
            break;
    ui->language->language_highlight = ui->language->search_offset;
}

void input_language_menu(ui_t *ui, player_t *player, int input)
{
    char input_str[2] = {input, 0};

    player = player;
    if (input == KEY_DOWN && ui->language->language_list[ui->language->language_highlight] != NULL) {
        if (ui->language->language_list[ui->language->language_highlight + 1] == NULL)
            return;
        if (ui->language->language_highlight - ui->language->start_showing - ui->language->search_offset < ui->row - 5 &&
            (strncmp(ui->language->language_list[ui->language->language_highlight + 1], ui->language->search,
                     strlen(ui->language->search)) == 0 || strlen(ui->language->search) == 0))
            ui->language->language_highlight++;
        else if (strncmp(ui->language->language_list[ui->language->language_highlight + 1], ui->language->search,
                         strlen(ui->language->search)) == 0 || strlen(ui->language->search) == 0){
        ui->language->language_highlight++;
        ui->language->start_showing++;
    }
    }
    if (input == KEY_UP && ui->language->language_highlight > 0) {
        if (ui->language->language_highlight - 1 == -1)
            return;
        if (ui->language->language_highlight != ui->language->start_showing + ui->language->search_offset &&
            strncmp(ui->language->language_list[ui->language->language_highlight - 1], ui->language->search,
                    strlen(ui->language->search)) == 0)
            ui->language->language_highlight--;
        else if (strncmp(ui->language->language_list[ui->language->language_highlight - 1], ui->language->search,
                         strlen(ui->language->search)) == 0 || strlen(ui->language->search) == 0){
            ui->language->language_highlight--;
            ui->language->start_showing--;
        }
    }
    if (input == '\n') {
        ui->language->current_language = ui->language->language_highlight;
        free_parser(ui->parser);
        ui->parser = parser_language(my_strcat("./asset/languages/",
                                               ui->language->language_list_json[ui->language->current_language]), ui->lenght);
        ui->language->language = my_strcat("󰇧 ", ui->language->language_list[ui->language->current_language]);
        free_array(ui->sentence_arr);
        cut_sentence_for_display(ui, ui->parser->sentence);
        return;
    }
    if (input == 27) {
        ui->menu = LANGUAGE_BUTTON;
        input = 0;
        ui->language->search = "\0";
    }
    if (input == 263 && strlen(ui->language->search) != 0) {
        ui->language->search[strlen(ui->language->search) - 1] = 0;
        update_offset(ui);
    }
    if (my_char_isprintable(input) == true && input != '\n') {
        ui->language->search = my_strcat(ui->language->search, input_str);
        update_offset(ui);
    }
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
        if (ui->gamemode == TIME)
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

    if (input == 27 && ui->menu != LANGUAGE_MENU)
        ui->exit = true;
    input_menu[ui->menu](ui, player, input);
}

