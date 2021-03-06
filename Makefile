SOURCE = ./source
MMS = $(SOURCE)/mms
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

all: $(NAME) $(GNL)/get_next_line.h $(LIBFT)/libft.h $(SOURCE)/cub3d.h

$(NAME): $(OBJTS) 
	$(MAKE) -C $(MMS)
	$(MAKE) bonus -C $(LIBFT)
	$(CC) $(OBJTS) $(LIBFT)/libft.a $(MMS)/libmlx.a -framework OpenGL -framework AppKit -o $(NAME)
clean:
	$(MAKE) clean -C $(LIBFT)

fclean: clean
	${RM} $(NAME)
	$(MAKE) fclean -C $(LIBFT)
	$(MAKE) clean -C $(MMS)
run : $(NAME)
	./$(NAME) map.cub

re: fclean all
