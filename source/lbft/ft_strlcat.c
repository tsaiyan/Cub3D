/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaiyan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:57:25 by tsaiyan           #+#    #+#             */
/*   Updated: 2020/10/29 13:57:27 by tsaiyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t r;

	i = 0;
	j = ft_strlen(dest);
	r = ft_strlen(src);
	if (size <= j)
		return (r + size);
	r += j;
	while (((j + 1) < size) && (src[i]))
		dest[j++] = src[i++];
	dest[j] = '\0';
	return (r);
}
