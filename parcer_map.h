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
# include "mms/mlx.h"
#include <fcntl.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include <stdio.h>

typedef struct	p_list
{
	char		**array;
	void		*mlx;
	void		*win;
	int			y;
	int			x;
	float		py;
	float		px;
	float		ps;
	float		pe;
}				t_struct;

int		visual_map(t_struct *map_world);
int		key_press(int key, t_struct *map);
void	scale_player(t_struct *map);
void	move_player(t_struct *map);
void	scale_map(t_struct *map);

#endif /* parcer_map_h */
