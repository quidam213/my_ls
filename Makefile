##
## EPITECH PROJECT, 2025
## my_ls
## File description:
## Makefile
##

CFILES = $(shell find ./src -name "*.c")

CFLAGS = -Wall -Wextra -Werror

NAME = my_ls

all:
	gcc -o $(NAME) $(CFILES) $(CFLAGS)

clean:
# rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
