# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avast <avast@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/10 11:41:55 by avast             #+#    #+#              #
#    Updated: 2023/04/05 15:05:52 by avast            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRC = src/init_bonus.c \
	src/utils_bonus.c \
	src/process_bonus.c \
	src/main.c

OBJ = $(SRC:.c=.o)

INCLUDES = includes/philo_bonus.h \

CC = cc

FLAGS = -Wall -Wextra -Werror -g3 -pthread

SANITIZE = -fsanitize=thread

MAKEFLAGS += --no-print-directory

BLUE = \033[1;94m

PURPLE = \033[1;95m

GREEN = \033[1;92m

YELLOW = \033[1;93m

all: $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -I./includes -c $< -o $@

$(NAME): $(OBJ) $(LIBFT) $(INCLUDES)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@printf "$(YELLOW)------Compilation executed------\n\n"


clean:
	@/bin/rm -f $(OBJ)
	@printf "$(PURPLE)------Object files deleted-------\n\n"

fclean: clean
	@/bin/rm -f $(NAME)
	@printf "$(GREEN)----Executable files deleted-----\n\n"

re: fclean all

.PHONY : all clean fclean re

