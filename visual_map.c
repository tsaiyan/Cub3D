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



int visual_map(t_struct *map)
{
	while (map->array[map->y])
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
				scale_player(map);
			}
			map->x++;
		}
		map->y++;
	}
	return (0);
}



