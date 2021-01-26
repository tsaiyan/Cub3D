NAME = cub3d

RM = rm -f

CC = gcc -Wall -Wextra -Werror

.PHONY:		all clean fclean re

all: $(NAME)

$(NAME): parcer_map.h main.c
	${RM} $(NAME)
	clang main.c libft/libft.a  get_next_line/get_next_line.c get_next_line/get_next_line_utils.c visual_map.c libmlx.dylib -framework OpenGL -framework AppKit -o $(NAME)
	./cub3d map.cub
clean:
	${RM} $(NAME)

fclean: clean
	${RM} $(NAME)

re: fclean all
