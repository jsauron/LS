# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsauron <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/01 18:30:18 by jsauron           #+#    #+#              #
#    Updated: 2019/07/23 15:49:34 by jsauron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRCS_DIR = srcs/

SRC = srcs/ft_ls.c \
	  srcs/ft_ls_2.c \
	ft_strmode.c

OBJS = $(SRC:.c=.o)

INCLUDES = includes/

DONE = "\033[35m LS READY \033[0m"

all: lib $(NAME)

$(NAME):$(OBJS)
	@gcc -Wall -Wextra -Werror -o $(NAME) libft/libft.a $(OBJS) -I $(INCLUDES) -g -fsanitize=address
	@echo $(DONE)

lib:
	@make -j -C libft/ libft.a

%.o: %.c $(INCLUDES)ft_ls.h
	@gcc -Wall -Wextra -Werror -o $@ -c $<

clean:
	@rm -f $(OBJS) && make -C libft/ clean

fclean: clean
	@rm -f $(NAME) && make -C libft/ fclean

re: fclean
	@$(MAKE)

.PHONY: all clean fclean re
