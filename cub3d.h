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

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include "mms/mlx.h"
# include <fcntl.h>
# include "lbft/libft.h"
# include "gnl/get_next_line.h"
# include <math.h>

# define ROT_SPEED 0.1
# define FOOT 0.5
# define SL 12
# define SR 14
# define FRWD 13
# define BACK 1
# define TURN_LEFT 0
# define TURN_RIGHT 2
# define MLX_GADR mlx_get_data_addr
# define CASTING_WALLS casting
# define CHOISE_SIDE choise_side
# define CAST_SPRITES spites
# define X	s->x
# define Y	s->y

typedef struct	s_win
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			line_l;
	int			bpp;
	int			en;
	int			max_h;
	int			max_w;
	int			h;
	int			w;
}				t_win;

typedef struct	s_txr
{
	void		*ptr;
	void		*addr;
	int			line_l;
	int			bpp;
	int			en;
	int			h;
	int			w;
	int			x;
	int			y;
	char		*way;
}				t_txr;

typedef struct	s_fl
{
	int			r;
	int			g;
	int			b;

}				t_fl;

typedef struct	s_map
{
	char		*no_way;
	char		*so_way;
	char		*we_way;
	char		*ea_way;
	int			sp_count;
	char		*s_way;
	char		*floor_color;
	char		*sky_color;
	int			total_lines_before_map;
	int			error;
	int			lines;
	int			y;
	int			x;
	int			longest_line;
}				t_map;

typedef struct	s_sprite
{
	double		x;
	double		y;
	double		distance;
}				t_sprite;

typedef struct	s_plr
{
	double		x;
	double		y;
	float		dir;
	double		start;
	double		end;
	double		plx;
	double		ply;
	char		plook;
}				t_plr;

typedef struct	s_all
{
	t_win		win;
	t_plr		plr;
	t_map		map;
	t_txr		no;
	t_txr		so;
	t_txr		ea;
	t_txr		current_side;
	t_txr		we;
	t_txr		sp;
	t_fl		fl;
	t_fl		c;
	t_sprite	*sprite;
	char		**array;
	char		**arrrecuv;
	double		side_dist_x;
	double		side_dist_y;
	double		old_side_dist;
	double		pwd;
	int			step_x;
	int			step_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		ws_x;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	int			hit;
	int			side;
	double		step;
	int			tex_x;
	int			tex_y;
	int			line_h;
	double		tex_pos;
	double		sprt_x;
	double		sprt_y;
	int			color;
	double		i_d;
	double		tr_x;
	double		tr_y;
	int			spr_scrn_x;
	int			spr_h;
	int			draw_start_y;
	int			drw_nd_y;
	int			spr_w;
	int			draw_start_x;
	int			draw_end_x;
	int			x;
	int			y;
	int			i;
	int			j;
	int			flag;
	double		*z_buffer;
	int			stripe;
	int			draw_start;
	int			draw_end;
}				t_all;

void			ft_map_parcer(t_all *all, char *argv);
void			config_map(t_all *all, char *str);
void			ft_putin(t_all *all);
char			**make_map(t_list **head, int size, t_all *all);
void			map_copy(t_all *all);
void			check_ways(t_all *all);
void			map_utils(t_all *all);
int				map_validate(t_all *all);
void			find_player(t_all *all);
void			write_player_pi(t_all *all);
void			key_press(int key, t_all *all);
void			lodev(t_all *all);
void			pixel_put(t_win *data, int x, int y, int color);
void			lodev_init(t_all *all);
void			write_textures(t_all *all);
unsigned		get_color(t_all *all, int x, int y, char side);
void			floor_color(t_fl *strct, char *str);
int				rgb(int r, int g, int b);
void			ft_exit(char *str, t_all *all);
void			map_check_around(t_all *s);
void			sprite_init(t_all *s);
void			sprite_write(t_all *s);
void			sort_sprite(t_all *s);
void			spites(t_all *s);
void			screenshot(t_all *s);
#endif
