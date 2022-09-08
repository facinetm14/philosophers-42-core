# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fakouyat <fakouyat@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/07 14:32:58 by fakouyat          #+#    #+#              #
#    Updated: 2022/09/07 14:32:58 by fakouyat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = srcs/check_input.c\
	srcs/utils.c\
	srcs/routine.c\
	srcs/timing.c\
	srcs/utils_prog.c\
	srcs/supervisor.c\
	srcs/utils_philo.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror -pthread

all : $(NAME)

$(NAME) :
	$(CC) $(CFLAGS) main.c $(SRCS) -o $(NAME)
	
debug : 
	$(CC) $(CFLAGS) -fsanitize=thread -g main.c $(SRCS) -o $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re