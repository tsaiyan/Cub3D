SOURCE = ./source
UTILS = $(SOURCE)/other_utils
MAP_UT = $(SOURCE)/map_utils
CASTING = $(SOURCE)/casting
GNL = $(SOURCE)/gnl
LIBFT = $(SOURCE)/lbft

OBJTS =  $(CASTING)/cast_sprites.c  $(CASTING)/raycast_utils.c  $(CASTING)/raycasting.c  $(CASTING)/textures.c  $(GNL)/get_next_line_utils.c $(GNL)/get_next_line.c  $(MAP_UT)/map_check_around.c $(MAP_UT)/map_config.c $(MAP_UT)/map_utils.c $(MAP_UT)/map_write.c $(MAP_UT)/sprite_write.c $(SOURCE)/cub3d.c $(UTILS)/ft_putin.c $(UTILS)/movements.c $(UTILS)/screenshot.c

NAME = cub3d

RM = rm -f

CC = clang -Wall -Wextra -Werror

.PHONY:		all clean fclean re

all: $(NAME) $(GNL)/get_next_line.h $(LIBFT)/libft.h cub3d.h $(SOURCE)/cub3d.c

$(NAME): $(OBJTS) $(SOURCE)/cub3d.c $(SOURCE)/cub3d.h
	$(MAKE) bonus -C $(LIBFT)
	clang $(OBJTS) $(LIBFT)/libft.a $(SOURCE)/libmlx.a -framework OpenGL -framework AppKit -o $(NAME)
clean:
	${RM} $(NAME)
	$(MAKE) clean -C $(LIBFT)

fclean: clean
	${RM} $(NAME)
	$(MAKE) fclean -C $(LIBFT)
run : $(NAME)
	./$(NAME) map.cub

re: fclean all
