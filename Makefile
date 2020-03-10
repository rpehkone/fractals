# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/30 20:09:24 by rpehkone          #+#    #+#              #
#    Updated: 2020/03/10 20:20:02 by rpehkone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractal
LIB = libft/libft.a
HEADERS = /usr/local/include libft mlx_wrappers src
MAIN_FILES = main.c handle_hook.c input_state.c main_loop.c image.c
FILES = fractal.c
.PHONY: clean fclean re all

all: $(NAME)

$(NAME):
	@make re -C libft
	gcc -Wall -Wextra -Werror -O3 $(addprefix mlx_wrappers/, $(MAIN_FILES)) $(addprefix src/, $(FILES)) $(LIB) $(addprefix -I , $(HEADERS)) -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit -o $(NAME)

clean:
	@make clean -C libft

fclean: clean
	@make fclean -C libft
	rm -f $(NAME)

re: fclean
	make all
