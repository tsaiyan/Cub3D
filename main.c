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
#include "parcer_map.h"

char	**make_map(t_list **head, int size)
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
	return (map);
}

int main(int argc, char **argv)
{
	t_struct *map;
	int fd = open(argv[1], O_RDONLY);
	char *line = NULL;
	t_list *head = NULL;

	if (!(map = malloc(sizeof(t_struct))))
		return (-1);
	while(get_next_line(fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	//make_map(&head, ft_lstsize(head));
	map->array = make_map(&head, ft_lstsize(head));
	visual_map(map);
	return 0;
}
