/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** resutl_display
*/

#include "../../../include/include.h"

int get_length_next(int value, int current)
{
    int diff;
    char path[16] = "./asset/ascii/";
    struct stat s;

    for (int i = 0; i < current; i++, value /= 10);
    diff = value % 10;
    path[14] = diff + 48;
    path[15] = 0;
    stat(path, &s);
    return s.st_size / 5 - 1;
}

void display_value(int value, int x, int y)
{
    int value_temp = value / 10;
    int diff;
    char path[17] = "./asset/ascii/";

    value_temp *= 10;
    diff = value - value_temp;
    path[14] = diff + 48;
    path[15] = 0;
    display_ascii_from_file(stdscr, path, x, y);
    value /= 10;
    if (value > 0)
        display_value(value, x - get_length_next(value, 0), y);
}

void display_with_ascii(char *title, int value, int x, int y)
{
    int art_lenght = 0;

    for (int i = 0; i < my_find_digits(value); i++)
        art_lenght += get_length_next(value, i);
    mvprintw(y, x - art_lenght, "%s :", title);
    display_value(value, x - get_length_next(value, 0), y + 1);
}

void display_stat(ui_t *ui, player_t *player)
{
    int column_offset = ui->col / 4 + ui->col / 16;
    int last_word_index = ui->result->current_word - 1;

    if (ui->result->current_word == 0) {
        display_with_ascii("WPM", 0, column_offset - 4, ui->row / 3);
        mvprintw(ui->row / 3 * 2 - 1, column_offset + ui->col / 2, "%d", 0);
    } else {
        display_with_ascii("WPM", ui->result->wpm_per_word[last_word_index], column_offset - 4, ui->row / 3);
        mvprintw(ui->row / 3 * 2 - 1, column_offset + ui->col / 2, "%d",
                 (int)round((double)ui->result->time_upto_word[ui->result->current_word - 1] / 1000 ));
    }
    display_with_ascii("ACC", ui->result->data[ACCURACY], column_offset - 4, ui->row / 3 + 6);
    mvprintw(ui->row / 3 * 3 / 2 - 2, column_offset - 3, "W");
    mvprintw(ui->row / 3 * 3 / 2, column_offset - 3, "P");
    mvprintw(ui->row / 3 * 3 / 2 + 2, column_offset - 3, "M");
    mvprintw((ui->row / 3) * 2 - 1, column_offset - 1, "0");
    mvprintw(ui->row / 3, column_offset - my_find_digits(ui->result->data[WPM_MAX]), "%d", ui->result->data[WPM_MAX]);
    box(ui->result->graph, 0, 0);
    draw_point_temp(ui);
    refresh();
    wrefresh(ui->result->graph);
}

void display_result(ui_t *ui, player_t *player)
{
    if (player->state != RESULT)
        return;
    display_stat(ui, player);
    while (getch() != 'q');
    player->state = START;
    reset_result(ui->result, ui->parser->nb_word);
}

