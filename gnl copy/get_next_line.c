/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaiyan <tsaiyan@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 20:08:48 by tsaiyan           #+#    #+#             */
/*   Updated: 2020/11/26 20:08:57 by tsaiyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t		ft_sn_finder(char *str)
{
	while (*str)
		if (*str++ == '\n')
			return (0);
	return (1);
}

char				*ft_gstrjoin(char *s1, char *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;

	if (!s2)
		return (0);
	i = ft_gstrlen(s1);
	j = ft_gstrlen(s2);
	if (!(dest = malloc(((i + j + 1)))))
		return (0);
	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
		{
			dest[i] = s1[i];
			i++;
		}
		free(s1);
	}
	while (s2[j] && s2[j] != '\n')
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}

char				*ft_gstrdup(char *src)
{
	char	*dest;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!(dest = malloc((ft_gstrlen(src) + 1) * sizeof(char))))
		return (0);
	while (src[i] != '\n' && src[i])
		i++;
	if (src[i] == '\n')
		i++;
	while (src[i])
		dest[j++] = src[i++];
	dest[j] = '\0';
	return (dest);
}

static char			*ft_move_buffer(char *src)
{
	char *reverse_buffer;
	char *start;
	char *dom;

	if (!src)
		return (NULL);
	dom = src;
	if (!(ft_sn_finder(src)))
	{
		while (*src != '\n' && *src)
			src++;
		src++;
	}
	else
		return (src);
	if (!(reverse_buffer = ft_gcalloc(BUFFER_SIZE + 1, sizeof(char))))
		return (0);
	start = reverse_buffer;
	while (*src)
		*reverse_buffer++ = *src++;
	*reverse_buffer = '\0';
	return (start);
}

int					get_next_line(int fd, char **line)
{
	int				readedbytes;
	static char		*buffer[1024];
	char			*dom;

	if (!line || fd < 0 || BUFFER_SIZE < 1 || !(*line = ft_gstrdup("\0")))
		return (-1);
	if (!buffer[fd])
		if (!(buffer[fd] = ft_gcalloc(sizeof(char), (BUFFER_SIZE + 1))))
			return (-1);
	*line = ft_gstrjoin(*line, buffer[fd]);
	if (!(dom = buffer[fd]) || !(ft_sn_finder(buffer[fd])))
		return ((buffer[fd] = ft_move_buffer(buffer[fd])) && freeturn(&dom, 1));
	readedbytes = 1;
	while (ft_sn_finder(buffer[fd]) && (readedbytes != 0))
	{
		if ((readedbytes = read(fd, buffer[fd], BUFFER_SIZE)) < 0)
			return (freeturn(&buffer[fd], -1));
		buffer[fd][readedbytes] = '\0';
		*line = ft_gstrjoin(*line, buffer[fd]);
	}
	ft_free_plus_dup(&buffer[fd]);
	if (!readedbytes)
		return (freeturn(&buffer[fd], 0));
	return (1);
}
