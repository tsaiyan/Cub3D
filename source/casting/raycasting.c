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

#include "../cub3d.h"

/*
** casting walls, floor and sky
*/

static void	casting(t_all *s)
{
	while (Y < s->draw_start)
		pixel_put(&s->win, X, Y++, rgb(s->c.r, s->c.g, s->c.b));
	while (Y < s->draw_end)
	{
		s->tex_y = (int)s->tex_pos & (s->current_side.h - 1);
		s->tex_pos += s->step;
		s->color = get_color(s, s->tex_x, s->tex_y, 'W');
		if (s->side)
		{
			if (s->step_y > 0)
				s->color = get_color(s, s->tex_x, s->tex_y, 'S');
			else
				s->color = get_color(s, s->tex_x, s->tex_y, 'N');
		}
		else
		{
			if (s->step_x > 0)
				s->color = get_color(s, s->tex_x, s->tex_y, 'E');
			else
				s->color = get_color(s, s->tex_x, s->tex_y, 'W');
		}
		pixel_put(&s->win, X, Y++, s->color);
	}
	while (Y < s->win.h)
		pixel_put(&s->win, X, Y++, rgb(s->fl.r, s->fl.g, s->fl.b));
}

static void	raycasting_3(t_all *s)
{
	if (s->side == 0)
		s->ws_x = s->plr.y + s->pwd * s->ray_dir_y;
	else
		s->ws_x = s->plr.x + s->pwd * s->ray_dir_x;
	s->ws_x -= floor((s->ws_x));
	s->tex_x = (int)(s->ws_x * (double)(s->current_side.w));
	if (s->side == 0 && s->ray_dir_x > 0)
		s->tex_x = s->current_side.w - s->tex_x - 1;
	if (s->side == 1 && s->ray_dir_y < 0)
		s->tex_x = s->current_side.w - s->tex_x - 1;
	s->step = 1.0 * s->current_side.h / s->line_h;
	s->tex_pos = (s->draw_start - s->win.h / 2 + s->line_h / 2) * s->step;
}

static void	raycasting_0(t_all *s)
{
	defines(s);
	if (s->ray_dir_x < 0)
	{
		s->step_x = -1;
		s->side_dist_x = (s->plr.x - s->map_x) * s->delta_dist_x;
	}
	else
	{
		s->step_x = 1;
		s->side_dist_x = (s->map_x + 1.0 - s->plr.x) * s->delta_dist_x;
	}
	if (s->ray_dir_y < 0)
	{
		s->step_y = -1;
		s->side_dist_y = (s->plr.y - s->map_y) * s->delta_dist_y;
	}
	else
	{
		s->step_y = 1;
		s->side_dist_y = (s->map_y + 1.0 - s->plr.y) * s->delta_dist_y;
	}
}

void		raycasting_2(t_all *s)
{
	while (s->hit == 0)
	{
		if (s->side_dist_x < s->side_dist_y)
		{
			s->old_side_dist = s->side_dist_x;
			s->side_dist_x += s->delta_dist_x;
			s->map_x += s->step_x;
			s->side = 0;
		}
		else
		{
			s->old_side_dist = s->side_dist_y;
			s->side_dist_y += s->delta_dist_y;
			s->map_y += s->step_y;
			s->side = 1;
		}
		if (s->array[s->map_y][s->map_x] > '0')
			s->hit = 1;
	}
	if (s->side == 0)
		s->pwd = (s->map_x - s->plr.x + (1 - s->step_x) / 2) / s->ray_dir_x;
	else
		s->pwd = (s->map_y - s->plr.y + (1 - s->step_y) / 2) / s->ray_dir_y;
}

void		raycasting_1(t_all *s)
{
	double	z_buf[s->win.w];

	s->win.img = mlx_new_image(s->win.mlx, s->win.w, s->win.h);
	s->win.addr = MLX_GADR(s->win.img, &s->win.bpp, &s->win.line_l, &s->win.en);
	X = 0;
	while (X < s->win.w)
	{
		RAYCASTING_0(s);
		RAYCASTING_2(s);
		s->line_h = (int)(s->win.h / s->pwd);
		s->draw_start = -s->line_h / 2 + s->win.h / 2;
		s->draw_start = (s->draw_start < 0) ? 0 : s->draw_start;
		s->draw_end = s->line_h / 2 + s->win.h / 2;
		s->draw_end = (s->draw_end >= s->win.h) ? s->win.h - 1 : s->draw_end;
		CHOISE_SIDE(s);
		RAYCASTING_3(s);
		CASTING_WALLS(s);
		z_buf[X] = s->pwd;
		X++;
	}
	s->z_buffer = z_buf;
	CAST_SPRITES(s);
	mlx_put_image_to_window(s->win.mlx, s->win.win, s->win.img, 0, 0);
}
