/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** result_new_word
*/

#include "../../../include/include.h"

void result_new_word(result_t *result, int input_lenght)
{
    result->time_upto_word[result->current_word] = time(NULL) - result->time_start_test;
    result->wpm_per_word[result->current_word] = get_wpm(result, input_lenght);
}
