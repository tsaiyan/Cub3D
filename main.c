//
//  main.c
//  cub3d
//
//  Created by Torres Saiyan on 1/20/21.
//  Copyright © 2021 21school. All rights reserved.
//

#include "parcer_map.h"
#define FOOT 0.3
char	**make_map(t_list **head, int size)
{
	char **map = ft_calloc(size + 1, sizeof(char *));
	int i = -1;
	t_list *tmp = *head;

	while(tmp)
	{
		map[++i] = tmp->content;
		tmp = tmp->next;
	}
	i = 0;
	return (map);
}

int key_press(int key, t_struct *map)
{
	printf("\npress\n");
	mlx_clear_window(map->mlx, map->win);
	map->y = 0;
	map->x = 0;
	if (key == 13)
		map->py -= FOOT;
	if (key == 1)
		map->py += FOOT;
	if (key == 0)
		map->px -= FOOT;
	if (key == 2)
		map->px += FOOT;
	if (key == 53)
		exit(0);
	visual_map(map);
	return(0);
}

int main(int argc, char **argv)
{
	t_struct *map;
	int fd = open(argv[1], O_RDONLY);
	char *line = NULL;
	t_list *head = NULL;

	if (!(map = malloc(sizeof(t_struct))))
		return (-1);
	while(get_next_line(fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	map->array = make_map(&head, ft_lstsize(head));
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, 640, 480, "window");
	map->y = 0;
	map->py = 0;
	map->px = 0;
	map->x = 0;
	visual_map(map);
	mlx_hook(map->win, 2, (1L << 0), &key_press, map);
	mlx_loop(map->mlx);
	return 0;
}
