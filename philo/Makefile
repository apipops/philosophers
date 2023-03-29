# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avast <avast@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/10 11:41:55 by avast             #+#    #+#              #
#    Updated: 2023/03/29 12:03:58 by avast            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = src/parsing.c \
	src/utils.c \
	src/main.c

OBJ = $(SRC:.c=.o)

INCLUDES = includes/philo.h \

CC = cc

FLAGS = -Wall -Wextra -Werror -g3

MAKEFLAGS += --no-print-directory

BLUE = \033[1;94m

PURPLE = \033[1;95m

GREEN = \033[1;92m

YELLOW = \033[1;93m

all: $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -I./includes -c $< -o $@

$(NAME): $(OBJ) $(LIBFT) $(INCLUDES)
	@$(CC) $(OBJ) -g3 -fsanitize=thread -pthread -o $(NAME)
	@printf "$(YELLOW)------Compilation executed------\n\n"


clean:
	@/bin/rm -f $(OBJ)
	@make clean -C $(LIBFTDIR)
	@printf "$(PURPLE)------Object files deleted-------\n\n"

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C $(LIBFTDIR)
	@printf "$(GREEN)----Executable files deleted-----\n\n"

re: fclean all

.PHONY : all clean fclean re

