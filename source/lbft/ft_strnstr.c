/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaiyan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 13:35:43 by tsaiyan           #+#    #+#             */
/*   Updated: 2020/11/15 13:35:44 by tsaiyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	j;
	size_t	i;

	if (!*needle)
		return ((char *)haystack);
	j = 0;
	while (haystack[j] && j < len)
	{
		i = 0;
		while (haystack[j + i] == needle[i] && j + i < len)
		{
			i++;
			if (!needle[i])
				return ((char *)haystack + j);
		}
		j++;
	}
	return (NULL);
}
