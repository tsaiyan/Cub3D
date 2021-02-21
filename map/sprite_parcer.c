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
					s->array[y][x] = 0;
					i++;
				}
				x++;
			}
			y++;
		}
}
