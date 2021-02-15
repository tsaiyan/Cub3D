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

static void	ft_putnbr_x(unsigned n)
{
	char	*array;
	char	result_array[ft_rank_count(n, 16) + 1];
	size_t	len;

	len = ft_rank_count(n, 16);
	array = "0123456789abcdef";
	result_array[len] = '\0';
	if (n == 0)
		result_array[--len] = 48;
	else
		while (n != 0)
		{
			result_array[--len] = array[n % 16];
			n /= 16;
		}
	while (result_array[len])
		putchar(result_array[len++]);
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
	//mlx_key_hook(all->win.win, key_press, all);
	mlx_hook(all->win.win, 2, (1L << 0), key_press, all);
	//visual_map(all);
	mlx_loop(all->win.mlx);
}
