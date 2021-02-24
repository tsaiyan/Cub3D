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

void	map_utils(t_all *all)
{
	find_player(all);
	if (!all->plr.plook)
		ft_exit("no player in map", all);
	write_player_pi(all);
	floor_color(&all->fl, all->map.floor_color);
	floor_color(&all->c, all->map.sky_color);
	map_copy(all);
	map_check_around(all);
	sprite_init(all);
	sprite_write(all);
	sort_sprite(all);
	//mlx_get_screen_size(all->win.mlx, &all->win.max_h,  &all->win.max_w);
}
