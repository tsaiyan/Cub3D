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

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	void	*p_dest;

	if (!dst && !src)
		return (NULL);
	p_dest = dst;
	while (n--)
		*(unsigned char*)dst++ = *(unsigned char*)src++;
	return (p_dest);
}
