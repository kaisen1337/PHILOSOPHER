# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/24 14:07:40 by nkasimi           #+#    #+#              #
#    Updated: 2025/03/19 17:16:50 by nkasimi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc -g
FLAGS = -Wall -Wextra -Werror 

SRC = main.c ft_init.c ft_mutex.c check_error.c philo_routing.c ft_utils.c allocate_mem.c
CMN = ft_printf.c  ft_atoi.c ft_time.c
# atoi.c ;
OPJ = $(SRC:.c=.o) $(CMN:.c=.o)

all: $(NAME)

$(NAME): $(OPJ)
	$(CC) $(FLAGS) $(OPJ) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
		rm -f $(OPJ)
fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OPJ)
