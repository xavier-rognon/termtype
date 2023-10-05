/*
** EPITECH PROJECT, 2023
** termtype
** File description:
** free_parser
*/

#include "../../include/include.h"

void free_parser(parser_t *parser)
{
    free(parser->sentence);
    free(parser->name);
    free(parser);
}
