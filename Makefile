OBJTS =  ft_putin.c map.cub cub3d.h map_validate.c map_write.c map_config.c error.c libft/libft.a get_next_line/get_next_line.c get_next_line/get_next_line_utils.c libmlx.dylib

NAME = cub3d

RM = rm -f

CC = gcc -Wall -Wextra -Werror

.PHONY:		all clean fclean re

all: $(NAME)

$(NAME): $(OBJTS) main.c cub3d.h
	$(MAKE) bonus -C ./libft
	clang main.c $(OBJTS) -framework OpenGL -framework AppKit
	./a.out map.cub
clean:
	${RM} $(NAME)
	$(MAKE) clean -C ./libft

fclean: clean
	${RM} $(NAME)
	$(MAKE) fclean -C ./libft

re: fclean all
