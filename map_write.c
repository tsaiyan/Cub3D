//
//  ft_map_parcer.c
//  cub3d
//
//  Created by Torres Saiyan on 1/26/21.
//  Copyright © 2021 21school. All rights reserved.
//

#include "cub3d.h"
char	**make_map(t_list **head, int size, t_all *all)
{
	char	  **map = ft_calloc(size + 1 - all->map.total_lines_before_map, sizeof(char *));
	int		  i = -1;
	t_list	*tmp = *head;
	int count = all->map.total_lines_before_map;
	while (count--)
		tmp = tmp->next;
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
		config_map(all, line);
		ft_lstadd_back(&head, ft_lstnew(line));
	}
	if (!check_ways(all))
	{
		all->map.error = 1;
		return;
	}
	ft_lstadd_back(&head, ft_lstnew(line));
	all->array = *make_map(&head, ft_lstsize(head), all);
}
