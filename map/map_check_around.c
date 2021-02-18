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
	while (++i < (s->mv.longest_line + 1))
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

void	check_around(t_all *s, int x, int y)
{
	char **str;
	int i = 0;
	int j = 0;
	str = s->arrrecuv;
	if (str[i - 1][ j] == ' ')
		ft_exit("bad border in map", s);
	if (str[i - 1][ j] == ' ')
		ft_exit("bad border in map", s);
	if (str[i][ j - 1] == ' ')
		ft_exit("bad border in map", s);
	if (str[i][j + 1] == ' ')
		ft_exit("bad border in map", s);
	if (str[i + 1][j + 1] == ' ')
		ft_putendl("ERROR : bad border in corner");
	if (str[i - 1][j - 1] == ' ')
		ft_putendl("ERROR : bad border in corner");
	if (str[i - 1][j + 1] == ' ')
		ft_putendl("ERROR : bad border in corner");
	if (str[i + 1][j - 1] == ' ')
		ft_putendl("ERROR : bad border in corner");
}

void	map_check_around(t_all *s)
{
	char **map = s->arrrecuv;
	map_copy(s);
	int x = 0;
	int y = 0;
	char symbols[6] = { '0', 'S', 'N', 'W', 'E', '2'};;
	
	while (map[y][x])
	{
		while(map[y][x])
		{
			if (ft_strchr(symbols, map[y][x]))
				check_around(s, y, x);
			else if ( map[y][x] != '1' && map[y][x] != ' ')
				ft_exit("bad char in map", s);
			x++;
		}
		x = 0;
		y++;
	}
}
