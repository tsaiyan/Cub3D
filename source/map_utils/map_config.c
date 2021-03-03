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
** записывает разрешение, пропускает пробелы через atoi
** увеличивает счетчик линий до карты
** проверяет максимальное разрешение, которое соотвествует моему ноуту
*/

void	write_resolution(t_all *all, char *str)
{
	int h;
	int w;

	h = 0;
	w = 0;
	mlx_get_screen_size(&w, &h);
	all->win.w = ft_atoi(str++);
	while (ft_isdigit(*str))
		str++;
	if (*str == 32)
		all->win.h = ft_atoi(str);
	else
		ft_exit("bad resolution", all);
	all->map.total_lines_before_map++;
	if (all->win.w > w)
		all->win.w = w;
	if (all->win.h > h)
		all->win.h = h;
}

/*
** записывает пути к текстурам по флагу
** проверяет синтаксис пути
** пропускает пробелы
*/

void	write_ways(t_all *all, char *str, int flag)
{
	while (*str == ' ')
		str++;
	if (flag < 6 && str[0] != '.' && str[1] != '/')
		ft_exit("bad chars in way for texture", all);
	if (flag == 1)
		all->no.way = str;
	else if (flag == 2)
		all->so.way = str;
	else if (flag == 3)
		all->we.way = str;
	else if (flag == 4)
		all->ea.way = str;
	else if (flag == 5)
		all->sp.way = str;
	else if (flag == 6)
		all->map.floor_color = str;
	else if (flag == 7)
		all->map.sky_color = str;
	all->map.total_lines_before_map++;
}

/*
** определяет флаги для записи путей структур во write_ways
*/

void	config_map(t_all *all, char *str)
{
	if (str[0] == '\0')
		all->map.total_lines_before_map++;
	else if (*str == 'R')
		write_resolution(all, (str + 1));
	else if (*str == 'N' && *(str + 1) == 'O')
		write_ways(all, (str + 2), 1);
	else if (*str == 'S' && *(str + 1) == 'O')
		write_ways(all, (str + 2), 2);
	else if (*str == 'W' && *(str + 1) == 'E')
		write_ways(all, (str + 2), 3);
	else if (*str == 'E' && *(str + 1) == 'A')
		write_ways(all, (str + 2), 4);
	else if (*str == 'S' && *(str + 1) == 32)
		write_ways(all, (str + 1), 5);
	else if (*str == 'F' && *(str + 1) == 32)
		write_ways(all, (str + 1), 6);
	else if (*str == 'C' && *(str + 1) == 32)
		write_ways(all, (str + 1), 7);
}

/*
** проверяет, что все пути были записаны
*/

void	check_ways(t_all *all)
{
	if (!all->ea.way || \
		!all->so.way || \
		!all->we.way || \
		!all->no.way || \
		!all->sp.way || \
		!all->win.h || \
		!all->win.w || \
		!all->map.floor_color || \
		!all->map.sky_color)
		ft_exit("BAD WAY FOR TEXTURES!", all);
}

/*
** записывает цвет пола
** выдает предупреждение, если int пола превышает 255
*/

void	floor_color(t_fl *strct, char *str)
{
	int	res;

	res = 0;
	while (*str == 32)
		str++;
	while (ft_isdigit(*str))
		res = res * 10 + (*str++ - 48);
	strct->r = res;
	res = 0;
	while (*str == 32 || *str == ',')
		str++;
	while (ft_isdigit(*str))
		res = res * 10 + (*str++ - 48);
	strct->g = res;
	res = 0;
	while (*str == 32 || *str == ',')
		str++;
	while (ft_isdigit(*str))
		res = res * 10 + (*str++ - 48);
	strct->b = res;
	if (*str)
		ft_putstr_fd("ATTENTION: too long color F/C\n", 1);
	if (strct->r > 255 || strct->b > 255 || strct->g > 255)
		write(1, "ATTENTION: color int more than 255 \n", 37);
}
