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

int		check_save(char *str, t_all *s)
{
	char	*save;
	int		res;

	save = "--save";
	res = ft_strncmp(str, save, ft_strlen(str));
	if (res == 0)
		return (1);
	else
		ft_exit("bad save argv", s);
	return (0);
}

void	key_exit(t_all *s)
{
	ft_exit("no. it's cross pressed", s);
}

int		main(int argc, char **argv)
{
	t_all *all;

	if ((argc != 2 && argc != 3) || !(all = malloc(sizeof(t_all))))
		return (0 * (int)write(1, "ERROR\n", 7));
	all->argc = argc;
	ft_putin(all);
	ft_map_parcer(all, argv[1]);
	map_utils(all);
	raycasting_init(all);
	if (argc == 3 && check_save(argv[2], all))
		screenshot(all);
	mlx_hook(all->win.win, 2, 0, key_press, all);
	mlx_hook(all->win.win, 17, 0, key_exit, all);
	mlx_loop(all->win.mlx);
}
