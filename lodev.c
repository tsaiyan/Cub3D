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
	for(s->v.x = 0; s->v.x < s->win.w; s->v.x++)
	{
		s->v.camera_x = 2 * s->v.x / (double)s->win.w - 1;
		s->v.ray_dir_x = s->plr.start + s->plr.plx * s->v.camera_x;
		s->v.ray_dir_y = s->plr.end + s->plr.ply * s->v.camera_x;
		s->v.map_x = (int)s->plr.x;
		s->v.map_y = (int)s->plr.y;
		s->v.delta_dist_x = fabs(1 / s->v.ray_dir_x);
		s->v.delta_dist_y = fabs(1 / s->v.ray_dir_y);
		s->v.hit = 0;
		side = 0;
		if (s->v.ray_dir_x < 0)
		{
			s->v.step_x = -1;
			s->v.side_dist_x = (s->plr.x - s->v.map_x) * s->v.delta_dist_x;
		}
		else
		{
			s->v.step_x = 1;
			s->v.side_dist_x = (s->v.map_x + 1.0 - s->plr.x) * s->v.delta_dist_x;
		}
		if (s->v.ray_dir_y < 0)
		{
			s->v.step_y = -1;
			s->v.side_dist_y = (s->plr.y - s->v.map_y) * s->v.delta_dist_y;
		}
		else
		{
			s->v.step_y = 1;
			s->v.side_dist_y = (s->v.map_y + 1.0 - s->plr.y) * s->v.delta_dist_y;
		}
		while (s->v.hit == 0)
		{
			if (s->v.side_dist_x < s->v.side_dist_y)
			{
				s->v.old_side_dist = s->v.side_dist_x;
				s->v.side_dist_x += s->v.delta_dist_x;
				s->v.map_x += s->v.step_x;
				side = 0;
			}
			else
			{
				s->v.old_side_dist = s->v.side_dist_y;
				s->v.side_dist_y += s->v.delta_dist_y;
				s->v.map_y += s->v.step_y;
				side = 1;
			}
			if (s->array[s->v.map_y][s->v.map_x] > '0')
				s->v.hit = 1;
		}
		if (side == 0)
			s->v.perp_wall_dist = (s->v.map_x - s->plr.x + (1 - s->v.step_x) / 2) / s->v.ray_dir_x;
		else
			s->v.perp_wall_dist = (s->v.map_y - s->plr.y + (1 - s->v.step_y) / 2) / s->v.ray_dir_y;
		s->v.line_height = (int)(s->win.h / s->v.perp_wall_dist);
		int drawStart = -s->v.line_height / 2 + s->win.h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = s->v.line_height / 2 + s->win.h / 2;
		if (drawEnd >= s->win.h)
			drawEnd = s->win.h - 1;
		if (side == 0)
			s->v.ws_x = s->plr.y + s->v.perp_wall_dist * s->v.ray_dir_y;
		else
			s->v.ws_x = s->plr.x + s->v.perp_wall_dist * s->v.ray_dir_x;
		s->v.ws_x -= floor((s->v.ws_x));
		s->v.tex_x = (int)(s->v.ws_x * (double)(s->no.w));
		if (side == 0 && s->v.ray_dir_x > 0)
			s->v.tex_x = s->no.w - s->v.tex_x - 1;
		if (side == 1 && s->v.ray_dir_y < 0)
			s->v.tex_x = s->no.w - s->v.tex_x - 1;
		step = 1.0 * s->no.h / s->v.line_height;
		s->v.tex_pos = (drawStart - s->win.h / 2 + s->v.line_height / 2) * step;
		for (s->v.y = 0; s->v.y < drawStart; s->v.y++)
			my_mlx_pixel_put(&s->win, s->v.x, s->v.y, create_rgb(s->c.r, s->c.g, s->c.b));
		for(s->v.y = drawStart; s->v.y < drawEnd; s->v.y++)
		{
			s->v.tex_y = (int)s->v.tex_pos & (s->no.h - 1);
			s->v.tex_pos += step;
			s->v.color = get_color(s, s->v.tex_x, s->v.tex_y, 'W');
			if (side)
			{
				if (s->v.step_y > 0)
					s->v.color = get_color(s, s->v.tex_x, s->v.tex_y, 'S');
				else
					s->v.color = get_color(s, s->v.tex_x, s->v.tex_y, 'N');
			}
			else
				{
				if (s->v.step_x > 0)
					s->v.color = get_color(s, s->v.tex_x, s->v.tex_y, 'E');
				else
					s->v.color = get_color(s, s->v.tex_x, s->v.tex_y, 'W');
			}
			my_mlx_pixel_put(&s->win, s->v.x, s->v.y, s->v.color);
		}
		for (s->v.y = drawEnd; s->v.y < s->win.h; s->v.y++)
			my_mlx_pixel_put(&s->win, s->v.x, s->v.y, create_rgb(s->fl.r, s->fl.g, s->fl.b));
			ZBuffer[s->v.x] = s->v.perp_wall_dist;
	}
	
	s->v.z_buffer = ZBuffer;
	spites(s);
	mlx_put_image_to_window(s->win.mlx, s->win.win, s->win.img, 0, 0);
}
