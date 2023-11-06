/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** calculs
*/

#include "../../../include/include.h"

int get_raw_wpm(result_t *result, int input_lenght)
{
    return (((float)input_lenght / 5) / ((float)(result->time_upto_word[result->current_word] + 1) / 60000));
}

int get_wpm(result_t *result, int input_lenght)
{
    int top_part = (((float)input_lenght / 5) - result->data[INCORRECT]);

    if (top_part <= 0)
        return 0;
    return round(top_part / ((float)(result->time_upto_word[result->current_word]) / 60000));
}

int get_accuracy(result_t *result, int input_lenght)
{
    return ((1 - (result->data[NB_ERRORS] / input_lenght)) * 100);
}

int get_max_wpm(result_t *result, int input_lenght)
{
    int wpm_max = 0;

    for (int i = 0; i < result->current_word; i++)
        if (result->wpm_raw_per_word[i] > wpm_max)
            wpm_max = result->wpm_raw_per_word[i];
    return wpm_max;
}

long long get_time_millisecond(void)
{
    struct timeval te;
    long long milliseconds;

    gettimeofday(&te, NULL);
    milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
    return milliseconds;
}

