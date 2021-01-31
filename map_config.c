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

int	write_resolution(t_all *all, char *str)
{
	all->win.gorisont = ft_atoi(str++);
	while(ft_isdigit(*str))
		str++;
	if (*str == 32)
		all->win.vert = ft_atoi(str);
	else
	{
		all->map.error = 1;
		return (0);
	}
	all->map.total_lines_before_map++;
	return (1);
}

int write_ways(t_all *all, char *str, int flag)
{
	str++;
	if (1 < flag && flag < 6 && str[0] != '.' && str[1] != '/')
		return (0 * (all->map.error = 1));
	if (flag == 1)
		all->map.no_way = str;
	else if (flag == 2)
		all->map.so_way = str;
	else if (flag == 3)
		all->map.we_way = str;
	else if (flag == 4)
		all->map.ea_way = str;
	else if (flag == 5)
		all->map.s_way = str;
	else if (flag == 6)
		all->map.floor_color = str;
	else if (flag == 7)
		all->map.sky_color = str;
	all->map.total_lines_before_map++;
	return (1);
}

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

int	check_ways(t_all *all)
{
	if (!all->map.no_way || \
		!all->map.so_way || \
		!all->map.we_way || \
		!all->map.ea_way || \
		!all->map.s_way || \
		!all->win.vert || \
		!all->win.gorisont || \
		!all->map.floor_color || \
		!all->map.sky_color)
	{
		write(1, "BAD WAY FOR TEXTURES!\n", 11);
		return (0);
	}
	return (1);
}

