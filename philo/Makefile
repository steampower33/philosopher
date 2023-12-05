# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 14:03:21 by seunlee2          #+#    #+#              #
#    Updated: 2023/12/05 14:14:31 by seunlee2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS =	main/philo.c \
		main/philo_work.c \
		main/init.c \
		util/free.c \
		util/ft_atoi.c \
		util/time.c \
		util/error.c \
		util/ft_strncmp.c \

OBJS = $(SRCS:.c=.o)
CC = cc
INC = -I./include
CFLAGS = -Wall -Wextra -Werror -pthread
LDFLAGS = -pthread
%.o: %.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE)

.PHONY: all clean fclean re
