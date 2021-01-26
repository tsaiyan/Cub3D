//
//  ft_map_parcer.c
//  cub3d
//
//  Created by Torres Saiyan on 1/26/21.
//  Copyright © 2021 21school. All rights reserved.
//

#include "cub3d.h"
char	**make_map(t_list **head, int size)
{
	char	  **map = ft_calloc(size + 1, sizeof(char *));
	int		  i = -1;
	t_list	*tmp = *head;

	while (tmp)
	{
		map[++i] = tmp->content;
		tmp= tmp->next;
	}
	i = -1;
	while (map[++i])
		ft_putendl(map[i]);
	return (map);
}

void	ft_map_parcer(t_all *all, char *argv)
{
	int fd = open(argv, O_RDONLY);
	char *line = NULL;
	t_list *head = NULL;

	while (get_next_line(fd, &line))
	{
		ft_check_map(all, line);
		ft_lstadd_back(&head, ft_lstnew(line));
	}
	ft_lstadd_back(&head, ft_lstnew(line));
	all->array = *make_map(&head, ft_lstsize(head));
}
