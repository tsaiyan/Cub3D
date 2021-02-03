/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaiyan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:19:57 by tsaiyan           #+#    #+#             */
/*   Updated: 2020/11/03 20:19:59 by tsaiyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_free(char **mall)
{
	while (*mall)
	{
		free(*mall);
		mall++;
	}
	return (0);
}

static size_t	atoi_strlen(char *str, char c)
{
	size_t len;

	len = 0;
	if (!str)
		return (0);
	while (*str == c)
		str++;
	while (*str != c && *str++)
		len++;
	return (len);
}

static size_t	wc(char *str, char c)
{
	size_t count;

	count = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == c)
			str++;
		if (*str != c)
		{
			count++;
			while (*str != c && *str)
				str++;
		}
	}
	return (count);
}

char			**ft_split(char *src, char c)
{
	char	**mall;
	size_t	i;

	i = 0;
	if (!src || !(mall = (char**)malloc(sizeof(char*) * (wc(src, c) + 1))))
		return (NULL);
	while (*src)
	{
		if (*src != c && *src != '\0')
		{
			if (!(mall[i++] = ft_substr((char*)src, 0, atoi_strlen(src, c))))
				return (ft_free(mall));
			src += atoi_strlen(src, c) - 1;
		}
		src++;
	}
	mall[i] = NULL;
	return (mall);
}
