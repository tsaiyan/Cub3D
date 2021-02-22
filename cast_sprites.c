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

#include "cub3d.h"

/*
** цикл отрисовки спрайтов
*/

void	casting(t_all *s)
{
	int	d;

	while (s->v.stripe < s->v.draw_end_x)
	{
		s->v.tex_x = (int)(256 * (s->v.stripe - \
			(-s->v.spr_w / 2 + s->v.spr_scrn_x)) * s->sp.w / s->v.spr_w) / 256;
		if (s->v.trans_y > 0 && s->v.stripe > 0 && s->v.stripe < s->win.w \
							&& s->v.trans_y < s->v.z_buffer[s->v.stripe])
		{
			s->v.y = s->v.draw_start_y;
			while (s->v.y < s->v.draw_end_y)
			{
				d = s->v.y * 256 - s->win.h * 128 + s->v.sprite_height * 128;
				s->v.tex_y = ((d * s->sp.h) / s->v.sprite_height) / 256;
				s->v.color = get_color(s, s->v.tex_x, s->v.tex_y, 'P');
				if ((s->v.color & 0x00FFFF) != 0)
					my_mlx_pixel_put(&s->win, s->v.stripe, s->v.y, s->v.color);
				s->v.y++;
			}
		}
		s->v.stripe++;
	}
}

/*
** функция вычисления для спрайтов
*/

void	spites(t_all *s)
{
	s->v.i = 0;
	while (s->v.i < s->map.sp_count)
	{
		s->v.sprt_x = s->sprite[s->v.i].x - s->plr.x;
		s->v.sprt_y = s->sprite[s->v.i].y - s->plr.y;
		sort_sprite(s);
		s->v.i_d = 1.0 / (s->plr.plx * s->plr.end - s->plr.start * s->plr.ply);
		s->v.trans_x = s->v.i_d * (s->plr.end * s->v.sprt_x - s->plr.start * s->v.sprt_y);
		s->v.trans_y = s->v.i_d * (-s->plr.ply * s->v.sprt_x + s->plr.plx * s->v.sprt_y);
		s->v.spr_scrn_x = (int)((s->win.w / 2) * (1 + s->v.trans_x / s->v.trans_y));
		s->v.sprite_height = abs((int)(s->win.h / (s->v.trans_y)));
		s->v.draw_start_y = (s->win.h / 2) - (s->v.sprite_height / 2);
		s->v.draw_start_y = (s->v.draw_start_y < 0) ? 0 : s->v.draw_start_y;
		s->v.draw_end_y = (s->v.sprite_height / 2) + (s->win.h / 2);
		s->v.draw_end_y = (s->v.draw_end_y >= s->win.h) ? s->win.h - 1 : s->v.draw_end_y;
		s->v.spr_w = abs((int)(s->win.w / (s->v.trans_y)));
		s->v.draw_start_x = -s->v.spr_w / 2 + s->v.spr_scrn_x;
		s->v.draw_start_x = (s->v.draw_start_x < 0) ? 0 : s->v.draw_start_x;
		s->v.draw_end_x = s->v.spr_w / 2 + s->v.spr_scrn_x;
		s->v.draw_end_x = (s->v.draw_end_x >= s->win.w) ? s->win.w : s->v.draw_end_x;
		s->v.stripe = s->v.draw_start_x;
		casting(s);
		s->v.i++;
	}
}
