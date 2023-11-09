/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** place_point
*/

#include "../../../../include/include.h"

void get_point_position(ui_t *ui)
{
    int graph_width = ui->col / 2 - 2;
    int graph_height = (ui->row / 3) - 2;
    int i = 0;
    int index = 0;
    int prev_graph_point_col = 0;

    ui->result->graph_point_col = malloc(sizeof(int) * ui->result->current_word);
    ui->result->graph_point_row = malloc(sizeof(int) * ui->result->current_word);
    while (i < ui->result->current_word) {
        if (i == 0)
            ui->result->graph_point_col[i] = 1;
        else
            ui->result->graph_point_col[i] = (int)(ui->result->time_upto_word[index] * graph_width) /
                ui->result->time_upto_word[ui->result->current_word - 1];
        ui->result->graph_point_row[i] = graph_height - (ui->result->wpm_per_word[index] * graph_height) / ui->result->data[WPM_MAX];
        if (prev_graph_point_col != ui->result->graph_point_col[i])
            i++;
        index++;
    }
}

void slope_neg(ui_t *ui, float m, int i)
{
    int x = ui->result->graph_point_col[i - 1];
    int y = ui->result->graph_point_row[i - 1];
    float m_dup = m;

    while (x < ui->result->graph_point_col[i]) {
        mvwprintw(ui->result->graph, y, x, "+");
        if (m <= -1) {
            y--;
            m++;
        }
        if (m > -1) {
            x++;
            m += m_dup;
        }
    }
    mvwprintw(ui->result->graph, y, x, "+");
}

void slope_pos(ui_t *ui, float m, int i)
{
    int x = ui->result->graph_point_col[i - 1];
    int y = ui->result->graph_point_row[i - 1];
    float m_dup = m;

    while (x < ui->result->graph_point_col[i]) {
        mvwprintw(ui->result->graph, y, x, "+");
        if (m >= 1) {
            y++;
            m--;
        }
        if (m < 1) {
            x++;
            m += m_dup;
        }
    }
    mvwprintw(ui->result->graph, y, x, "+");
}

void draw_line(ui_t *ui, int *diff, int i)
{
    float m = (float)diff[1] / diff[0];

    if (diff[0] == 1)
        mvwprintw(ui->result->graph, ui->result->graph_point_row[i - 1], ui->result->graph_point_col[i - 1], "+");
    if (m >= 0)
        slope_pos(ui, m, i);
    else
        slope_neg(ui, m, i);
}

void draw_point_temp(ui_t *ui)
{
    int diff[2];
    int i = 1;

    if (ui->result->current_word == 0)
        return;
    get_point_position(ui);
    while (i < ui->result->current_word) {
        diff[0] = ui->result->graph_point_col[i] - ui->result->graph_point_col[i - 1];
        diff[1] = ui->result->graph_point_row[i] - ui->result->graph_point_row[i - 1];
        draw_line(ui, diff, i);
        i++;
    }
}

