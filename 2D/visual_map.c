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

//рисуем карту

void	scale_map(t_all *all)
{
	int start = 100;
	int x;
	int y = all->map.y * SCALE;
		while (y < (all->map.y * SCALE + SCALE))
		{
			x = all->map.x * SCALE;
			while(x < (all->map.x * SCALE + SCALE))
				my_mlx_pixel_put(&all->dd, (x++ + start), (y + start), 0xFFFFFF);
			y++;
		}
}


// пускаем лучи

void	scale_player(t_all *all)
{
	t_plr ray = all->plr;
	int move = 100;
	ray.start = ray.dir - M_PI_4;
	ray.end = ray.dir + M_PI_4;
	  while (ray.start <= ray.end)
		{
			ray.x = all->plr.x * SCALE; // каждый раз возвращаемся в точку начала
			ray.y = all->plr.y * SCALE;
			while (all->array[(int)(ray.y / SCALE)][(int)(ray.x / SCALE)] != '1')
			{
				ray.x += cos(ray.start);
				ray.y += sin(ray.start);
				my_mlx_pixel_put(&all->dd, ray.x + move, ray.y + move, 0x990099);
			}
			ray.start += M_PI / 1000;
		}
}





// основная функция
int visual_map(t_all *all)
{
	int *y = &all->map.y;
	int *x = &all->map.x;
	t_dd	*img = &all->dd;
	img->bpp = all->win.bpp;
	img->line_l = all->win.line_l;
	img->en = all->win.en;
	all->dd.mlx = mlx_init();
	all->dd.win = mlx_new_window(all->dd.mlx, all->win.gorisont, all->win.vert, "2D map");
	
	img->img = mlx_new_image(img->mlx, all->win.gorisont, all->win.vert);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_l,
									 &img->en);
	
	while (all->array[*y])
	{
		*x = 0;
		while(all->array[*y][*x])
		{
			if (all->array[*y][*x] == '1')
				scale_map(all);
			if (all->array[*y][*x] == all->plr.plook)
				scale_player(all);
			*x += 1;
		}
		*y += 1;
	}
	mlx_put_image_to_window(all->dd.mlx, all->dd.win, img->img, 0, 0);
	mlx_loop(all->dd.mlx);
	return (0);
}

