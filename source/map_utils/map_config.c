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
#define CMP ft_strncmp
#define WR write_resolution
#define WW write_ways
#define EXIT ft_exit

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
		EXIT("bad resolution", all);
	if (all->win.h <= 0 || all->win.w <= 0)
		EXIT("bad resolution", all);
	all->map.total_lines_before_map++;
	if (all->win.w > w && all->argc == 2)
		all->win.w = w;
	if (all->win.h > h && all->argc == 2)
		all->win.h = h;
	all->win.flag = 1;
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
		EXIT("bad chars in way for texture", all);
	if (flag == 1)
		all->no.way = ft_strdup(str);
	else if (flag == 2)
		all->so.way = ft_strdup(str);
	else if (flag == 3)
		all->we.way = ft_strdup(str);
	else if (flag == 4)
		all->ea.way = ft_strdup(str);
	else if (flag == 5)
		all->sp.way = ft_strdup(str);
	else if (flag == 6)
	{
		all->map.floor_color = ft_strdup(str);
		all->fl.flag = 1;
	}
	else if (flag == 7)
	{
		all->map.sky_color = ft_strdup(str);
		all->c.flag = 1;
	}
	all->map.total_lines_before_map++;
}

/*
** определяет флаги для записи путей структур во vv
*/

void	config_map(t_all *s, char *str)
{
	if (str[0] == '\0')
		s->map.total_lines_before_map++;
	else if (*str == 'R')
		(s->win.flag) ? EXIT("double defination res", s) : WR(s, (str + 1));
	else if (!CMP(str, "NO ", 3))
		(s->no.way) ? EXIT("double defination NO", s) : WW(s, (str + 2), 1);
	else if (!CMP(str, "SO ", 2))
		(s->so.way) ? EXIT("double defination SO", s) : WW(s, (str + 2), 2);
	else if (!CMP(str, "WE ", 2))
		(s->we.way) ? EXIT("double defination WE", s) : WW(s, (str + 2), 3);
	else if (!CMP(str, "EA ", 2))
		(s->ea.way) ? EXIT("double defination EA", s) : WW(s, (str + 2), 4);
	else if (!CMP(str, "S ", 2))
		(s->sp.way) ? EXIT("double defination S", s) : WW(s, (str + 1), 5);
	else if (!CMP(str, "F ", 2))
		(s->fl.flag) ? EXIT("double defination FL", s) : WW(s, (str + 1), 6);
	else if (!CMP(str, "C ", 2))
		(s->c.flag) ? EXIT("double defination C", s) : WW(s, (str + 1), 7);
	else if (!check_ways(s, 2))
		ft_exit("bad string in map", s);
}

/*
** проверяет, что все пути были записаны
*/

int		check_ways(t_all *all, int flag)
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
	{
		if (flag == 1)
			EXIT("BAD WAY FOR TEXTURES!", all);
		else
			return (0);
	}
	return (1);
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
