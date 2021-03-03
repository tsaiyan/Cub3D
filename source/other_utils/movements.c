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
** функции передвижения
** step используется для использования функции как для поворота,
** так и для стрейфа
*/

void	turn_right(t_plr *plr, double step)
{
	double plx;
	double plane_y;
	double dir_x;
	double dir_y;

	plx = plr->plx;
	plane_y = plr->ply;
	dir_x = plr->start;
	dir_y = plr->end;
	plr->start = dir_x * cos(step) - dir_y * sin(step);
	plr->end = dir_x * sin(step) + dir_y * cos(step);
	plr->plx = plx * cos(step) - plane_y * sin(step);
	plr->ply = plx * sin(step) + plane_y * cos(step);
}

void	turn_left(t_plr *plr, double step)
{
	double plane_x;
	double plane_y;
	double dir_x;
	double dir_y;

	plane_x = plr->plx;
	plane_y = plr->ply;
	dir_x = plr->start;
	dir_y = plr->end;
	plr->start = dir_x * cos(-step) - dir_y * sin(-step);
	plr->end = dir_x * sin(-step) + dir_y * cos(-step);
	plr->plx = plane_x * cos(-step) - plane_y * sin(-step);
	plr->ply = plane_x * sin(-step) + plane_y * cos(-step);
}

void	go_forward(t_all *all)
{
	if (all->array[(int)(all->plr.y + all->plr.end)]\
		[(int)(all->plr.x + all->plr.start)] == '0')
	{
		all->plr.x += all->plr.start * FOOT;
		all->plr.y += all->plr.end * FOOT;
	}
}

void	go_back(t_all *all)
{
	if (all->array[(int)(all->plr.y - all->plr.end)]\
		[(int)(all->plr.x - all->plr.start)] == '0')
	{
		all->plr.x -= all->plr.start * FOOT;
		all->plr.y -= all->plr.end * FOOT;
	}
}

/*
** считывание кнопок и вызов функций передвижения
** сокращения заданы в cub3d.h
** SL - стрейф влево
** SR - стрейф вправо
*/

void	key_press(int key, t_all *all)
{
	if (key == SL)
	{
		turn_left(&all->plr, M_PI_2);
		go_forward(all);
		turn_right(&all->plr, M_PI_2);
	}
	if (key == SR)
	{
		turn_right(&all->plr, M_PI_2);
		go_forward(all);
		turn_left(&all->plr, M_PI_2);
	}
	if (key == FRWD)
		go_forward(all);
	if (key == BACK)
		go_back(all);
	if (key == TURN_LEFT)
		turn_left(&all->plr, ROT_SPEED);
	if (key == TURN_RIGHT)
		turn_right(&all->plr, ROT_SPEED);
	if (key == 53)
		ft_exit("OH, NO. IT'S ESCAPE", all);
	raycasting_1(all);
}
