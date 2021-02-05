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
#define FOOT 0.5


//рисуем карту

void	scale_map(t_all *all)
{
	t_map *map = &all->map;
	t_win *win = &all->win;
	int start = 100;
	int x;
	int y = map->y * SCALE;
		while (y < (map->y * SCALE + SCALE))
		{
			x = map->x * SCALE;
			while(x < (map->x * SCALE + SCALE))
				mlx_pixel_put(win->mlx, win->win, (x++ + start), (y + start), 0xFFFFFF);
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
				mlx_pixel_put(all->win.mlx, all->win.win,ray.x + move, ray.y + move, 0x990099);
			}
			ray.start += M_PI / 100;
		}
}

// считываем кнопки
int key_press(int key, t_all *all)
 {
	all->map.y = 0;
	all->map.x = 0;
	printf("\npress\n");
	mlx_clear_window(all->win.mlx, all->win.win);
	if (key == 13)
		all->plr.y -= FOOT;
	if (key == 1)
		all->plr.y += FOOT;
	 if (key == 12)
		 all->plr.x -= FOOT;
	 if (key == 14)
		 all->plr.x += FOOT;
	if (key == 0)
		all->plr.dir -= 0.2;
	if (key == 2)
		all->plr.dir += 0.2;
	if (key == 53)
		exit(0);
	visual_map(all);
	return(0);
 }

// основная функция
int visual_map(t_all *all)
{
	int *y = &all->map.y;
	int *x = &all->map.x;

	all->win.mlx = mlx_init();
	all->win.win = mlx_new_window(all->win.mlx, 800, 400, "Hello world!");
	while (all->array[*y])
	{
		*x = 0;
		while(all->array[*y][*x])
		{
			if (all->array[*y][*x] == '1')
				scale_map(all);
			if (all->array[*y][*x] == all->plr.plook)
			{
				if(all->plr.y == 0 && all->plr.x == 0)
				{
				all->plr.y = *y;
				all->plr.x = *x;
				}
				scale_player(all);
			}
			*x += 1;
		}
		*y += 1;
	}
	mlx_hook(all->win.win, 2, (1L << 0), key_press, &all->win);
	mlx_loop(all->win.mlx);
	return (0);
}

