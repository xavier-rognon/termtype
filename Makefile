##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## do something apparently
##

SRC		=	./src/main.c													\
			./src/parser/parser_language.c									\
			./src/parser/free_parser.c										\
			./src/debug/my_show_word_array.c								\
			./src/curses/curses.c											\
			./src/curses/start.c											\
			./src/curses/test.c												\
			./src/curses/free_ui.c											\
			./src/curses/language.c											\
			./src/curses/input.c											\
			./src/curses/variant.c											\
			./src/curses/special_character.c								\
			./src/curses/result/result.c									\
			./src/curses/result/calculs.c									\
			./src/curses/result/resutl_display.c							\
			./src/curses/result/graph/place_point.c							\
			./src/player/free_player.c										\
			./src/player/player_init.c										\
			./src/utils/strlen_til_c.c										\
			./src/utils/exit_with_message.c									\
			./src/utils/my_str_to_word_array.c								\
			./src/utils/my_arrlen.c											\
			./src/utils/free_array.c										\
			./src/utils/my_strcat.c											\
			./src/utils/my_strcpy.c											\
			./src/utils/my_realloc.c										\
			./src/utils/my_char_isprintable.c								\
			./src/utils/my_find_digits.c									\
			./src/utils/clear_window.c										\

OBJ		=	$(SRC:.c=.o)

NAME	=	termtype

FLAG	=	-W -Wall -Wextra -Wpedantic -g -lncursesw -lm

CFLAGS	+=	$(FLAG)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) -I include $(FLAG)

all:		$(NAME)

clean:
	rm -f $(OBJ)

fclean: 	clean
	rm -f $(NAME) lib/my.a lib/printf.a

re:    		fclean all

mouli:
	make re --silent make fclean --silent make --silent make clean --silent

cs:
	coding-style . .
	cat coding-style-reports.log
	rm -f coding-style-reports.log
