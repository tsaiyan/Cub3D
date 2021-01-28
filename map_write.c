/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaiyan <tsaiyan@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 18:29:13 by tsaiyan           #+#    #+#             */
/*   Updated: 2021/01/28 18:29:15 by tsaiyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

/*
** запись карты через листы минус строки конфига
*/

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
	return (map);
}

/*
** считывание файла и его запись
** проверка путей к текстурам
** запись карты без конфига
** запуск проверки карты
*/

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
	all->array = make_map(&head, ft_lstsize(head), all);
}
