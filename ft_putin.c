//
//  ft_putin.c
//  cub3d
//
//  Created by Torres Saiyan on 1/26/21.
//  Copyright © 2021 21school. All rights reserved.
//

#include "cub3d.h"

void ft_putin(t_all *all)
{
	all->win.gorisont = 0;
	all->win.vert = 0;
	all->map.error = 0;
	all->map.no_way = NULL;
	all->map.so_way = NULL;
	all->map.we_way = NULL;
	all->map.ea_way = NULL;
	all->map.s_way = NULL;
	all->map.total_lines_before_map = 0;
}
