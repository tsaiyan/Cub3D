//
//  main.c
//  cub3d
//
//  Created by Torres Saiyan on 1/20/21.
//  Copyright © 2021 21school. All rights reserved.
//

#include "cub3d.h"

//int key_press(int key, t_struct *map)
//{
//	printf("\npress\n");
//	mlx_clear_window(map->mlx, map->win);
//	map->y = 0;
//	map->x = 0;
//	if (key == 13)
//		map->py -= FOOT;
//	if (key == 1)
//		map->py += FOOT;
//	if (key == 0)
//		map->px -= FOOT;
//	if (key == 2)
//		map->px += FOOT;
//	if (key == 53)
//		exit(0);
//	//visual_map(map);
//	return(0);
//}

int main(int argc, char **argv)
{
	t_all *all;
	if (!(all = malloc(sizeof(t_all))))
		return (-1);
	ft_putin(all);
	ft_map_parcer(all, argv[1]);
	return 0;
}

