# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 14:03:21 by seunlee2          #+#    #+#              #
#    Updated: 2023/11/21 16:38:10 by seunlee2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = main/philo.c \
		util/ft_atoi.c \
		

OBJS = $(SRCS:.c=.o)
CC = cc
INC = -I./include
CFLAGS = -Wall -Wextra -Werror $(INC) -pthread -fsanitize=address

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE)

.PHONY: all clean fclean re
