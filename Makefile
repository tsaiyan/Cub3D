NAME = cub3d

RM = rm -f

CC = gcc -Wall -Wextra -Werror

.PHONY:		all clean fclean re

all: $(NAME)

$(NAME): cub3d.h main.c
	${RM} $(NAME)
	clang main.c libft/libft.a  get_next_line/get_next_line.c get_next_line/get_next_line_utils.c ft_map_parcer.c ft_check_map.c ft_putin.c  libmlx.dylib -framework OpenGL -framework AppKit -o $(NAME)
	./cub3d map.cub
clean:
	${RM} $(NAME)

fclean: clean
	${RM} $(NAME)

re: fclean all
