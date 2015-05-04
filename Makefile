# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/04 17:53:41 by qmuntada          #+#    #+#              #
#    Updated: 2015/05/04 18:02:28 by qmuntada         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RT
CFLAGS = -Wall -Werror -Wextra
SRC = display.c env.c event.c get.c get2.c inter.c light.c light2.c main.c \
	  obj.c parser.c pixel.c reader.c shadows.c
OBJ = $(SRC:.c=.o)
MLX = minilibx_macos
LFT = libft

all : $(NAME)

$(NAME) : $(LFT) $(MLX)
	@make -C $(LFT)
	@make -C $(MLX)
	@gcc $(CFLAGS) -c $(SRC)
	@gcc -o $(NAME) $(OBJ) -L $(LFT) -lft -L $(MLX) -lmlx -framework OpenGl -framework AppKit

clean :
	@echo "Removing object files ..."
	@rm -f $(OBJ)

fclean : clean
	@echo "Removing $(NAME) ..."
	@rm -f $(NAME)

re : fclean all
