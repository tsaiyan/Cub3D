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
** ищет игрока
** проверяет что вокруг него все ок
*/

void	find_player(t_all *all)
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
					ft_exit("double player in map", all);
				all->plr.plook = all->array[i][j];
				all->plr.y = i;
				all->plr.x = j;
			}
			j++;
		}
		i++;
	}
	if (!all->plr.plook)
		ft_exit("no player in map", all);
}

