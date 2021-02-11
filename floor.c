//
//  floor.c
//  cub3d
//
//  Created by Torres Saiyan on 2/10/21.
//  Copyright © 2021 21school. All rights reserved.
//

#include <cub3d.h>



//void	ft_floor(t_all *all)
//{
//	void    *img;
//	char    *relative_path = "./images/FL.xpm";
//	int     img_width;
//	int     img_height;
//	int screenHeight = all->win.vert;
//	int screenWidth = all->win.gorisont;
//	double dirX = all->plr.start;
//	double dirY = all->plr.end;
//	double planeX = all->plr.planeX;
//	double planeY = all->plr.planeY;
//	double posX = all->plr.x;
//	double posY = all->plr.y;
//	int texWidth = 64;
//	int texHeight = 64;
//	all->tx.ptr = mlx_xpm_file_to_image(all->win.mlx, relative_path, &all->tx.w,  &all->tx.h);
//	if (!all->tx.ptr)
//		puts("TEXTURE NOT LOADED");
//	char buffer[all->tx.w][all->tx.h];
//	for(int y = screenHeight / 2 + 1; y < screenHeight; ++y)
//	   {
//		 // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
//		 float rayDirX0 = dirX - planeX;
//		 float rayDirY0 = dirY - planeY;
//		 float rayDirX1 = dirX + planeX;
//		 float rayDirY1 = dirY + planeY;
//
//		 // Current y position compared to the center of the screen (the horizon)
//		 int p = y - screenHeight / 2;
//
//		 // Vertical position of the camera.
//		 // NOTE: with 0.5, it's exactly in the center between floor and ceiling,
//		 // matching also how the walls are being raycasted. For different values
//		 // than 0.5, a separate loop must be done for ceiling and floor since
//		 // they're no longer symmetrical.
//		 float posZ = 0.5 * screenHeight;
//
//		 // Horizontal distance from the camera to the floor for the current row.
//		 // 0.5 is the z position exactly in the middle between floor and ceiling.
//		 // NOTE: this is affine texture mapping, which is not perspective correct
//		 // except for perfectly horizontal and vertical surfaces like the floor.
//		 // NOTE: this formula is explained as follows: The camera ray goes through
//		 // the following two points: the camera itself, which is at a certain
//		 // height (posZ), and a point in front of the camera (through an imagined
//		 // vertical plane containing the screen pixels) with horizontal distance
//		 // 1 from the camera, and vertical position p lower than posZ (posZ - p). When going
//		 // through that point, the line has vertically traveled by p units and
//		 // horizontally by 1 unit. To hit the floor, it instead needs to travel by
//		 // posZ units. It will travel the same ratio horizontally. The ratio was
//		 // 1 / p for going through the camera plane, so to go posZ times farther
//		 // to reach the floor, we get that the total horizontal distance is posZ / p.
//		 float rowDistance = posZ / p;
//
//		 // calculate the real world step vector we have to add for each x (parallel to camera plane)
//		 // adding step by step avoids multiplications with a weight in the inner loop
//		 float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / screenWidth;
//		 float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / screenWidth;
//
//		 // real world coordinates of the leftmost column. This will be updated as we step to the right.
//		 float floorX = posX + rowDistance * rayDirX0;
//		 float floorY = posY + rowDistance * rayDirY0;
//
//		 for(int x = 0; x < screenWidth; ++x)
//		 {
//		   // the cell coord is simply got from the integer parts of floorX and floorY
//		   int cellX = (int)(floorX);
//		   int cellY = (int)(floorY);
//
//		   // get the texture coordinate from the fractional part
//		   int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
//		   int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);
//
//		   floorX += floorStepX;
//		   floorY += floorStepY;
//
//		   // choose texture and draw the pixel
//		   int checkerBoardPattern = ((int)(cellX + cellY)) & 1;
//		   int floorTexture;
//		   if(checkerBoardPattern == 0) floorTexture = 3;
//		   else floorTexture = 4;
//		   int ceilingTexture = 6;
//		   int color;
//
//		   // floor
//			 color = get_color(&all->tx, tx, ty);
//			// texture[floorTexture][texWidth * ty + tx];
//		   color = (color >> 1) & 8355711; // make a bit darker
//		   buffer[y][x] = color;
//
//		   //ceiling (symmetrical, at screenHeight - y - 1 instead of y)
////		   color = texture[ceilingTexture][texWidth * ty + tx];
////		   color = (color >> 1) & 8355711; // make a bit darker
////		   buffer[screenHeight - y - 1][x] = color;
//		 }
//	   }
//	//FLOOR CASTING
//	 double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall
//
//	 //4 different wall directions possible
//	 if(side == 0 && rayDirX > 0)
//	 {
//	   floorXWall = mapX;
//	   floorYWall = mapY + wallX;
//	 }
//	 else if(side == 0 && rayDirX < 0)
//	 {
//	   floorXWall = mapX + 1.0;
//	   floorYWall = mapY + wallX;
//	 }
//	 else if(side == 1 && rayDirY > 0)
//	 {
//	   floorXWall = mapX + wallX;
//	   floorYWall = mapY;
//	 }
//	 else
//	 {
//	   floorXWall = mapX + wallX;
//	   floorYWall = mapY + 1.0;
//	 }
//
//	 double distWall, distPlayer, currentDist;
//
//	 distWall = perpWallDist;
//	 distPlayer = 0.0;
//
//	 if(drawEnd < 0) drawEnd = h; //becomes < 0 when the integer overflows
//
//	 //draw the floor from drawEnd to the bottom of the screen
//	 for(int y = drawEnd + 1; y < h; y++)
//	 {
//	   currentDist = h / (2.0 * y - h); //you could make a small lookup table for this instead
//
//	   double weight = (currentDist - distPlayer) / (distWall - distPlayer);
//
//	   double currentFloorX = weight * floorXWall + (1.0 - weight) * posX;
//	   double currentFloorY = weight * floorYWall + (1.0 - weight) * posY;
//
//	   int floorTexX, floorTexY;
//	   floorTexX = int(currentFloorX * texWidth) & (texWidth - 1);
//	   floorTexY = int(currentFloorY * texHeight) & (texHeight - 1);
//
//	   int checkerBoardPattern = ((int)currentFloorX + (int)currentFloorY) & 1;
//	   int floorTexture;
//	   if(checkerBoardPattern == 0) floorTexture = 3;
//	   else floorTexture = 4;
//
//	   //floor
//	   buffer[y][x] = (texture[floorTexture][texWidth * floorTexY + floorTexX] >> 1) & 8355711;
//	   //ceiling (symmetrical)
//	   buffer[h - y][x] = texture[6][texWidth * floorTexY + floorTexX];
//	 }
//}
