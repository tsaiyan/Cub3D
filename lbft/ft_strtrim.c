/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaiyan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:32:14 by tsaiyan           #+#    #+#             */
/*   Updated: 2020/11/02 13:32:16 by tsaiyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *src, char *set)
{
	size_t	i;

	if (!set || !src)
		return (0);
	while (ft_strchr(set, *src) && *src)
		src++;
	i = ft_strlen(src);
	while (i && ft_strchr(set, src[i]))
		i--;
	return (ft_substr((char*)src, 0, i + 1));
}
