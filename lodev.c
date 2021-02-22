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

#define numSprites 2

#include "cub3d.h"




void	lodev(t_all *s)
{

	double ZBuffer[s->win.w];
	int side;
	double step;

	s->array[(int)s->plr.y][(int)s->plr.x] = '0';
	s->win.img = mlx_new_image(s->win.mlx, s->win.w, s->win.h);
	s->win.addr = mlx_get_data_addr(s->win.img, &s->win.bpp, &s->win.line_l, &s->win.en);
	write_textures(s);
	for(s->x = 0; s->x < s->win.w; s->x++)
	{
		s->camera_x = 2 * s->x / (double)s->win.w - 1;
		s->ray_dir_x = s->plr.start + s->plr.plx * s->camera_x;
		s->ray_dir_y = s->plr.end + s->plr.ply * s->camera_x;
		s->map_x = (int)s->plr.x;
		s->map_y = (int)s->plr.y;
		s->delta_dist_x = fabs(1 / s->ray_dir_x);
		s->delta_dist_y = fabs(1 / s->ray_dir_y);
		s->hit = 0;
		side = 0;
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
		while (s->hit == 0)
		{
			if (s->side_dist_x < s->side_dist_y)
			{
				s->old_side_dist = s->side_dist_x;
				s->side_dist_x += s->delta_dist_x;
				s->map_x += s->step_x;
				side = 0;
			}
			else
			{
				s->old_side_dist = s->side_dist_y;
				s->side_dist_y += s->delta_dist_y;
				s->map_y += s->step_y;
				side = 1;
			}
			if (s->array[s->map_y][s->map_x] > '0')
				s->hit = 1;
		}
		if (side == 0)
			s->perp_wall_dist = (s->map_x - s->plr.x + (1 - s->step_x) / 2) / s->ray_dir_x;
		else
			s->perp_wall_dist = (s->map_y - s->plr.y + (1 - s->step_y) / 2) / s->ray_dir_y;
		s->line_height = (int)(s->win.h / s->perp_wall_dist);
		int drawStart = -s->line_height / 2 + s->win.h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = s->line_height / 2 + s->win.h / 2;
		if (drawEnd >= s->win.h)
			drawEnd = s->win.h - 1;
		if (side == 0)
			s->ws_x = s->plr.y + s->perp_wall_dist * s->ray_dir_y;
		else
			s->ws_x = s->plr.x + s->perp_wall_dist * s->ray_dir_x;
		s->ws_x -= floor((s->ws_x));
		s->tex_x = (int)(s->ws_x * (double)(s->no.w));
		if (side == 0 && s->ray_dir_x > 0)
			s->tex_x = s->no.w - s->tex_x - 1;
		if (side == 1 && s->ray_dir_y < 0)
			s->tex_x = s->no.w - s->tex_x - 1;
		step = 1.0 * s->no.h / s->line_height;
		s->tex_pos = (drawStart - s->win.h / 2 + s->line_height / 2) * step;
		for (s->y = 0; s->y < drawStart; s->y++)
			my_mlx_pixel_put(&s->win, s->x, s->y, create_rgb(s->c.r, s->c.g, s->c.b));
		for(s->y = drawStart; s->y < drawEnd; s->y++)
		{
			s->tex_y = (int)s->tex_pos & (s->no.h - 1);
			s->tex_pos += step;
			s->color = get_color(s, s->tex_x, s->tex_y, 'W');
			if (side)
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
			my_mlx_pixel_put(&s->win, s->x, s->y, s->color);
		}
		for (s->y = drawEnd; s->y < s->win.h; s->y++)
			my_mlx_pixel_put(&s->win, s->x, s->y, create_rgb(s->fl.r, s->fl.g, s->fl.b));
			ZBuffer[s->x] = s->perp_wall_dist;
	}
	
	s->z_buffer = ZBuffer;
	spites(s);
	mlx_put_image_to_window(s->win.mlx, s->win.win, s->win.img, 0, 0);
}
