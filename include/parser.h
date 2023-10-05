/*
** EPITECH PROJECT, 2023
** PARSER_H_
** File description:
** parser
*/


#ifndef PARSER_H_
    #define PARSER_H_

    #define BASE_LANGUAGE = "../../asset/english.json"

typedef struct parser_s {
    char *name;
    char *sentence;
}parser_t;

parser_t *parser_language(char *path);
void free_parser(parser_t *parser);
#endif /* PARSER_H_ */
