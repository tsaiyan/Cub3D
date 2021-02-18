//
//  map_check_around.c
//  cub3d
//
//  Created by Artyom on 18.02.2021.
//  Copyright © 2021 21school. All rights reserved.
//

#include "cub3d.h"

void	longer_str(t_all *s)
{
	int lenght;
	int j;
	int i;

	j = 0;
	lenght = 0;
	i = 0;
	while (s->array[j])
	{
		while (s->array[j][i])
		{
			if (i > lenght)
				lenght = i;
			i++;
		}
		i = 0;
		j++;
	}
	s->mv.longest_line = lenght + 1;
}

char	*mapdup(t_all *s, char *src)
{
	char	*dest;
	size_t	i;

	i = 0;
	if (!(dest = malloc((s->mv.longest_line + 2) * sizeof(char))))
		ft_exit("can't malloc in mapdup", s);
	dest[i] = ' ';
	while (src[i])
	{
		dest[i + 1] = src[i];
		i++;
	}
	while (++i < (s->mv.longest_line + 2))
		dest[i] = ' ';
	dest[i] = '\0';
	return (dest);
}

void	map_copy(t_all *s)
{
	char **line;
	int j = 0;
	int i = s->map.lines;

	longer_str(s);
	if(!(line = (char **)malloc(sizeof(char*) * (i + 2))))
		ft_exit("can't malloc in map_copy", s);
	line[0] = mapdup(s, "");
	line[i] = mapdup(s, "");
	line[i + 1] = NULL;
	while (i--)
	{
		line[j + 1] = mapdup(s, s->array[j]);
		j++;
	}
	s->arrrecuv = line;
}

void	check_around(t_all *s, int y, int x)
{
	char **str;

	str = s->arrrecuv;
	if (str[y - 1][x] == ' ')
		ft_exit("bad border in map", s);
	if (str[y + 1][x] == ' ')
		ft_exit("bad border in map", s);
	if (str[y][x - 1] == ' ')
		ft_exit("bad border in map", s);
	if (str[y][x + 1] == ' ')
		ft_exit("bad border in map", s);
	if (str[y + 1][x + 1] == ' ')
	{
		printf("checked char = %c\n", str[y][x]);
		ft_putendl("ERROR : bad border in corner");
	}
	if (str[y - 1][x - 1] == ' ')
		ft_putendl("ERROR : bad border in corner");
	if (str[y - 1][x + 1] == ' ')
		ft_putendl("ERROR : bad border in corner");
	if (str[y + 1][x - 1] == ' ')
		ft_putendl("ERROR : bad border in corner");
}

void	map_check_around(t_all *s)
{
	char **map;

	map_copy(s);
	map = s->arrrecuv;
	int x;
	int y = 0;
	char symbols[7] = { '0', 'S', 'N', 'W', 'E', '2' , '\0'};
	
	while (map[y])
	{
		x = 0;
		while(map[y][x])
		{
			if (ft_strchr(symbols, map[y][x]))
				check_around(s, y, x);
			else if ( map[y][x] != '1' && map[y][x] != ' ')
				ft_exit("bad char in map", s);
			x++;
		}
		y++;
	}
}
