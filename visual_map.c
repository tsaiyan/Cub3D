//
//  mlx.c
//  cub3d
//
//  Created by Torres Saiyan on 1/21/21.
//  Copyright © 2021 21school. All rights reserved.
//

#include "mms/mlx.h"
#include "lbft/lbft.h"
#include "cub3d.h"


void	scale_map(t_all *all)
{
	int start = 100;
	int x;
	int y = all->map.y * SCALE;
		while (y < (all->map.y * SCALE + SCALE))
		{
			x = all->map.x * SCALE;
			while(x < (mall->map.x * SCALE + SCALE))
				mlx_pixel_put(map->mlx, map->win, (x++ + start), (y + start), 0xFFFFFF);
			y++;
		}
}



int visual_map(t_all *map)
{
	while (all->array[all->map.y])
	{
		map->x = 0;
		while(map->array[map->y][map->x])
		{
			if (map->array[map->y][map->x] == '1')
				scale_map(map);
			if (map->array[map->y][map->x] == 'N')
			{
				if (map->py == 0 && map->px == 0)
				{
					map->py = map->y;
					map->px = map->x;
				}
				//scale_player(map);
			}
			map->x++;
		}
		map->y++;
	}
	return (0);
}



