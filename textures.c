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

#include <cub3d.h>

void	write_textures_small(t_txr *st, t_all *all)
{
		st->addr = mlx_xpm_file_to_image(all->win.mlx, st->way, &st->w, &st->h);
	if (!st->addr)
		ft_exit("can't open texture", all);
		st->ptr = mlx_get_data_addr(st->addr, &st->bpp,  &st->line_l,  &st->en);
}

void	write_textures(t_all *all)
{
	t_txr *st = NULL;
	st = &all->no;
	write_textures_small(st, all);
	st = &all->we;
	write_textures_small(st, all);
	st = &all->so;
	write_textures_small(st, all);
	st = &all->ea;
	write_textures_small(st, all);
}

unsigned	get_color(t_all *all, int x, int y, char side)
{
	t_txr *data;
	if (side == 'N')
		 data = &all->no;
	else if (side == 'W')
		 data = &all->we;
	else if (side == 'E')
		 data = &all->ea;
	else if (side == 'S')
		 data = &all->so;
	else
		return (0);
    char    *dst = NULL;
	dst = data->ptr;
	dst +=  (x * (data->bpp / 8)) + (y * data->line_l);
	int color = *(unsigned int*)dst;
	return (color);
}

int		create_rgb(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}
