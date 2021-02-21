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
	if(!(sprite = malloc(sizeof(t_sprite) * s->map.sp_count)))
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
		while(s->array[y])
		{
			x = 0;
			while(s->array[y][x])
			{
				if (s->array[y][x] == '2')
				{
					s->sprite[i].y = y;
					s->sprite[i].x = x;
					s->sprite[i].distance = ((s->plr.x - x) * (s->plr.x - x) + (s->plr.y - y) * (s->plr.y - y)); 
					s->array[y][x] = 0;
					i++;
				}
				x++;
			}
			y++;
		}
}

void sort_sprite(t_all *s)
{
	double x;
	double y;
	int i;
	int flag;
	double d;

	flag = 1;
	puts("- - - - - - -- - ");
	while (flag)
	{
		i = -1;
		flag = 0;
		d = 0;
		while (++i < s->map.sp_count)
			s->sprite[i].distance = ((s->plr.x - s->sprite[i].x) * (s->plr.x - s->sprite[i].x) + (s->plr.y - s->sprite[i].y) * (s->plr.y - s->sprite[i].y));
		i = 0;
		while (i < s->map.sp_count)
		{
			if (s->sprite[i].distance < s->sprite[i + 1].distance ) // как сделать защиту?)
			{
				x = s->sprite[i].x;
				y = s->sprite[i].y;
				d = s->sprite[i].distance;
				s->sprite[i].x = s->sprite[i + 1].x;
				s->sprite[i].y = s->sprite[i + 1].y;
				s->sprite[i].distance = s->sprite[i + 1].distance;
				s->sprite[i + 1].x = x;
				s->sprite[i + 1].y = y;
				s->sprite[i + 1].distance = d;
				flag = 1;
				printf("%f\n", s->sprite[i].distance);
			}
			i++;
		}
		i = 0;
		while (i < s->map.sp_count)
			printf("sorted: %f\n", s->sprite[i++].distance);
	}
	puts("- - - - - - -- - ");
}
