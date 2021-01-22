//
//  parcer_map.h
//  cub3d
//
//  Created by Torres Saiyan on 1/22/21.
//  Copyright © 2021 21school. All rights reserved.
//

#ifndef PARCER_MAP_H
#define PARCER_MAP_H
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct	p_list
{
	char		**array;
	void		*mlx;
	void		*win;
	int			y;
	int			x;

}				t_struct;

int visual_map(t_struct *map_world);

#endif /* parcer_map_h */
