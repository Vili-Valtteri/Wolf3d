# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/26 14:57:41 by vlaine            #+#    #+#              #
#    Updated: 2022/09/27 14:39:40 by vlaine           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
CC = gcc
LIB = libft/libft.a
DSYM = wolf3d.dSYM
INCLUDE = libft/
LIBMLX = libmlx.dylib
CFLAGS = -I $(INCLUDE) -Wall -Wextra -Werror -O2
SRCS = main.c wolf3d.c create_window.c inputs.c raycasting_wall.c\
draw_sprite.c casting_floor.c recon_types.c get_textures.c\
ai_bot_controller.c restart.c player_controller.c draw_minimap.c\
edit_map.c exit_program.c path_following.c path_functions.c check_neighbors.c\
ai_bot_anim.c inputs_move.c read_map.c recon_helper.c load_textures.c\
player_move.c sprite_helper.c wall_helper.c paeth_helper.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIB) $(LIBMLX) $(OBJS)
	$(CC) $(LIB) $(LIBMLX) $(OBJS) -o $(NAME) $(CFLAGS)

$(LIB):
	make -C libft

$(LIBMLX):
	make -C  minilibx
	mv minilibx/libmlx.dylib libmlx.dylib

clean:
	make -C libft clean
	make -C minilibx clean
	rm -rf $(DSYM)
	rm -f $(OBJS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)
	rm -f $(LIBMLX)

re: fclean all

.PHONY: all clean fclean re
