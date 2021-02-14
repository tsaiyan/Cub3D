//
//  lodev_utils.c
//  cub3d
//
//  Created by Torres Saiyan on 2/13/21.
//  Copyright © 2021 21school. All rights reserved.
//

#include "cub3d.h"

//вывод изображения
void            my_mlx_pixel_put(t_win *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_l + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}



// считываем кнопки
int key_press(int key, t_all *all)
 {
	 double FOOT = 0.1;
	 double rotSpeed = 0.05;
	 double planeX = all->plr.planeX;
	 double planeY = all->plr.planeY;
	 double posX = all->plr.x;
	 double posY = all->plr.y;
	 double dirX = all->plr.start;
	 double dirY = all->plr.end;
	//printf("\npress\n");
	//mlx_clear_window(all->win.mlx, all->win.win);
	if (key == 13)
	{
		//printf("%c\n", all->array[(int)(posY + dirY)][(int)(posX + dirX)]);
		if (all->array[(int)(posY + dirY)][(int)(posX + dirX)] == '0')
		{
			all->plr.x += dirX * FOOT;
			all->plr.y += dirY * FOOT;
		}
	}
	if (key == 1)
	{
		//printf("%c\n", all->array[(int)posY][(int)(posX - FOOT)]);
		if (all->array[(int)(posY - dirY)][(int)(posX - dirX)] == '0')
		{
			all->plr.x -= dirX * FOOT;
			all->plr.y -= dirY * FOOT;
		}
	}
	 ///w
	 if (key == 12)
	 {
		 if (all->array[(int)(posY - all->plr.start)][(int)posX] == '0')
		 all->plr.y -= all->plr.start;
	 }
	 //s
	 if (key == 14)
	 {
		 if (all->array[(int)(posY + all->plr.start)][(int)posX] == '0')
		 all->plr.y += all->plr.start;
	 }
	 //left
	if (key == 0)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = dirX;
		all->plr.start = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		all->plr.end = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		double oldPlaneX = planeX;
		all->plr.planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		all->plr.planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	 //right
	if (key == 2)
	 {
	   //both camera direction and camera plane must be rotated
	   double oldDirX = dirX;
	   all->plr.start = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
	   all->plr.end = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
	   double oldPlaneX = planeX;
	   all->plr.planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
	   all->plr.planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	 }
	if (key == 53)
		exit(0);
	lodev(all);
	return(0);
 }

void	lodev_init(t_all *all)
{
	all->win.mlx = mlx_init();
	all->win.win = mlx_new_window(all->win.mlx, all->win.gorisont, all->win.vert, "3D");
	//ft_floor(all);
	lodev(all);
}
