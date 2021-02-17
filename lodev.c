/* ************************************************************************** */
/*																																						*/
/*																												:::			::::::::	 */
/*	 cub3d																							:+:			:+:		:+:	 */
/*																										+:+ +:+				 +:+		 */
/*	 By: tsaiyan <tsaiyan@42.fr>										+#+	+:+			 +#+				*/
/*																								+#+#+#+#+#+	 +#+					 */
/*	 Created: 2021/01/28 18:29:13 by tsaiyan					 #+#		#+#						 */
/*	 Updated: 2021/01/28 18:29:15 by tsaiyan					###	 ########.fr			 */
/*																																						*/
/* ************************************************************************** */

#include "cub3d.h"
#define numSprites 19
#define texWidth 3
#define texHeight 3
typedef struct Sprite
{
	double x;
	double y;
	int texture;
}	Sprite;

void	lodev(t_all *s)
{
	Sprite sprite[numSprites] =
	{
		//row of pillars in front of wall: fisheye test
		{10, 5, 9},

		//some barrels around the map
	};
	double ZBuffer[s->win.w];
	int spriteOrder[numSprites];
	double spriteDistance[numSprites];
	double sideDistX;
	double sideDistY;
	double oldsideDist;
	double perpWallDist;
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
			perpWallDist = (mapX - s->plr.x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - s->plr.y + (1 - stepY) / 2) / rayDirY;
		lineHeight = (int)(s->win.h / perpWallDist);
		int drawStart = -lineHeight / 2 + s->win.h / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + s->win.h / 2;
		if(drawEnd >= s->win.h)
			drawEnd = s->win.h - 1;
		if(side == 0)
			wsX = s->plr.y + perpWallDist * rayDirY;
		else
			wsX = s->plr.x + perpWallDist * rayDirX;
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
			ZBuffer[x] = perpWallDist;
		
	}
	//SPRITE CASTING
		//sort sprites from far to close
		for(int i = 0; i < numSprites; i++)
		{
		spriteOrder[i] = i;
		spriteDistance[i] = ((s->plr.x - sprite[i].x) * (s->plr.x - sprite[i].x) + (s->plr.y - sprite[i].y) * (s->plr.y - sprite[i].y)); //sqrt not taken, unneeded
		}
		//sortSprites(spriteOrder, spriteDistance, numSprites);

		//after sorting the sprites, do the projection and draw them
		for(int i = 0; i < numSprites; i++)
		{
		//translate sprite position to relative to camera
		double spriteX = sprite[spriteOrder[i]].x - s->plr.x;
		double spriteY = sprite[spriteOrder[i]].y - s->plr.y;

		//transform sprite with the inverse camera matrix
		 // [ planeX	 dirX ] -1																			 [ dirY			-dirX ]
		 // [							 ]			 =	1/(planeX*dirY-dirX*planeY) *	 [								 ]
		 // [ planeY	 dirY ]																					[ -planeY	planeX ]

		double invDet = 1.0 / (s->plr.planeX * s->plr.end - s->plr.start * s->plr.planeY); //required for correct matrix multiplication

		double transformX = invDet * (s->plr.end * spriteX - s->plr.start * spriteY);
		double transformY = invDet * (-s->plr.planeY * spriteX + s->plr.planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		int spriteScreenX = (int)((s->win.w / 2) * (1 + transformX / transformY));

	 //	int vMoveScreen = (int)(vMove / transformY);

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(s->win.h / (transformY))); //using "transformY" instead of the real distance prevents fisheye
		 //calculate lowest and highest pixel to fill in current stripe
		int drawStartY = (s->win.h / 2) - (spriteHeight / 2);
		if (drawStartY < 0)
			drawStartY = 0;
		int drawEndY = (spriteHeight / 2) + (s->win.h / 2);
		if (drawEndY >= s->win.h)
			drawEndY = s->win.h - 1;

		 //calculate width of the sprite
		int spriteWidth = abs( (int)(s->win.w / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0)
			drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= s->win.w)
			drawEndX = s->win.w;

		 //loop through every vertical stripe of the sprite on screen
		int stripe = drawStartX;
		while (stripe < drawEndX)
		{
			//int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
			 //the conditions in the if are:
			 //1) it's in front of camera plane so you don't see things behind you
			 //2) it's on the screen (left)
			 //3) it's on the screen (right)
			 //4) ZBuffer, with perpendicular distance
			if(transformY > 0 && stripe > 0 && stripe < s->win.w && transformY < ZBuffer[stripe])
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
			{
				//int d = y * 256 - s->win.h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
				//int texY = ((d * texHeight) / spriteHeight) / 256;
				color = 0xFF0000; //get current color from the texture
				// if((color & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(&s->win, stripe, y, 0xFFF000);
					// buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
			}
			stripe++;
		}
		}

	mlx_put_image_to_window(s->win.mlx, s->win.win, s->win.img, 0, 0);
}

////sort the sprites based on distance
//void sortSprites(int* order, double* dist, int amount)
//{
//	std::vector<std::pair<double, int>> sprites(amount);
//	for(int i = 0; i < amount; i++) {
//		sprites[i].first = dist[i];
//		sprites[i].second = order[i];
//	}
//	std::sort(sprites.begin(), sprites.end());
//	// restore in reverse order to go from farthest to nearest
//	for(int i = 0; i < amount; i++) {
//		dist[i] = sprites[amount - i - 1].first;
//		order[i] = sprites[amount - i - 1].second;
//	}
//}
