/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** result_input
*/

#include "../../../include/include.h"
#include <curses.h>

void start_same_test(ui_t *ui, player_t *player)
{
    player_reset_test(player, ui->parser);
    curs_set(1);
    reset_result(ui->result, ui->parser->nb_word);
    ui->result->time_start_test = get_time_millisecond();
    ui->result->time_start_word = get_time_millisecond();
    player->last_input = 0;
    curs_set(1);
    player->cursor_pos[1] = (ui->col - strlen(ui->sentence_arr[0])) / 2;
    if (ui->gamemode == TIME)
        alarm(player->playtime);
    player->state = TEST;
}

void start_new_test(ui_t *ui, player_t *player)
{
    reset_test(player, ui);
    curs_set(1);
    reset_result(ui->result, ui->parser->nb_word);
    ui->result->time_start_test = get_time_millisecond();
    ui->result->time_start_word = get_time_millisecond();
    player->last_input = 0;
    curs_set(1);
    player->cursor_pos[1] = (ui->col - strlen(ui->sentence_arr[0])) / 2;
    if (ui->gamemode == TIME)
        alarm(player->playtime);
    player->state = TEST;
}

void startscreen(ui_t *ui, player_t *player)
{
    reset_test(player, ui);
    reset_result(ui->result, ui->parser->nb_word);
    player->state = START;
}

void analyze_input_result(ui_t *ui, player_t *player)
{
    int input = getch();
    void (*action[3])(ui_t *, player_t *) = {&start_new_test, &start_same_test, &startscreen}; 

    if (input == KEY_RIGHT || input == '\t')
        ui->result->current_button = (ui->result->current_button + 1) % 3;
    if (input == KEY_LEFT)
        ui->result->current_button--;
    if (ui->result->current_button < 0)
        ui->result->current_button = 2;
    if (input == '\n')
        action[ui->result->current_button](ui, player);
}

