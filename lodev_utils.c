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

void	pixel_put(t_win *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_l + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

/*
** инициализация окна
*/

void	lodev_init(t_all *s)
{
	s->win.mlx = mlx_init();
	s->win.win = mlx_new_window(s->win.mlx, s->win.w, s->win.h, "3D");
	write_textures(s);
	s->array[(int)s->plr.y][(int)s->plr.x] = '0';
	lodev(s);
	
}

/*
** функция экстренного завершения программы
** освобожает память, если она была аллоцирована
*/

void	ft_exit(char *str, t_all *all)
{
	ft_putstr_fd("ERROR!\n", 1);
	ft_putstr_fd(str, 1);
	write(1, "\n", 1);
	if (all->array)
		free(all->array);
	if (all->arrrecuv)
		free(all->arrrecuv);
	if (all)
		free(all);
	exit(1);
}
