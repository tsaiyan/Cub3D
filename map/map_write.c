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


#include "../cub3d.h"

/*
** запись карты через листы минус строки конфига
*/

char	**make_map(t_list **head, int size, t_all *all)
{
	char	  **map = ft_calloc(size + 1 - all->map.total_lines_before_map, sizeof(char *));
	int		  i = 0;
	t_list	*tmp = *head;
	int count = all->map.total_lines_before_map;
	while (count--)
		tmp = tmp->next;
	while (tmp)
	{
		map[i++] = tmp->content;
		tmp= tmp->next;
		all->map.lines++;
	}
	return (map);
}

char	**map_copy(t_all *all)
{
	char **line;
	int j = 0;
	int i = all->map.lines;

	line = (char **)malloc(sizeof(char*) * (i + 1));
	line[i--] = NULL;
	while (i--)
	{
		line[j] = ft_strdup(all->array[j]);
		j++;
	}
	return(line);
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
	check_ways(all);
	ft_lstadd_back(&head, ft_lstnew(line));
	all->array = make_map(&head, ft_lstsize(head), all);
	all->arrrecuv = map_copy(all);
	close(fd);
}

void	write_player_pi(t_all *all)
{
	t_plr *plr = &all->plr;
	if (plr->plook == 'N')
	{
		plr->start = 0;
		plr->end = -1;
		plr->planeX = 0.66;
		plr->planeY = 0;
		plr->x += 0.5;
		plr->y += 0.5;
	}
	if (plr->plook == 'W')
		{
		plr->start = -1;
		plr->end = 0;
		plr->planeX = 0;
		plr->planeY = -0.66;
		plr->y += 0.5;
	}
	if (plr->plook == 'E')
	{
		plr->start = 1;
		plr->end = 0;
		plr->planeX = 0;
		plr->planeY = 0.66;
		plr->y += 0.5;
	}
	if (plr->plook == 'S')
		{
		plr->start = 0;
		plr->end = 1;
		plr->planeX = -0.66;
		plr->planeY = 0;
		plr->x += 0.5;
		plr->y += 0.5;
		}
}
