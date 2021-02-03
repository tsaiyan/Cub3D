OBJTS =  ft_putin.c map.cub cub3d.h map/map_validate.c map/map_write.c map/map_config.c map/error.c lbft/libft.a gnl/get_next_line.c gnl/get_next_line_utils.c libmlx.dylib

NAME = cub3d

RM = rm -f

CC = gcc -Wall -Wextra -Werror

.PHONY:		all clean fclean re

all: $(NAME)

$(NAME): $(OBJTS) main.c cub3d.h
	$(MAKE) bonus -C ./lbft
	clang main.c $(OBJTS) -framework OpenGL -framework AppKit
	./a.out map.cub
clean:
	${RM} $(NAME)
	$(MAKE) clean -C ./lbft

fclean: clean
	${RM} $(NAME)
	$(MAKE) fclean -C ./lbft

re: fclean all
