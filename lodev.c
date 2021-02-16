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

void	lodev(t_all *s)
{
	double sideDistX;
	double sideDistY;
	double oldsideDist;
	double perpWsDist;
	int stepX;
	int stepY;
	double deltaDistX;
	double deltaDistY;
	double wsX;
	int y;
	int color;
	double cameraX;
	double rayDirX;
	double rayDirY;
	int mapX;
	int mapY;
	int hit;
	int side;
	int x;
	int texX;
	int texY;
	int lineHeight;
	double step;
	double texPos;

	s->array[(int)s->plr.y][(int)s->plr.x] = '0';
	s->win.img = mlx_new_image(s->win.mlx, s->win.w, s->win.h);
	s->win.addr = mlx_get_data_addr(s->win.img, &s->win.bpp, &s->win.line_l, &s->win.en);
	write_textures(s);
	for(x = 0; x < s->win.w; x++)
	{
		cameraX = 2 * x / (double)s->win.w - 1;
		rayDirX = s->plr.start + s->plr.planeX * cameraX;
		rayDirY = s->plr.end + s->plr.planeY * cameraX;
		mapX = (int)s->plr.x;
		mapY = (int)s->plr.y;
		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);
		hit = 0;
		side = 0;
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (s->plr.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - s->plr.x) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (s->plr.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - s->plr.y) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				oldsideDist = sideDistX;
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				oldsideDist = sideDistY;
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (s->array[mapY][mapX] > '0')
				hit = 1;
		}
		if(side == 0)
			perpWsDist = (mapX - s->plr.x + (1 - stepX) / 2) / rayDirX;
		else
			perpWsDist = (mapY - s->plr.y + (1 - stepY) / 2) / rayDirY;
		lineHeight = (int)(s->win.h / perpWsDist);
		int drawStart = -lineHeight / 2 + s->win.h / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + s->win.h / 2;
		if(drawEnd >= s->win.h)
			drawEnd = s->win.h - 1;
		if(side == 0)
			wsX = s->plr.y + perpWsDist * rayDirY;
		else
			wsX = s->plr.x + perpWsDist * rayDirX;
		wsX -= floor((wsX));
		texX = (int)(wsX * (double)(s->no.w));
		if(side == 0 && rayDirX > 0)
			texX = s->no.w - texX - 1;
		if(side == 1 && rayDirY < 0)
			texX = s->no.w - texX - 1;
		step = 1.0 * s->no.h / lineHeight;
		texPos = (drawStart - s->win.h / 2 + lineHeight / 2) * step;
		for (y = 0; y < drawStart; y++)
			my_mlx_pixel_put(&s->win, x, y, create_rgb(s->c.r, s->c.g, s->c.b));
		for(int y = drawStart; y < drawEnd; y++)
		{
			texY = (int)texPos & (s->no.h - 1);
			texPos += step;
			color = get_color(s, texX, texY, 'W');
			if (side)
			{
				if (stepY > 0)
					color = get_color(s, texX, texY, 'S');
				else
					color = get_color(s, texX, texY, 'N');
			}
			else
				{
				if (stepX > 0)
					color = get_color(s, texX, texY, 'E');
				else
					color = get_color(s, texX, texY, 'W');
			}
			my_mlx_pixel_put(&s->win, x, y, color);
		}
		for (y = drawEnd; y < s->win.h; y++)
			my_mlx_pixel_put(&s->win, x, y, create_rgb(s->fl.r, s->fl.g, s->fl.b));
	}
	mlx_put_image_to_window(s->win.mlx, s->win.win, s->win.img, 0, 0);
}
