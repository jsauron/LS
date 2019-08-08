# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsauron <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/01 18:30:18 by jsauron           #+#    #+#              #
#    Updated: 2019/08/08 18:00:47 by jsauron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRCS_DIR = srcs/

SRC = srcs/ft_ls.c \
	  srcs/ft_ls_2.c \
		srcs/utils.c	\
		srcs/sort.c \
		srcs/parsing.c \
		srcs/error.c \
		srcs/init.c	\
		srcs/display.c	\
	srcs/ft_strmode.c

OBJS = $(SRC:.c=.o)

INCLUDES = includes/

DONE = "\033[35m LS READY \033[0m"

all: lib $(NAME)

$(NAME):$(OBJS)
	@gcc -Wall -Wextra -Werror -o $(NAME) libft/libft.a $(OBJS) -I $(INCLUDES)  -g -fsanitize=address
	@echo $(DONE)

lib:
	@make -j -C libft/ libft.a

%.o: %.c $(INCLUDES)ft_ls.h
	@gcc -Wall -Wextra -Werror -g -o $@ -c $<

clean:
	@rm -f $(OBJS) && make -C libft/ clean

fclean: clean
	@rm -f $(NAME) && make -C libft/ fclean

re: fclean
	@$(MAKE)

.PHONY: all clean fclean re
