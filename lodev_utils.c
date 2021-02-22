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
	char	*dst;

	dst = data->addr + (y * data->line_l + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
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
