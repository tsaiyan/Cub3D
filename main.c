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


#include <math.h>
#include <string.h>
#include "cub3d.h"

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

void printf_checks(t_all *all)
{
	puts("- - -- - - - - - - - - - -- - - ");
	int i = 0;
	puts("filled map:");
	while(i < (all->map.lines - 1))
		printf("%s\n", all->arrrecuv[i++]);
	printf("\nR vert			=%d\n", all->win.vert);
	printf("R gor			=%d\n", all->win.gorisont);
	printf("NO texture		=%s\n", all->map.no_way);
	printf("SO texture		=%s\n", all->map.so_way);
	printf("WE texture		=%s\n", all->map.we_way);
	printf("EA texture		=%s\n", all->map.ea_way);
	printf("Sprite texture		=%s\n", all->map.s_way);
	printf("Floor color		=%s\n", all->map.floor_color);
	printf("Sky color		=%s\n", all->map.sky_color);
	printf("Player looks at		=%c\n", all->plr.plook);
	i = 0;
	puts("\nmap:");
	while(all->array[i])
		printf("%s\n", all->array[i++]);
	puts("- - -- - - - - - - - - - -- - - ");
}



int main(int argc, char **argv)
{
	t_all *all;
	printf("argc=%d\n", argc);
	if (argc != 2)
	{
		puts("wrong input file");
		return (-1);
	}
	if (!(all = malloc(sizeof(t_all))))
		return (-1);
	ft_putin(all);
	ft_map_parcer(all, argv[1]);
	if (error(all))
		return (-1);
	//printf_checks(all);
	lodev_init(all);
	mlx_hook(all->win.win, 2, (1L << 0), key_press, all);
	//visual_map(all);
	mlx_loop(all->win.mlx);
}
