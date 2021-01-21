//
//  mlx.c
//  cub3d
//
//  Created by Torres Saiyan on 1/21/21.
//  Copyright © 2021 21school. All rights reserved.
//

#include "mms/mlx.h"
#include "libft/libft.h"

int main (void)
{
	void *mlx = NULL;
	void *win = NULL;
	int x = 100;
	int y = 100;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 640, 480, "window");
	while (y++ < 200)
	{
		x = 100;
		while (x++ < 200)
			mlx_pixel_put(mlx, win, x, y, 0xFFFFFF);
	}
	mlx_loop(mlx);
}
