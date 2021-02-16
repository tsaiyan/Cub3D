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

void ft_putin(t_all *all)
{
	puts("ft_putin");
	all->win.w = 0;
	all->win.h = 0;
	all->map.error = 0;
	all->map.no_way = NULL;
	all->map.so_way = NULL;
	all->map.we_way = NULL;
	all->map.ea_way = NULL;
	all->map.s_way = NULL;
	all->map.floor_color = NULL;
	all->map.sky_color = NULL;
	all->map.total_lines_before_map = 0;
	all->plr.plook = 0;
	all->map.lines = 0;
	all->map.y = 0;
	all->map.x = 0;
	all->plr.y = 0;
	all->plr.x = 0;
	all->win.bpp = 4;
	all->plr.start = 1;
	all->plr.end = 0;
}
