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

int	write_resolution(t_all *all, char *str)
{
	all->win.w = ft_atoi(str++);
	while(ft_isdigit(*str))
		str++;
	if (*str == 32)
		all->win.h = ft_atoi(str);
	else
		ft_exit("bad resolution", all);
	all->map.total_lines_before_map++;
	if (all->win.w > 1920)
		all->win.w = 1920;
	if (all->win.h > 1200)
		all->win.h = 1200;
	return (1);
}

/*
** записывает пути к текстурам по флагу
** проверяет синтаксис пути
** пропускает пробелы
*/

int	write_ways(t_all *all, char *str, int flag)
{
	while(*str == ' ')
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
	return (1);
}

/*
** определяет флаги для записи путей структур во write_ways
*/

int	config_map(t_all *all, char *str)
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

	return (1);
}

/*
** проверяет, что все пути были записаны
*/

int	check_ways(t_all *all)
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
	while(*str == 32)
		str++;
	while(ft_isdigit(*str))
		res = res * 10 + (*str++ -  48);
	strct->r = res;
	res = 0;
	while(*str == 32 || *str == ',')
		str++;
	while(ft_isdigit(*str))
		res = res * 10 + (*str++ -  48);
	strct->g = res;
	res = 0;
	while(*str == 32 || *str == ',')
		str++;
	while(ft_isdigit(*str))
		res = res * 10 + (*str++ -  48);
	strct->b = res;
	if (*str)
		ft_putstr_fd("ATTENTION: too long color F/C\n", 1);
	if (strct->r > 255 || strct->b > 255 || strct->g > 255)
		write(1, "ATTENTION: color int more than 255 \n", 37);
}

/*
** функция экстренного завершения программы
** освобожает память, если она была аллоцирована
*/

void	ft_exit(char *str, t_all *all)
{
	ft_putstr_fd("ERROR!\n", 1);
	ft_putstr_fd(str, 1);
	write(1, "\n", 1);
	if (all->array)
		free(all->array);
	if(all->arrrecuv)
		free(all->arrrecuv);
	if(all)
		free(all);
	exit(1);
}
