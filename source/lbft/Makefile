SRCS = ft_atoi.c ft_memmove.c ft_bzero.c ft_memset.c ft_isalnum.c ft_strchr.c ft_isalpha.c ft_strlcat.c ft_isascii.c ft_strlcpy.c ft_isdigit.c ft_strlen.c ft_isprint.c ft_strncmp.c ft_memccpy.c ft_strnstr.c ft_memchr.c  ft_strrchr.c ft_memcmp.c  ft_tolower.c ft_memcpy.c  ft_toupper.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putendl.c

BNS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS = $(SRCS:.c=.o)

BNSOBJS =  $(BNS:.c=.o)

NAME = libft.a

RM = rm -f

CC = gcc -Wall -Wextra -Werror

.PHONY:		all clean fclean re

all: $(NAME) $(SRCS) libft.h $(BNS)

$(NAME): $(OBJS) $(BNS)
	ar rc $(NAME) $?
	ranlib $(NAME)

bonus: $(OBJS) $(BNSOBJS)
	ar rc $(NAME) $?
	ranlib $(NAME)

.c.o:
	$(CC) -c $< -o $@

clean:
	${RM} $(OBJS)
	${RM} $(BNSOBJS)

fclean: clean
	${RM} $(NAME)

re: fclean all











