/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** place_point
*/

#include "../../../../include/include.h"
#include <curses.h>
#include <stdbool.h>
#include <stdlib.h>

void get_point_position(ui_t *ui)
{
    int index = 0;
    int i = 0;
    int graph_height = ui->row / 3;
    int graph_width = (ui->col >> 1) - 2;
    long long test_time_ms = ui->result->time_upto_word[ui->result->current_word - 1];
    int temp_col = -1;

    if (ui->result->wpm_per_word[index] == 0)
        ui->result->wpm_per_word[index] = ui->result->wpm_per_word[index + 1];
    ui->result->graph_point_col = malloc(sizeof(int) * ui->result->current_word + 3);
    ui->result->graph_point_row = malloc(sizeof(int) * ui->result->current_word + 3);
    ui->result->graph_point_col[i] = 1;
    ui->result->graph_point_row[i] = graph_height + 1 - graph_height *
        ((float)ui->result->wpm_per_word[index] / (ui->result->data[WPM_MAX] + 1));
    if (ui->result->graph_point_row[i] == 0)
        ui->result->graph_point_row[i]++;
    while (i < ui->result->current_word && ui->result->graph_point_col[i] < ui->col / 2) {
        if (ui->result->graph_point_col[i] != temp_col) {
            temp_col = ui->result->graph_point_col[i];
            i++;
        }
        ui->result->graph_point_col[i] = graph_width * ((double)ui->result->time_upto_word[index] / test_time_ms);
        if (ui->result->graph_point_col[i] == 0)
            ui->result->graph_point_col[i] = graph_width;
        ui->result->graph_point_row[i] = graph_height + 1 - graph_height *
            ((float)ui->result->wpm_per_word[index] / (ui->result->data[WPM_MAX] + 1));
        index++;
    }
}

int find_difference_between_point(int *points, int i)
{
    return points[i] - points[i - 1];
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

    get_point_position(ui);
    while (i <= ui->result->current_word) {
        diff[0] = find_difference_between_point(ui->result->graph_point_col, i);
        diff[1] = find_difference_between_point(ui->result->graph_point_row, i);
        draw_line(ui, diff, i);
        i++;
    }
}

