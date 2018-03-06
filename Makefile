##
## EPITECH PROJECT, 2018
## PSU_2017_malloc
## File description:
## Epitech 2nd Year project for recode functions use for allocation
##

CC	=	gcc -shared

RM	=	rm -f

NAME	=	libmy_malloc.so

SRC	=	./src/malloc.c			\
		./src/block_tools.c		\
		./src/free.c			\
		./src/realloc.c			\
		./src/calloc.c			\
		./src/show_alloc_mem.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -I./include -fPIC -g3

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		clean fclean re all
