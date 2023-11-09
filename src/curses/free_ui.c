/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** free_ui
*/

#include "../../include/include.h"

void free_ui(ui_t *ui)
{
    free_parser(ui->parser);
    free_result(ui->result);
    language_free(ui->language);
    free_array(ui->sentence_arr);
    free_array(ui->top_bar_button);
    for (int i = 0; ui->top_bar_option[i] != NULL; i++)
        free_array(ui->top_bar_option[i]);
    free(ui->top_bar_option);
    free(ui);
}
