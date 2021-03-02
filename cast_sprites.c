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

static void	casting(t_all *s)
{
	int	d;

	while (s->stripe < s->draw_end_x)
	{
		s->tex_x = (int)(256 * (s->stripe - \
			(-s->spr_w / 2 + s->spr_scrn_x)) * s->sp.w / s->spr_w) / 256;
		if (s->tr_y > 0 && s->stripe > 0 && s->stripe < s->win.w \
							&& s->tr_y < s->z_buffer[s->stripe])
		{
			s->y = s->draw_start_y;
			while (s->y < s->drw_nd_y)
			{
				d = s->y * 256 - s->win.h * 128 + s->spr_h * 128;
				s->tex_y = ((d * s->sp.h) / s->spr_h) / 256;
				s->color = get_color(s, s->tex_x, s->tex_y, 'P');
				if ((s->color & 0x00FFFF) != 0)
					pixel_put(&s->win, s->stripe, s->y, s->color);
				s->y++;
			}
		}
		s->stripe++;
	}
}

/*
** функция вычисления для спрайтов
*/

void		spites(t_all *s)
{
	s->i = 0;
	while (s->i < s->map.sp_count)
	{
		s->sprt_x = s->sprite[s->i].x - s->plr.x;
		s->sprt_y = s->sprite[s->i].y - s->plr.y;
		sort_sprite(s);
		s->i_d = 1.0 / (s->plr.plx * s->plr.end - s->plr.start * s->plr.ply);
		s->tr_x = s->i_d * (s->plr.end * s->sprt_x - s->plr.start * s->sprt_y);
		s->tr_y = s->i_d * (-s->plr.ply * s->sprt_x + s->plr.plx * s->sprt_y);
		s->spr_scrn_x = (int)((s->win.w / 2) * (1 + s->tr_x / s->tr_y));
		s->spr_h = abs((int)(s->win.h / (s->tr_y)));
		s->draw_start_y = (s->win.h / 2) - (s->spr_h / 2);
		s->draw_start_y = (s->draw_start_y < 0) ? 0 : s->draw_start_y;
		s->drw_nd_y = (s->spr_h / 2) + (s->win.h / 2);
		s->drw_nd_y = (s->drw_nd_y >= s->win.h) ? s->win.h - 1 : s->drw_nd_y;
		s->spr_w = abs((int)(s->win.w / (s->tr_y)));
		s->draw_start_x = -s->spr_w / 2 + s->spr_scrn_x;
		s->draw_start_x = (s->draw_start_x < 0) ? 0 : s->draw_start_x;
		s->draw_end_x = s->spr_w / 2 + s->spr_scrn_x;
		s->draw_end_x = (s->draw_end_x >= s->win.w) ? s->win.w : s->draw_end_x;
		s->stripe = s->draw_start_x;
		casting(s);
		s->i++;
	}
}
