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

#ifndef PARCER_MAP_H
#define PARCER_MAP_H
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include "mms/mlx.h"
#include <fcntl.h>
#include "lbft/libft.h"
#include "gnl/get_next_line.h"
#include <stdio.h>
#include <math.h>
#define SCALE 16 // условный размер каждого квадратика в карте
#define rotSpeed 0.1
#define FOOT 0.5
#define SL 12
#define SR 14
#define FRWD 13
#define BACK 1
#define TURN_LEFT 0
#define TURN_RIGHT 2
typedef struct	s_win //структура для окна 3D
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			line_l;
	int			bpp;
	int			en;
	int			h;
	int			w;
}				  t_win;

typedef struct	s_dd //структура для окна 2D
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			line_l;
	int			bpp;
	int			en;
	int			h;
	int			w;
}				  t_dd;

typedef struct	s_txr //структура для изображения
{
	void		*ptr;
	void		*addr;
	int			line_l;
	int			bpp;
	int			en;
	int			h;
	int			w;
	int 		x;
	int 		y;
	char		*way;
}				t_txr;

typedef struct	s_fl //структура для изображения
{
	int			r;
	int			g;
	int			b;

}				t_fl;

typedef struct	s_map //структура для карты
{
	char *no_way;
	char *so_way;
	char *we_way;
	char *ea_way;
	int	sp_count;
	char *s_way;
	char *floor_color;
	char *sky_color;
	int total_lines_before_map;
	int error;
	int lines;
	int y;
	int x;
}				  t_map;

typedef struct s_sprite
{
	double x;
	double y;
	double distance;
}	t_sprite;

typedef struct	s_point // структура для точки
{
	int			x;
	int			y;
}				  t_point;

typedef struct	s_plr //структура для игрока и луча
{
	double		x;
	double		y;
	float		dir;
	double		start;
	double		end;
	double		planeX;
	double		planeY;
	char		plook;
}				  t_plr;

typedef struct	s_mv
{
	int longest_line;
}				t_mv;

typedef struct	s_all // структура для всего вместе
{
	t_win		win;
	t_plr		plr;
	t_map		map;
	t_dd		dd;
	t_txr		no;
	t_txr		so;
	t_txr		ea;
	t_txr		we;
	t_txr		sp;
	t_fl		fl;
	t_fl		c;
	t_mv		mv;
	t_sprite	*sprite;
	char		**array;
	char		**arrrecuv;
}				  t_all;


void printf_checks(t_all *all);
// for map:
void	ft_map_parcer(t_all *all, char *argv);
int		config_map(t_all *all, char *str);
void	ft_putin(t_all *all);
char	**make_map(t_list **head, int size, t_all *all);
void	map_copy(t_all *all);
int		check_ways(t_all *all);
void	map_utils(t_all *all);
int		map_validate(t_all *all);
void	find_player(t_all *all);
int		bad_chars_in_map(t_all *all);
int		borders_ok(t_all *all);
void	write_player_pi(t_all *all);
void		key_press(int key, t_all *all);
// for 2d
int		visual_map(t_all *all);
// 3D
void	lodev(t_all *all);
void    my_mlx_pixel_put(t_win *data, int x, int y, int color);
void	lodev_init(t_all *all);
void	write_textures(t_all *all);
unsigned	get_color(t_all *all, int x, int y, char side);
void	floor_color(t_fl *strct, char *str);
int		create_rgb(int r, int g, int b);
void	ft_exit(char *str, t_all *all);
void	map_check_around(t_all *s);
void	sprite_init(t_all *s);
void	sprite_write(t_all *s);
void	sort_sprite(t_all *s);
//void	ft_floor(t_all *all);
#endif /* parcer_map_h */
