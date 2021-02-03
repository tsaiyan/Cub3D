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

int	error(t_all *all)
{
	if (bad_chars_in_map(all) || !borders_ok(all)|| all->map.error || !find_player(all))
	{
		write(1, "ERROR MAP!\n", 11);
		return (1);
	}
	return (0);
}
