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

#include "../cub3d.h"

/*
** рекурсивная заливка поля 1
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

/*
** рекурсивная заливка поля 2
*/

int	recursive_needed(t_all *all, int i, int j)
{
	if (all->arrrecuv[i][j] != all->plr.plook && \
		all->arrrecuv[i][j] != '1')
		return (1);
	return (0);
}

/*
** рекурсивная заливка поля 3
*/

int	fill_error(t_all *all, int i, int j)
{
	if (all->arrrecuv[i][j] == '1' || all->arrrecuv[i][j] == 'x')
		return (0);
	if (all->arrrecuv[i][j] == 0 || all->arrrecuv[i][j] == ' ')
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
** поиск левых символов в карте
*/

int	bad_chars_in_map(t_all *all)
{
	char chr;
	char **str;
	int i = 0;
	int j = 0;
	//puts("bad_chars_in_map start");
	str = all->array;
		while(str[i])
		{
			j = 0;
			puts(str[i]);
			while(str[i][j])
			{
				chr = str[i][j];
				if (chr != 'W' && chr != 'N' && chr != 'S' && chr != 'E' \
					&& chr != '1' &&  chr != 32 && chr != '1' && chr != '2' \
					&& chr != '0' && chr != '\0')
				{
					all->map.error = 1;
					write(1, "BAD CHAR IN MAP\n", 16);
					printf("c=%d\n", chr);
					printf("j=%d\n", j);
					return (1);
				}
				j++;
			}
			i++;
		}
	return (0);
}

/*
** проверка границ поля
*/

int	borders_ok(t_all *all)
{
	int i;

	i = 0;
	while (all->array[0][i])
		if (all->array[0][i++] != '1')
			return (0);
	i = 0;
	while (all->array[all->map.lines][i])
		if (all->array[0][i++] != '1')
			return (0);
	i = 0;
	while (all->array[i][0])
		if (all->array[i][0] != '1')
			return (0);
	i = 0;
	while (all->array[i][ft_strlen(all->array[i])])
	{
		if (all->array[i][ft_strlen(all->array[i])] != '1')
			return (0);
		i++;
	}
	return (1);
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
	puts("find_player");
	return (all->plr.plook ? 1 : 0);
}
