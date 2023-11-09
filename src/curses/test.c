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
    char *language_path = my_strcat("./asset/languages/",
                                    ui->language->language_list_json[ui->language->current_language]);
    clear_window(stdscr);
    clear_window(ui->result->graph);
    player->state = RESULT;
    refresh();
    ui->result->data[WPM_MAX] = get_max_wpm(ui->result, player->lenght_input);
    free_parser(ui->parser);
    ui->parser = parser_language(language_path, ui->lenght);
    free_array(ui->sentence_arr);
    cut_sentence_for_display(ui, ui->parser->sentence);
    ui->result->data[ACCURACY] = get_accuracy(ui->result, player->lenght_input);
    player_reset_test(player, ui->parser);
    refresh();
    curs_set(0);
    free(language_path);
}

bool check_end_of_line(player_t *player, char **sentence_arr, int col, ui_t *ui)
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
        if (sentence_arr[player->current_row[0]] == NULL)
            reset_test(player, ui);
        player->cursor_pos[1] = (col - strlen(sentence_arr[player->current_row[0]])) / 2;
        return true;
    }
    return false;
}

void check_input(player_t *player, ui_t *ui)
{
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
    if (player->last_input == ui->parser->sentence[player->lenght_input + player->offset + player->offset_current_line]) {
        player->correct_input[player->lenght_input] = ui->parser->sentence[player->lenght_input + player->offset + player->offset_current_line];
        if (player->correct_input[player->lenght_input] == ' ') {
            ui->result->time_upto_word[ui->result->current_word] = get_time_millisecond() - ui->result->time_start_test;
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
    if (check_end_of_line(player, ui->sentence_arr, ui->col, ui) == false)
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

void print_info_test(player_t *player, ui_t *ui)
{
    if (ui->gamemode == TIME)
        mvprintw(ui->row / 2 - 2, ui->col / 6,
                 "%lld", player->playtime + (ui->result->time_start_test - get_time_millisecond()) / 1000);
    else
        mvprintw(ui->row / 2 - 2, ui->col / 6,
                 "%d/%d", ui->result->current_word, ui->lenght);
}

void end_of_timer(player_t *player, ui_t *ui)
{
    if (check_alarm_g == 1) {
        check_alarm_g = 0;
        reset_test(player, ui);
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

