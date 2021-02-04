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


//void	scale_map(t_struct *map)
//{
//	int start = 100;
//	int x;
//	int y = map->y * SCALE;
//		while (y < (map->y * SCALE + SCALE))
//		{
//			x = map->x * SCALE;
//			while(x < (map->x * SCALE + SCALE))
//				mlx_pixel_put(map->mlx, map->win, (x++ + start), (y + start), 0xFFFFFF);
//			y++;
//		}
//}



int visual_map(t_all *all)
{
	int y = 0;
	int x = 0;
	void    *mlx;
	void    *win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 400, 400, "Hello world!");
	while (all->array[y])
	{
		while(all->array[y][x])
		{
			if (all->array[y][x] == '1')
				mlx_pixel_put(mlx, win, x++, y, 0xFFFFFF);
			if (all->array[y][x] == 'N')
//			{
//				if (map->py == 0 && map->px == 0)
//				{
//					map->py = map->y;
//					map->px = map->x;
//				}
//				//scale_player(map);
//			}
			x++;
		}
		y++;
	}
	mlx_loop(mlx);
	return (0);
}
