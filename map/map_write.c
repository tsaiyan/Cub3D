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
** запись карты через листы без строк конфига
*/

char	**make_map(t_list **head, int size, t_all *all)
{
	char	  **map;
	int		  i;
	t_list	*tmp;

	map = ft_calloc(size + 1 - all->map.total_lines_before_map, sizeof(char *));
	i = 0;
	tmp = *head;
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


/*
** проверка расширения файла
** считывание файла и его запись
** проверка путей к текстурам
** запись карты без конфига
** запуск проверки карты
*/

void	ft_map_parcer(t_all *all, char *argv)
{
	int		fd;
	char	*line;
	t_list	*head;
	size_t	i;

	line = NULL;
	head = NULL;
	fd = open(argv, O_RDONLY);
	i = ft_strlen(argv) - 1;
	if (argv[i] != 'b' || argv[i -1] != 'u' || argv[i - 2] != 'c' \
		|| argv[i - 3] != '.')
		ft_exit("bad map extention", all);
	while (get_next_line(fd, &line))
	{
		config_map(all, line);
		ft_lstadd_back(&head, ft_lstnew(line));
	}
	ft_lstadd_back(&head, ft_lstnew(line));
	all->array = make_map(&head, ft_lstsize(head), all);
	check_ways(all);
	close(fd);
}

void	write_player_pi(t_all *all)
{
	t_plr *plr;

	plr = &all->plr;
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

/*
** ищет игрока
** проверяет что он один и есть
*/

void	find_player(t_all *all)
{
	int y;
	int x;

	y = 0;
	while (all->array[y])
	{
		x = 0;
		while (all->array[y][x])
		{
			if (all->array[y][x] == 'N' || all->array[y][x] == 'S' || \
				all->array[y][x] == 'W' || all->array[y][x] == 'E')
			{
				if (all->plr.plook)
					ft_exit("double player in map", all);
				all->plr.plook = all->array[y][x];
				all->plr.y = y;
				all->plr.x = x;
			}
			if (all->array[y][x] == '2')
				all->map.sp_count++;
			x++;
		}
		y++;
	}
	if (!all->plr.plook)
		ft_exit("no player in map", all);
}
