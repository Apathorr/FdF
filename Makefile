# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsmith <rsmith@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/26 14:26:46 by rsmith            #+#    #+#              #
#    Updated: 2019/07/08 12:27:33 by rsmith           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = FdF

SRCDIR = ./sources/

SRC = draw.c \
	hooks.c\
	images.c \
	main.c \
	map.c \
	reader.c \

OBJECTS = $(SRC:.c=.o)

INC = Includes

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

FRAMEWORK = -framework OpenGL -framework AppKit

LIBFT = libft/libft.a

MLX = minilibx_macos/libmlx.a

all : $(NAME)

$(NAME):
	@make -C libft
	@make -C minilibx_macos
	@rm -rf
	@$(CC) $(CFLAGS) -c $(addprefix $(SRCDIR), $(SRC)) -I $(INC)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT) $(MLX) $(FRAMEWORK)

clean:

	@/bin/rm -f $(OBJECTS)
	@make -C libft clean
	@make -C minilibx_macos clean

fclean : clean
	rm -rf $(NAME)
	make -C libft fclean

re: clean all

 .PHONY: make, all, clean, fclean, re
