//
//  textures.c
//  cub3d
//
//  Created by Torres Saiyan on 2/13/21.
//  Copyright © 2021 21school. All rights reserved.
//

#include <cub3d.h>

void	write_textures(t_all *all)
{
	t_txr *st = NULL;
	st = &all->no;
		st->addr = mlx_xpm_file_to_image(all->win.mlx, all->map.no_way, &st->w, &st->h);
		st->ptr = mlx_get_data_addr(st->addr, &st->bpp,  &st->line_l,  &st->en);
	st = &all->we;
		st->addr = mlx_xpm_file_to_image(all->win.mlx, all->map.we_way, &st->w, &st->h);
		st->ptr = mlx_get_data_addr(st->addr, &st->bpp,  &st->line_l,  &st->en);
}



unsigned            get_color(t_all *all, int x, int y, char side)
{
	t_txr *data = &all->tx;
//	if (side == 'N')
//		 data = &all->no;
//	else if (side == 'W')
//		 data = &all->we;
//	else
//		 data = &all->tx;
    char    *dst = NULL;
	dst = data->ptr;
	dst += (x * 4) + (y * data->line_l);
	int color = *(unsigned int*)dst;
	//printf("color = %u\n", color);
	return (color);
}
