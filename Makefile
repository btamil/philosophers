# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tponnusa <tponnusa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/05 14:14:56 by tponnusa          #+#    #+#              #
#    Updated: 2023/10/13 15:41:17 by tponnusa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= philo

CC 			= cc -pthread

CFLAGS 		= -Wall -Wextra -Werror

SRC 		= 	philo_main.c philo_init.c philo_check.c \
				philo_utils.c philo_actions.c philo_exit.c
OBJ         =  $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): 	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all 	:	$(NAME)

clean	: 
			rm -f $(OBJ)

fclean	: 	clean
			rm -f $(NAME)

re 		: 	fclean all

.PHONY	:	all clean fclean re