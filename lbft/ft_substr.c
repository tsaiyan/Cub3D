/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaiyan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:12:15 by tsaiyan           #+#    #+#             */
/*   Updated: 2020/11/01 19:12:17 by tsaiyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *src, unsigned int start, size_t len)
{
	char		*dest;
	size_t		i;

	i = -1;
	if (!src)
		return (NULL);
	if (!(dest = (char *)malloc(sizeof(*src) * (len + 1))))
		return (NULL);
	if ((start >= (unsigned)ft_strlen(src)) && !(dest[0] = 0))
		return (dest);
	while (src[++i + start] && len--)
		dest[i] = src[i + start];
	dest[i] = '\0';
	return (dest);
}
