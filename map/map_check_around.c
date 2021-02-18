//
//  map_check_around.c
//  cub3d
//
//  Created by Artyom on 18.02.2021.
//  Copyright © 2021 21school. All rights reserved.
//

#include "cub3d.h"

int	longer_str(t_all *s)
{
	int lenght;
	int j;
	int i;

	j = 0;
	lenght = 0;
	i = 0;
	while (s->array[j])
	{
		while (s->array[j][i]);
		if (i > lenght)
			lenght = i;
		i = 0;
		j++;
	}
	return (lenght);
}

char	*mapdup(t_all *s, char *src)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = malloc(ft_strlen(src) + 1);
	if (dest == 0)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**map_copy(t_all *all)
{
	char **line;
	int j = 0;
	int i = all->map.lines;

	line = (char **)malloc(sizeof(char*) * (i + 1));
	line[i--] = NULL;
	while (i--)
	{
		line[j] = ft_strdup(all->array[j]);
		j++;
	}
	return(line);
}
