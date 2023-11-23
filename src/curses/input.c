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
    if (input == '\n' && ui->top_bar_highlight < 3) {
        ui->prev_gamemode = ui->gamemode;
        ui->gamemode = ui->top_bar_highlight;
        if (ui->gamemode != ui->prev_gamemode && (ui->gamemode == QUOTE))
            ui->language->current_type = QUOTES;
        if (ui->gamemode != ui->prev_gamemode && (ui->prev_gamemode == QUOTE))
            ui->language->current_type = RANDOM_WORDS;
        manage_variant(ui, player);
    }
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
    gamemode_language_info_t *current_type = ui->language->info[ui->language->current_type];

    current_type->search_offset = 0;
    current_type->start_showing = 0;
    if (strlen(current_type->search) == 0){
        current_type->language_highlight = 0;
        return;
    }
    for(int i = 0; strncmp(current_type->language_list[i], current_type->search,
                           strlen(current_type->search)) != 0;
        i++, current_type->search_offset++)
        if (current_type->language_list[i + 1] == NULL)
            break;
    current_type->language_highlight = current_type->search_offset;
}

void input_language_menu(ui_t *ui, player_t *player, int input)
{
    char input_str[2] = {input, 0};
    gamemode_language_info_t *current_type = ui->language->info[ui->language->current_type];

    player = player;
    if (ui->language->state == EXIT) {
        if (input == '\t')
            ui->language->state = SEARCH;
        if (input == '\n')
            ui->menu = LANGUAGE_BUTTON;
        return;
    }
    if (input == '\t' && ui->language->state == SEARCH)
        ui->language->state = EXIT;
    if (input == KEY_DOWN && current_type->language_list[current_type->language_highlight] != NULL) {
        if (current_type->language_list[current_type->language_highlight + 1] == NULL)
            return;
        if (current_type->language_highlight - current_type->start_showing - current_type->search_offset < ui->row - 5 &&
            (strncmp(current_type->language_list[current_type->language_highlight + 1], current_type->search,
                     strlen(current_type->search)) == 0 || strlen(current_type->search) == 0))
            current_type->language_highlight++;
        else if (strncmp(current_type->language_list[current_type->language_highlight + 1], current_type->search,
                         strlen(current_type->search)) == 0 || strlen(current_type->search) == 0){
        current_type->language_highlight++;
        current_type->start_showing++;
    }
    }
    if (input == KEY_UP && current_type->language_highlight > 0) {
        if (current_type->language_highlight - 1 == -1)
            return;
        if (current_type->language_highlight != current_type->start_showing + current_type->search_offset &&
            strncmp(current_type->language_list[current_type->language_highlight - 1], current_type->search,
                    strlen(current_type->search)) == 0)
            current_type->language_highlight--;
        else if (strncmp(current_type->language_list[current_type->language_highlight - 1], current_type->search,
                         strlen(current_type->search)) == 0 || strlen(current_type->search) == 0){
        current_type->language_highlight--;
        current_type->start_showing--;
    }
    }
    if (input == '\n') {
        current_type->current_language = current_type->language_highlight;
        manage_variant(ui, player);
        free(current_type->language);
        current_type->language = my_strcat("󰇧 ", current_type->language_list[current_type->current_language]);
        free_array(ui->sentence_arr);
        cut_sentence_for_display(ui, ui->parser->sentence);
        return;
    }
    if (input == 263 && strlen(current_type->search) != 0) {
        current_type->search[strlen(current_type->search) - 1] = 0;
        update_offset(ui);
    }
    if (my_char_isprintable(input) == true && input != '\n') {
        if (current_type->search == NULL)
            current_type->search = (char *)&input;
        else
            current_type->search = my_strcat(current_type->search, input_str);
        update_offset(ui);
    }
}

void input_start_button(ui_t *ui, player_t *player, int input)
{
    if (input == '\n') {
        clear();
        refresh();
        player->state = TEST;
        ui->result->time_start_test = get_time_millisecond();
        ui->result->time_start_word = get_time_millisecond();
        player->last_input = 0;
        curs_set(1);
        player->cursor_pos[1] = (ui->col - strlen(ui->sentence_arr[0])) / 2;
        if (ui->gamemode == TIME)
            alarm(player->playtime);
    }
    if (input == '\t')
        ui->menu = EXIT_BUTTON;
}

void input_exit_button(ui_t *ui, player_t *player, int input)
{
    player = player;
    if (input == '\t')
        ui->menu = TOP_BAR;
    if (input == '\n')
        ui->exit = true;
}

void analyze_input(ui_t *ui, player_t *player)
{
    int input = getch();
    void (*input_menu[5])(ui_t *, player_t *, int) = {&input_top_bar, &input_language_button,
        &input_language_menu, &input_start_button, &input_exit_button};

    input_menu[ui->menu](ui, player, input);
}

