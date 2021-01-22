//
//  mlx.c
//  cub3d
//
//  Created by Torres Saiyan on 1/21/21.
//  Copyright © 2021 21school. All rights reserved.
//

#include "mms/mlx.h"
#include "libft/libft.h"
#include "parcer_map.h"
# define SCALE 10

void	scale_map(t_struct *map)
{
	int start = 100;
	int x;
	int y = map->y * SCALE;
		while (y < (map->y * SCALE + SCALE))
		{
			x = map->x * SCALE;
			while(x < (map->x * SCALE + SCALE))
				mlx_pixel_put(map->mlx, map->win, (x++ + start), (y + start), 0xFFFFFF);
			y++;
		}
}

void	scale_player(t_struct *map)
{
	int start = 100;
	int x;
	int y = map->y * SCALE;
		while (y < (map->y * SCALE + SCALE))
		{
			x = map->x * SCALE;
			while(x < (map->x * SCALE + SCALE))
				mlx_pixel_put(map->mlx, map->win, (x++ + start), (y + start), 0xff0000);
			y++;
		}
}

int visual_map(t_struct *map)
{
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, 1000, 1000, "window");
	map->y = 0;

	while (map->array[map->y])
	{
		map->x = 0;
		while(map->array[map->y][map->x])
		{
			if (map->array[map->y][map->x] == '1')
				scale_map(map);
			if (map->array[map->y][map->x] == 'N')
				scale_player(map);
			map->x++;
		}
		map->y++;
	}
	mlx_loop(map->mlx);
	return (0);
}



