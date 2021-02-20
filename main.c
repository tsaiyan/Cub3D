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

/*
** СТРУКТУРА ПРОГРАММЫ:
** main: аллоцируем структуру
** ft_putin: заполняем исходные значения структуры
** ft_map_parcer: записываем карту в массив через gnl
** ft_map_parcer -> config map: запись конфиг путей карты
** ft_map_parcer -> check_ways: проверяет, что все пути были записаны
** map_utils -> find_player: ищет игрока на карте, проверяет, что он один
** map_utils -> write_player_pi: записывает в стуктуру игрока направление
** map_utils -> floor_color: запись в 0x цвета пола и потолка
** map_utils -> map_copy: копирование карты для валидации / longer_str, mapdup
** map_utils -> map_check_around: валидация карты / check_around
** дальше идет рейкастинг
*/

int main(int argc, char **argv)
{
	t_all *all;
	if (argc != 2)
		return (0 * (int)write(1, "ERROR\n", 7));
	if (!(all = malloc(sizeof(t_all))))
		return (-1);
	ft_putin(all);
	ft_map_parcer(all, argv[1]);
	map_utils(all);
	lodev_init(all);
	mlx_hook(all->win.win, 2, (1L << 0), key_press, all);
//	mlx_loop_hook(all->win.mlx, lodev, all);
	mlx_loop(all->win.mlx);
}

//void printf_checks(t_all *all)
//{
//	puts("- - -- - - - - - - - - - -- - - ");
//	int i = 0;
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
//	puts("rec map:");
//	while(all->arrrecuv[i])
//		printf("\nstr =%s|", all->arrrecuv[i++]);
//	puts("- - -- - - - - - - - - - -- - - ");
//}
