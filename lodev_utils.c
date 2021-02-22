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
** запись пикселя в img
** bpp / 8 смещение по x
** y * line_l перед по строкам
*/

void	my_mlx_pixel_put(t_win *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_l + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}


/*
** функции передвижения
** step используется для использования функции как для поворота,
** так и для стрейфа
*/

void	turn_right(t_plr *plr, double step)
{
	double plx;
	double planeY;
	double dirX;
	double dirY;

	plx = plr->plx;
	planeY = plr->ply;
	dirX = plr->start;
	dirY = plr->end;
	plr->start = dirX * cos(step) - dirY * sin(step);
	plr->end = dirX * sin(step) + dirY * cos(step);
	plr->plx = plx * cos(step) - planeY * sin(step);
	plr->ply = plx * sin(step) + planeY * cos(step);
}

void	turn_left(t_plr *plr, double step)
{
	double plx;
	double planeY;
	double dirX;
	double dirY;

	plx = plr->plx;
	planeY = plr->ply;
	dirX = plr->start;
	dirY = plr->end;
	plr->start = dirX * cos(-step) - dirY * sin(-step);
	plr->end = dirX * sin(-step) + dirY * cos(-step);
	plr->plx = plx * cos(-step) - planeY * sin(-step);
	plr->ply = plx * sin(-step) + planeY * cos(-step);
}

void	go_forward(t_all *all)
{
	if (all->array[(int)(all->plr.y + all->plr.end)][(int)(all->plr.x + all->plr.start)] == '0')
	{
		all->plr.x += all->plr.start * FOOT;
		all->plr.y += all->plr.end * FOOT;
	}
}

void	go_back(t_all *all)
{
	if (all->array[(int)(all->plr.y - all->plr.end)][(int)(all->plr.x - all->plr.start)] == '0')
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
		turn_left(&all->plr, rotSpeed);
	if (key == TURN_RIGHT)
		turn_right(&all->plr, rotSpeed);
	if (key == 53)
		ft_exit("? NO. IT'S ESCAPE", all);
	lodev(all);
}

/*
** инициализация окна
*/

void	lodev_init(t_all *all)
{
	all->win.mlx = mlx_init();
	all->win.win = mlx_new_window(all->win.mlx, all->win.w, all->win.h, "3D");
	lodev(all);
}
