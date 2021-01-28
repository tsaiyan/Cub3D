//
//  ft_check_map.c
//  cub3d
//
//  Created by Torres Saiyan on 1/26/21.
//  Copyright © 2021 21school. All rights reserved.
//

#include "cub3d.h"

int	write_res(t_all *all, char *str)
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
	if (str[0] != '.' && str[1] != '/')
	{
		all->map.error = 1;
		puts("way error\n");
		return (0);
	}
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
	all->map.total_lines_before_map++;
	return (1);
}

int	config_map(t_all *all, char *str)
{
	if (str[0] == '\0')
		all->map.total_lines_before_map++;
	else if (*str == 'R')
		write_res(all, (str + 1));
	else if (*str == 'N' && *(str + 1) == 'O')
		write_ways(all, (str + 2), 1);
	else if (*str == 'S' && *(str + 1) == 'O')
		write_ways(all, (str + 2), 2);
	else if (*str == 'W' && *(str + 1) == 'E')
		write_ways(all, (str + 2), 3);
	else if (*str == 'E' && *(str + 1) == 'A')
		write_ways(all, (str + 2), 4);
	else if (*str == 'S')
		write_ways(all, (str + 1), 5);
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
		!all->win.gorisont)
	{
		write(1, "MAP ERROR!\n", 11);
		return (0);
	}
	return (1);
}
