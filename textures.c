//
//  textures.c
//  cub3d
//
//  Created by Torres Saiyan on 2/13/21.
//  Copyright © 2021 21school. All rights reserved.
//

#include <cub3d.h>

void	write_textures_small(t_txr *st, t_all *all)
{
		st->addr = mlx_xpm_file_to_image(all->win.mlx, st->way, &st->w, &st->h);
	if (!st->addr)
	{
		write(1, "error : can't open texture\n", 27);
		exit(1);
	}
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



unsigned            get_color(t_all *all, int x, int y, char side)
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
	//printf("color = %u\n", color);
	return (color);
}

int		create_rgb(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

