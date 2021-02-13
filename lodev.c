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

unsigned            get_color(t_all *all, int x, int y)
{
	t_txr *data = &all->tx;
	double step = (all->tx.de - all->tx.ds);
	step /= data->w;
    char    *dst;
	
	dst = all->tx.ptr;
	dst +=  x * (data->bpp / 8);
	int color = *(unsigned int*)dst;
	//printf("color = %u\n", color);
	return (color);
}


// считываем кнопки
int key_press(int key, t_all *all)
 {
	 double FOOT = 0.5;
	 double rotSpeed = 0.05;
	 double planeX = all->plr.planeX;
	 double planeY = all->plr.planeY;
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
	all->array[(int)all->plr.y][(int)all->plr.x] = '0';
	all->win.img = mlx_new_image(all->win.mlx, w, h);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_l, &img->en);
	all->tx.addr = mlx_xpm_file_to_image(all->win.mlx, "./images/lgbt2.xpm", &all->tx.w, &all->tx.h);
	all->tx.ptr = mlx_get_data_addr(all->tx.addr, &all->tx.bpp,  &all->tx.line_l,  &all->tx.en);
/* wall */
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
	  if(side == 0)
		  perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
	  else
		  perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

	  //Calculate height of line to draw on screen
			int lineHeight = (int)(h / perpWallDist);

		
	  //calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if(drawStart < 0)
		  drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h)
		  drawEnd = h - 1;
		
		//textures
		 int texNum = worldMap[mapX][mapY] - 1;
		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if(side == 0) wallX = posY + perpWallDist * rayDirY;
		else          wallX = posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));
		//x coordinate on the texture
		int texX = (int)(wallX * (double)(all->tx.w));
		if(side == 0 && rayDirX > 0) texX = all->tx.w - texX - 1;
		if(side == 1 && rayDirY < 0) texX = all->tx.w - texX - 1;

		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * all->tx.h / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
		
		
		int y;
		all->tx.line_l = lineHeight;
		all->tx.de = drawEnd;
		all->tx.ds = drawStart;
		for (y = 0; y < drawStart; y++)
			my_mlx_pixel_put(&all->win, x, y, 0x00bfff);
		for(int y = drawStart; y < drawEnd; y++)
		{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)texPos & (all->tx.h - 1);
		texPos += step;
		 int color = get_color(all, texY, texX);
		  //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if(side == 1) color = (color >> 1) & 8355711;
			my_mlx_pixel_put(&all->win, x, y, color);
		}
		for (y = drawEnd; y < all->win.vert; y++)
			my_mlx_pixel_put(&all->win, x, y, 0x754500);
	}
	mlx_put_image_to_window(all->win.mlx, all->win.win, all->win.img, 0, 0);
}
