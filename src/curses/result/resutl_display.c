/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** resutl_display
*/

#include "../../../include/include.h"
#include <curses.h>

void display_stat(ui_t *ui, player_t *player)
{
    mvprintw(ui->row / 3 * 3 / 2 - 2, ui->col / 4 - 3, "W");
    mvprintw(ui->row / 3 * 3 / 2, ui->col / 4 - 3, "P");
    mvprintw(ui->row / 3 * 3 / 2 + 2, ui->col / 4 - 3, "M");
    mvprintw((ui->row / 3) * 2 - 1, ui->col / 4 - 1, "0");
    mvprintw(ui->row / 3, ui->col / 4 - my_find_digits(ui->result->data[WPM_MAX]), "%d", ui->result->data[WPM_MAX]);
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

