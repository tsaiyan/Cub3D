/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaiyan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:37:58 by tsaiyan           #+#    #+#             */
/*   Updated: 2020/10/31 14:38:00 by tsaiyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void *src, size_t len)
{
	unsigned char		*p_dest;
	unsigned char		*p_src;

	p_dest = (unsigned char*)dst;
	p_src = (unsigned char*)src;
	if (!p_dest && !p_src)
		return (0);
	if (p_src < p_dest)
		while (len--)
			p_dest[len] = p_src[len];
	else
		while (len--)
		{
			*p_dest = *p_src;
			p_dest++;
			p_src++;
		}
	return (dst);
}
