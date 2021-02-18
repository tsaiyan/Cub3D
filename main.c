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

void printf_checks(t_all *all)
{
	puts("- - -- - - - - - - - - - -- - - ");
	int i = 0;
//	puts("filled map:");
//	while(i < (all->map.lines - 1))
//		printf("%s\n", all->arrrecuv[i++]);
//	printf("\nR vert			=%d\n", all->win.h);
//	printf("R gor			=%d\n", all->win.w);
//	printf("NO texture		=%s\n", all->map.no_way);
//	printf("SO texture		=%s\n", all->map.so_way);
//	printf("WE texture		=%s\n", all->map.we_way);
//	printf("EA texture		=%s\n", all->map.ea_way);
//	printf("Sprite texture		=%s\n", all->map.s_way);
//	printf("Floor color		=%s\n", all->map.floor_color);
//	printf("Sky color		=%s\n", all->map.sky_color);
//	printf("Player looks at		=%c\n", all->plr.plook);
//	i = 0;
	puts("rec map:");
	while(all->arrrecuv[i])
		printf("\nstr =%s | ", all->arrrecuv[i++]);
	//puts("- - -- - - - - - - - - - -- - - ");
}

size_t	ft_rank_count(unsigned long long n, int base)
{
	size_t i;

	if (n == 0)
		return (1);
	i = 0;
	while (n)
	{
		i++;
		n /= base;
	}
	return (i);
}

int main(int argc, char **argv)
{
	t_all *all;
	if (argc != 2)
		return (0 * (int)write(1, "ERROR\n", 7));
	if (!(all = malloc(sizeof(t_all))))
		return (-1);
	ft_putin(all);
	ft_map_parcer(all, argv[1]);
	printf_checks(all);
	if (error(all))
		return (-1);
	lodev_init(all);
	mlx_hook(all->win.win, 2, (1L << 0), key_press, all);
//	mlx_loop_hook(all->win.mlx, lodev, all);
	mlx_loop(all->win.mlx);
}
