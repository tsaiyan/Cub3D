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
** функция, помещающая изначальные значения в структуру
** (от англ. put in) - класть
*/

void	ft_putin(t_all *all)
{
	all->fl.flag = 0;
	all->c.flag = 0;
	all->win.flag = 0;
	all->map.sp_count = 0;
	all->arrrecuv = NULL;
	all->array = NULL;
	all->win.w = 0;
	all->win.h = 0;
	all->no.way = NULL;
	all->so.way = NULL;
	all->we.way = NULL;
	all->ea.way = NULL;
	all->sp.way = NULL;
	all->map.floor_color = NULL;
	all->map.sky_color = NULL;
	all->map.total_lines_before_map = 0;
	all->plr.plook = 0;
	all->map.lines = 0;
	all->map.y = 0;
	all->map.x = 0;
	all->plr.y = 0;
	all->plr.x = 0;
	all->array = NULL;
	all->arrrecuv = NULL;
	all->sprite = NULL;
}
