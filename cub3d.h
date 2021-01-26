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

#define SCALE 16 // условный размер каждого квадратика в карте
#define FOOT 0.3 // шаг шага

typedef struct	s_win //структура для окна
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			line_l;
	int			bpp;
	int			en;
	int			vert;
	int			gorisont;
}				  t_win;

typedef struct	s_map //структура для карты
{
	char *no_way;
	char *so_way;
	char *we_way;
	char *ea_way;
	char *s_way;
	int count;
	int error;
}				  t_map;

typedef struct	s_point // структура для точки
{
	int			x;
	int			y;
}				  t_point;

typedef struct	s_plr //структура для игрока и луча
{
	float		x;
	float		y;
	float		dir;
	float		start;
	float		end;
}				  t_plr;

typedef struct	s_all // структура для всего вместе
{
	t_win		win;
	t_plr		*plr;
	t_map		map;
	char		*array;
}				  t_all;


void	ft_map_parcer(t_all *all, char *argv);
int		ft_check_map(t_all *all, char *str);
void	ft_putin(t_all *all);
#endif /* parcer_map_h */
