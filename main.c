//
//  main.c
//  cub3d
//
//  Created by Torres Saiyan on 1/20/21.
//  Copyright © 2021 21school. All rights reserved.
//

#include <fcntl.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include <stdio.h>

void	make_map(t_list **head, int size)
{
	char **map = ft_calloc(size + 1, sizeof(char *));
	int i = -1;
	t_list *tmp = *head;
	
	while(tmp)
	{
		map[++i] = tmp->content;
		tmp = tmp->next;
	}
	i = 0;
	while (*map[i])
	{
		ft_putendl(map[i++]);
	}
}

int main(int argc, char **argv)
{
	int fd = open(argv[1], O_RDONLY);
	char *line = NULL;
	t_list *head = NULL;
	
	while(get_next_line(fd, &line))
	{
		ft_lstadd_back(&head, ft_lstnew(line));
	}
	ft_lstadd_back(&head, ft_lstnew(line));
	make_map(&head, ft_lstsize(head));
	return 0;
}
