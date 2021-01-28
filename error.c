//
//  error.c
//  cub3d
//
//  Created by Torres Saiyan on 1/28/21.
//  Copyright © 2021 21school. All rights reserved.
//

#include "cub3d.h"

int	error(t_all *all)
{
	if (all->map.error)
		return (1);

	return (0);
}
