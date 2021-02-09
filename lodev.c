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
	 double FOOT = 0.5;
	 double posX = all->plr.x;
	 double posY = all->plr.y;
	 double dirX = all->plr.start;
	 double dirY = all->plr.end;
	printf("\npress\n");
	//mlx_clear_window(all->win.mlx, all->win.win);
	if (key == 13)
	{
		printf("%c\n", all->array[(int)(posY + dirY)][(int)(posX + dirX)]);
		if (all->array[(int)(posY + dirY)][(int)(posX + dirX)] == '0')
		{
			all->plr.x += dirX * FOOT;
			all->plr.y += dirY * FOOT;
		}
	}
	if (key == 1)
	{
		printf("%c\n", all->array[(int)posY][(int)(posX - FOOT)]);
		if (all->array[(int)(posY - dirY)][(int)(posX - dirX)] == '0')
		{
			all->plr.x -= dirX * FOOT;
			all->plr.y -= dirY * FOOT;
		}
	}
	 if (key == 12)
	 {
		 if (all->array[(int)(posY - all->plr.start)][(int)posX] == '0')
		 all->plr.y -= all->plr.start;
	 }
	 if (key == 14)
	 {
		 if (all->array[(int)(posY + all->plr.start)][(int)posX] == '0')
		 all->plr.y += all->plr.start;
	 }
	if (key == 0)
		all->plr.end -= 0.2;
	if (key == 2)
		all->plr.end += 0.2;
	if (key == 53)
		exit(0);
	lodev(all);
	return(0);
 }

void	lodev_init(t_all *all)
{
	all->win.mlx = mlx_init();
	all->win.win = mlx_new_window(all->win.mlx, all->win.gorisont, all->win.vert, "3D");
	lodev(all);
}
void	lodev(t_all *all)
{
	t_win	*img = &all->win;
	char **worldMap = all->array;
	double posX = all->plr.x;
	double posY = all->plr.y;  //x and y start position
	double dirX = all->plr.start;
	double dirY =  all->plr.end; //initial direction vector
	double planeX = all->plr.planeX, planeY = all->plr.planeY;//the 2d raycaster version of camera plane
	int w = img->gorisont;
	int h = img->vert;
	all->win.img = mlx_new_image(all->win.mlx, w, h);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_l, &img->en);
	for(int x = 0; x < img->gorisont; x++)
	{
	  //calculate ray position and direction
	  double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
	  double rayDirX = dirX + planeX * cameraX;
	  double rayDirY = dirY + planeY * cameraX;
	  //which box of the map we're in
	  int mapX = (int)posX;
	  int mapY = (int)posY;

	  //length of ray from current position to next x or y-side
	  double sideDistX;
	  double sideDistY;

	   //length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

	  //what direction to step in x or y-direction (either +1 or -1)
	  int stepX;
	  int stepY;

	  int hit = 0; //was there a wall hit?
	  int side; //was a NS or a EW wall hit?
	  //calculate step and initial sideDist
	  if(rayDirX < 0)
	  {
		stepX = -1;
		sideDistX = (posX - mapX) * deltaDistX;
	  }
	  else
	  {
		stepX = 1;
		sideDistX = (mapX + 1.0 - posX) * deltaDistX;
	  }
	  if(rayDirY < 0)
	  {
		stepY = -1;
		sideDistY = (posY - mapY) * deltaDistY;
	  }
	  else
	  {
		stepY = 1;
		sideDistY = (mapY + 1.0 - posY) * deltaDistY;
	  }
	  //perform DDA
	  while (hit == 0)
	  {
		//jump to next map square, OR in x-direction, OR in y-direction
		if(sideDistX < sideDistY)
		{
		  sideDistX += deltaDistX;
		  mapX += stepX;
		  side = 0;
		}
		else
		{
		  sideDistY += deltaDistY;
		  mapY += stepY;
		  side = 1;
		}
		//Check if ray has hit a wall
		  if(worldMap[mapY][mapX] > '0') hit = 1;
	  }
	  //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
	  if(side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
	  else          perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

	  //Calculate height of line to draw on screen
	  int lineHeight = (int)(h / perpWallDist);

	  //calculate lowest and highest pixel to fill in current stripe
	  int drawStart = -lineHeight / 2 + h / 2;
	  if(drawStart < 0)drawStart = 0;
	  int drawEnd = lineHeight / 2 + h / 2;
	  if(drawEnd >= h)drawEnd = h - 1;
		int y;
		
		for (y = drawStart; y < drawEnd; y++)
			my_mlx_pixel_put(&all->win, x, y, 0xFFFFF);
	}
	mlx_put_image_to_window(all->win.mlx, all->win.win, all->win.img, 0, 0);
}
