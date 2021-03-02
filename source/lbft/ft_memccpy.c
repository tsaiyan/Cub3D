/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaiyan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:28:59 by tsaiyan           #+#    #+#             */
/*   Updated: 2020/10/31 16:29:01 by tsaiyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, void *src, int c, size_t n)
{
	unsigned char	*p_dest;
	unsigned char	*p_src;

	p_dest = (unsigned char*)dst;
	p_src = (unsigned char*)src;
	if (!p_dest && !p_src)
		return (NULL);
	while (n--)
	{
		*p_dest = *p_src;
		if (*p_src == (unsigned char)c)
			return ((void *)++p_dest);
		p_dest++;
		p_src++;
	}
	return (NULL);
}
