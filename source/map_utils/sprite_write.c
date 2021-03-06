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
** создает массив спрайтов
*/

void	sprite_init(t_all *s)
{
	t_sprite *sprite;

	if (!(sprite = malloc(sizeof(t_sprite) * s->map.sp_count)))
		ft_exit("can't malloc sprite", s);
	s->sprite = sprite;
}

/*
** записывает координаты спрайтов
** обнуляет позиции спрайтов в карте чтобы там не было стены
*/

void	sprite_write(t_all *s)
{
	int x;
	int y;
	int i;

	i = 0;
	y = 0;
	while (i < s->map.sp_count)
		while (s->array[y])
		{
			x = 0;
			while (s->array[y][x])
			{
				if (s->array[y][x] == '2')
				{
					s->sprite[i].y = y + 0.5;
					s->sprite[i].x = x + 0.5;
					s->sprite[i].distance = ((s->plr.x - x) * \
					(s->plr.x - x) + (s->plr.y - y) * (s->plr.y - y));
					s->array[y][x] = 0;
					i++;
				}
				x++;
			}
			y++;
		}
}

void	sort_sprite_body(t_all *s)
{
	double	x;
	double	y;
	double	d;

	while (s->j < s->map.sp_count)
	{
		if (s->sprite[s->j].distance < s->sprite[s->j + 1].distance)
		{
			x = s->sprite[s->j].x;
			y = s->sprite[s->j].y;
			d = s->sprite[s->j].distance;
			s->sprite[s->j].x = s->sprite[s->j + 1].x;
			s->sprite[s->j].y = s->sprite[s->j + 1].y;
			s->sprite[s->j].distance = s->sprite[s->j + 1].distance;
			s->sprite[s->j + 1].x = x;
			s->sprite[s->j + 1].y = y;
			s->sprite[s->j + 1].distance = d;
			s->flag = 1;
		}
		s->j++;
	}
}

void	sort_sprite(t_all *s)
{
	s->flag = 1;
	while (s->flag)
	{
		s->j = -1;
		s->flag = 0;
		while (++s->j < s->map.sp_count)
			s->sprite[s->j].distance = ((s->plr.x - s->sprite[s->j].x) \
			* (s->plr.x - s->sprite[s->j].x) + (s->plr.y - s->sprite[s->j].y) \
									* (s->plr.y - s->sprite[s->j].y));
		s->j = 0;
		while (s->j < s->map.sp_count)
			sort_sprite_body(s);
	}
}
