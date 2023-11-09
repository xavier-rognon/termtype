/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** result
*/

#include "../../../include/include.h"
#include <curses.h>

result_t *init_result(int sentence_length, int col, int row)
{
    result_t *result = malloc(sizeof(result_t));

    result->time_upto_word = malloc(sizeof(int) * sentence_length);
    result->wpm_per_word = malloc(sizeof(int) * sentence_length);
    result->wpm_raw_per_word = malloc(sizeof(int) * sentence_length);
    result->graph_point_row = NULL;
    result->graph_point_col = NULL;
    result->current_word = 0;
    result->data[NB_ERRORS] = 0;
    result->data[INCORRECT] = 0;
    result->graph = newwin(row / 3, col / 2, row / 3, col / 4 + col / 16);
    box(result->graph, 0, 0);
    keypad(result->graph, true);
    return result;
}

void reset_result(result_t *result, int sentence_length)
{
    free(result->time_upto_word);
    free(result->wpm_per_word);
    free(result->wpm_raw_per_word);
    free(result->graph_point_col);
    free(result->graph_point_row);
    result->graph_point_col = NULL;
    result->graph_point_row = NULL;
    result->time_upto_word = malloc(sizeof(int) * sentence_length);
    result->wpm_per_word = malloc(sizeof(int) * sentence_length);
    result->wpm_raw_per_word = malloc(sizeof(int) * sentence_length);
    result->data[NB_ERRORS] = 0;
    result->current_word = 0;
}

void free_result(result_t *result)
{
    free(result->time_upto_word);
    free(result->wpm_per_word);
    free(result->wpm_raw_per_word);
    if (result->graph_point_col != NULL)
        free(result->graph_point_col);
    if (result->graph_point_row != NULL)
        free(result->graph_point_row);
    free(result);
}
