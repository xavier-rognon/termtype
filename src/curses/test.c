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

void reset_test(player_t *player, ui_t *ui)
{
    clear_window(stdscr);
    clear_window(ui->result->graph);
    manage_variant(ui, player);
    player_reset_test(player, ui->parser);
    free_array(ui->sentence_arr);
    cut_sentence_for_display(ui, ui->parser->sentence);
}

bool check_end_of_line(player_t *player, char **sentence_arr, char *sentence, int col)
{
    int current_char = player->lenght_input + player->offset + player->offset_current_line;

    if (current_char >= (int)strlen(sentence)) {
        check_alarm_g = 1;
        return true;
    }
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
        if (sentence_arr[player->current_row[1]] == NULL)
            player->cursor_pos[1]++;
        return true;
    }
    return false;
}

void check_input(player_t *player, ui_t *ui)
{
    int current_char = player->lenght_input + player->offset + player->offset_current_line;

    if (player->last_input == 7) {
        if (player->cursor_pos[1] == (int) (ui->col - strlen(ui->sentence_arr[player->current_row[0]])) / 2)
            return;
        player->cursor_pos[1]--;
        player->lenght_input--;
        if (player->wrong_input[player->lenght_input] != 0)
            ui->result->data[INCORRECT]--;
        if (player->correct_input[player->lenght_input] < 0 || player->wrong_input[player->lenght_input] < 0)
            player->offset_current_line--;
        if (player->correct_input[player->lenght_input] == ' ') {
            ui->result->current_word--;
        }
        player->correct_input[player->lenght_input] = 0;
        player->wrong_input[player->lenght_input] = 0;
        return;
    }
    if (player->last_input == ui->parser->sentence[current_char]) {
        player->correct_input[player->lenght_input] = ui->parser->sentence[current_char];
        if (player->correct_input[player->lenght_input] == ' ') {
            ui->result->time_upto_word[ui->result->current_word] =
                get_time_millisecond() - ui->result->time_start_test;
            ui->result->wpm_raw_per_word[ui->result->current_word] =
                get_raw_wpm(ui->result, player->lenght_input);
            ui->result->wpm_per_word[ui->result->current_word] =
                get_wpm(ui->result, player->lenght_input);
            ui->result->current_word++;
        }
    } else {
        if (player->last_input != ' ')
            player->wrong_input[player->lenght_input] = player->last_input;
        else
            player->wrong_input[player->lenght_input] = '_';
        ui->result->data[NB_ERRORS]++;
        ui->result->data[INCORRECT]++;
    }
    player->lenght_input++;
    if (check_end_of_line(player, ui->sentence_arr, ui->parser->sentence, ui->col) == false)
        player->cursor_pos[1]++;
}

void print_player_input(player_t *player, char **sentence_arr, int col, int row)
{
    int i_clean = 0;
    int last_line_offset = 0;

    if (sentence_arr[player->current_row[1]] == NULL && my_arrlen(sentence_arr) != 1)
        last_line_offset++;
    for (int i = player->start_showing_player_input; i <= player->lenght_input; i++, i_clean++) {
        if (player->correct_input[i] != 0) {
            attron(COLOR_PAIR(2));
            check_special_character(row / 2 - 1, (col - strlen(sentence_arr[player->current_row[0]])) / 2 +
                                    i_clean + last_line_offset, player->correct_input[i]);
            attroff(COLOR_PAIR(2));
        } else {
            attron(COLOR_PAIR(1));
            check_special_character(row / 2 - 1, (col - strlen(sentence_arr[player->current_row[0]])) / 2 +
                                    i_clean + last_line_offset, player->wrong_input[i]);
            attroff(COLOR_PAIR(1));
        }
    }
}

void print_info_test(player_t *player, ui_t *ui)
{
    if (ui->gamemode == TIME)
        mvprintw(ui->row / 2 - 2, player->pos_start_first_line,
                 "%lld", player->playtime + (ui->result->time_start_test - get_time_millisecond()) / 1000);
    else
        mvprintw(ui->row / 2 - 2, player->pos_start_first_line,
                 "%d/%d", ui->result->current_word, ui->lenght);
}

void end_of_timer(player_t *player, ui_t *ui)
{
    if (check_alarm_g == 1) {
        check_alarm_g = 0;
        player->state = RESULT;
        ui->result->data[WPM_MAX] = get_max_wpm(ui->result);
        ui->result->data[ACCURACY] = get_accuracy(ui->result, player->lenght_input);
        curs_set(0);
    }
}

void test_game(player_t *player, ui_t *ui)
{
    if (player->state != TEST)
        return;
    print_sentence(player, ui);
    print_player_input(player, ui->sentence_arr, ui->col, ui->row);
    print_info_test(player, ui);
    move(player->cursor_pos[0], player->cursor_pos[1]);
    player->last_input = getch();
    if (player->last_input == -61) {
        player->last_input = getch();
        player->offset_current_line++;
    }
    check_input(player, ui);
    end_of_timer(player, ui);
}

