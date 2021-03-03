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

void	defines(t_all *s)
{
	s->camera_x = 2 * X / (double)s->win.w - 1;
	s->ray_dir_x = s->plr.start + s->plr.plx * s->camera_x;
	s->ray_dir_y = s->plr.end + s->plr.ply * s->camera_x;
	s->map_x = (int)s->plr.x;
	s->map_y = (int)s->plr.y;
	s->delta_dist_x = fabs(1 / s->ray_dir_x);
	s->delta_dist_y = fabs(1 / s->ray_dir_y);
	s->hit = 0;
	s->side = 0;
	Y = 0;
}

void	choise_side(t_all *s)
{
	if (s->side)
	{
		if (s->step_y > 0)
			s->current_side = s->so;
		else
			s->current_side = s->no;
	}
	else
	{
		if (s->step_x > 0)
			s->current_side = s->ea;
		else
			s->current_side = s->we;
	}
}

/*
** запись пикселя в img
** bpp / 8 смещение по x
** y * line_l перед по строкам
*/

void	pixel_put(t_win *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_l + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

/*
** инициализация окна
*/

void	raycasting_init(t_all *s)
{
	s->win.mlx = mlx_init();
	s->win.win = mlx_new_window(s->win.mlx, s->win.w, s->win.h, "3D");
	write_textures(s);
	s->array[(int)s->plr.y][(int)s->plr.x] = '0';
	raycasting_1(s);
}

/*
** функция экстренного завершения программы
** освобожает память, если она была аллоцирована
*/

void	ft_exit(char *str, t_all *all)
{
	int i;

	i = 0;
	ft_putstr_fd("ERROR!\n", 1);
	ft_putstr_fd(str, 1);
	write(1, "\n", 1);
	if (all->array)
		free(all->array);
	if (all->arrrecuv)
	{
		while (all->arrrecuv[i])
			free(all->arrrecuv[i++]);
		free(all->arrrecuv);
	}
	if (all->sprite)
		free(all->sprite);
	if (all)
		free(all);
	exit(1);
}
