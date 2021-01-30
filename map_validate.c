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
** рекурсивная заливка поля
*/

int	find_bad_char(t_all *all, char chr)
{
	if (chr == 32 || chr == '\0')
	{
		all->map.error = 1;
		puts("PLAYER IN THE SPACE!\n");
		return (1);
	}
	puts("fbc runs\n");
	return (0);
}

int	recursive_needed(t_all *all, int i, int j)
{
	if (all->arrrecuv[i][j] != all->plr.plook && \
		all->arrrecuv[i][j] != '1' && all->arrrecuv[i][j] != 'S')
		return (1);
	return (0);
}

int	fill_error(t_all *all, int i, int j)
{
	if (all->arrrecuv[i][j] == '1' || all->arrrecuv[i][j] == 'x')
		return (0);
	if (all->arrrecuv[i][j] == '\0' || all->arrrecuv[i][j] == ' ' \
		|| (all->arrrecuv[i][j] != '1' && i == 0))
	{
		all->map.error = 1;
		puts("the player can be sucked into space \n");
		return (1);
	}
	all->arrrecuv[i][j] = 'x';
	if (recursive_needed(all, i - 1, j))
		fill_error(all, i - 1, j);
	if (recursive_needed(all, i, j + 1))
		fill_error(all, i, j + 1);
	if (recursive_needed(all, i, j - 1))
		fill_error(all, i, j - 1);
	if (recursive_needed(all, i + 1, j))
		fill_error(all, i + 1, j);
	return (0);
}

/*
** проверка 1 по краям карты (для душных) и левые символы в ней
*/

int	bad_chars_in_map(t_all *all)
{
	char *chr;
	char **str;

	str = all->array;
	chr = *all->array;
	while(*all->array)
	{
		while(*str)
		{
			if (*chr != 'W' && *chr != 'N' && *chr != 'S' && *chr != 'E' \
				&& *chr != '1' &&  *chr != ' ' && *chr != '1' && *chr != '2' \
				&& *chr != '0' && *chr != '\0')
			{
				write(1, "bad_chars_in_map\n", 17);
				return (1);
			}
			if (*chr + 1 == '\0' && *chr != '1')
			{
				write(1, "NO WALL ON BORDER \n", 18);
			}
			chr++;
		}
		str++;
	}
	return (0);
}
/*
** ищет игрока
** проверяет что вокруг него все ок
*/

int	find_player(t_all *all)
{
	int i;
	int j;

	i = 0;
	while (all->array[i])
	{
		j = 0;
		while (all->array[i][j])
		{
			if (all->array[i][j] == 'N' || all->array[i][j] == 'S' || \
				all->array[i][j] == 'W' || all->array[i][j] == 'E')
			{
				if (all->plr.plook)
					return (0);
				all->plr.plook = all->array[i][j];
				if (fill_error(all, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (all->plr.plook ? 1 : 0);
}
