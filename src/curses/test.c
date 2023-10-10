/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** test
*/

#include "../../include/include.h"
#include <curses.h>
#include <stdio.h>
#include <unistd.h>

bool check_end_of_line(player_t *player, char **sentence_arr, int col)
{
    if (player->cursor_pos[1] == (int) ((col - strlen(sentence_arr[player->current_row[player->current_line - 1]])) / 2 +
        strlen(sentence_arr[player->current_row[player->current_line - 1]]) - player->offset_current_line)) {
        player->start_showing_player_input += strlen(sentence_arr[player->current_row[0]])
            + 1 - player->offset_current_line;
        player->offset += player->offset_current_line;
        player->offset_current_line = 0;
        player->current_row[0]++;
        player->current_row[1]++;
        player->current_row[2]++;
        player->cursor_pos[1] = (col - strlen(sentence_arr[player->current_row[0]])) / 2;
        return true;
    }
    return false;
}

void check_input(player_t *player, char *sentence, char **sentence_arr, int col)
{
    if (player->last_input == 7) {
        if (player->cursor_pos[1] == (int) (col - strlen(sentence_arr[player->current_row[0]])) / 2)
            return;
        player->cursor_pos[1]--;
        player->lenght_input--;
        if (player->correct_input[player->lenght_input] < 0 || player->wrong_input[player->lenght_input] < 0)
            player->offset_current_line--;
        player->correct_input[player->lenght_input] = 0;
        player->wrong_input[player->lenght_input] = 0;
        return;
    }
    if (sentence[player->lenght_input + player->offset + player->offset_current_line] == 0)
        if (sentence[player->lenght_input + player->offset + player->offset_current_line] < 0)
            player->offset_current_line--;
    if (player->last_input == sentence[player->lenght_input + player->offset + player->offset_current_line])
        player->correct_input[player->lenght_input] = sentence[player->lenght_input + player->offset + player->offset_current_line];
    else {
        if (player->last_input != ' ')
            player->wrong_input[player->lenght_input] = player->last_input;
        else
            player->wrong_input[player->lenght_input] = '_';
    }
    player->lenght_input++;
    if (check_end_of_line(player, sentence_arr, col) == false)
        player->cursor_pos[1]++;
}

void print_player_input(player_t *player, char **sentence_arr, int col, int row)
{
    int i_clean = 0;

    for (int i = player->start_showing_player_input; i <= player->lenght_input; i++, i_clean++) {
        if (player->correct_input[i] != 0) {
            attron(COLOR_PAIR(2));
            check_special_character(row / 2 - 1, (col - strlen(sentence_arr[player->current_row[0]])) / 2 +
                                    i_clean, player->correct_input[i]);
            attroff(COLOR_PAIR(2));
        } else {
            attron(COLOR_PAIR(1));
            check_special_character(row / 2 - 1, (col - strlen(sentence_arr[player->current_row[0]])) / 2 +
                                    i_clean, player->wrong_input[i]);
            attroff(COLOR_PAIR(1));
        }
    }
}

void end_of_timer(player_t *player, ui_t *ui)
{
    if (check_alarm_g == 1) {
        check_alarm_g = 0;
        player->state = START;
        free_parser(ui->parser);
        ui->parser = parser_language(my_strcat("./asset/languages/",
                                               ui->language->language_list_json[ui->language->current_language]));
        free_array(ui->sentence_arr);
        cut_sentence_for_display(ui, ui->parser->sentence);
        player_reset_test(player, ui->parser);
        curs_set(0);
    }
}

void test_game(player_t *player, ui_t *ui)
{
    if (player->state != TEST)
        return;
    print_sentence(player, ui);
    print_player_input(player, ui->sentence_arr, ui->col, ui->row);
    move(player->cursor_pos[0], player->cursor_pos[1]);
    player->last_input = getch();
    if (player->last_input == -61) {
        player->last_input = getch();
        player->offset_current_line++;
    }
    check_input(player, ui->parser->sentence, ui->sentence_arr, ui->col);
    end_of_timer(player, ui);
}
