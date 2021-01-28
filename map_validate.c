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


int player_on_border(t_all *all)
{
	
	return (0);
}

int	find_bad_char(char str)
{
	if (str == 32 || str == '\0')
		return (1);
	return(0);
}


/*
** проверка вокруг игрока / спрайта (что нет пробела или пустоты)
** проверка что игрок / спрайт не лежат на краях
*/

int	check_around(t_all *all, int i, int j)
{
	char **map = all->array;
	
	if (i == 0 || i == ft_strlen(*map) || j == 0 || j == ft_strlen(map[i]))
	{
		all->map.error = 1;
		write(1, "BAD SPACING IN MAP!\n", 20);
		return (1);
	}
		
		
	if (find_bad_char(map[i][j + 1]) || \
		find_bad_char(map[i + 1][j]) || \
		find_bad_char(map[i + 1][j + 1]) || \
		find_bad_char(map[i - 1][j]) || \
		find_bad_char(map[i][j - 1]) || \
		find_bad_char(map[i - 1][j - 1]) )
	{
		all->map.error = 1;
		write(1, "SOMETHING OVERBOARD!\n", 21);
		return (1);
	}
	return(0);
}

/*
** ищет игрока
** проверяет что вокруг него все ок
*/

int	find_player(t_all *all)
{
	int i = 0;
	int j = 0;
	while (all->array[i])
	{
		while (all->array[i][j])
		{
			if ( all->array[i][j] == 'N' || all->array[i][j] == 'S' || \
				all->array[i][j] == 'W' || all->array[i][j] == 'E')
			{
				if (all->plr.plook)
				{
					all->map.error = 1;
					write(1, "BAD PLAYER!\n", 12);
					return (0);
				}
				all->plr.plook = all->array[i][j];
				if (check_around(all, i, j))
					return (0);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (all->plr.plook ? 1 : 0);
}

int	map_validate(t_all *all)
{
	if (!find_player(all))
	{
		write(1, "WHERE IS PLAYER?\n", 18);
		return (0);
	}
	return(1);
}

