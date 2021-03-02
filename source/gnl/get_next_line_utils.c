/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaiyan <tsaiyan@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 20:10:20 by tsaiyan           #+#    #+#             */
/*   Updated: 2020/11/26 20:10:23 by tsaiyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				freeturn(char **str, int flag)
{
	free(*str);
	*str = NULL;
	return (flag);
}

void			ft_free_plus_dup(char **buffer)
{
	char *dom;

	dom = *buffer;
	*buffer = ft_gstrdup(*buffer);
	free(dom);
}

size_t			ft_gstrlen(char *str)
{
	size_t i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void			*ft_gcalloc(size_t number, size_t size)
{
	char *str;
	char *start;

	if (!(str = malloc(number * size)))
		return (0);
	start = str;
	while (size--)
		*str++ = 0;
	return (start);
}
