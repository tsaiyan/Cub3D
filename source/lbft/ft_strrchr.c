/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaiyan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:31:00 by tsaiyan           #+#    #+#             */
/*   Updated: 2020/10/30 11:31:03 by tsaiyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int symbol)
{
	size_t i;

	i = ft_strlen(str);
	if (!symbol)
		return ((char*)(str + i));
	while (i--)
		if (str[i] == symbol)
			return ((char*)(str + i));
	return (NULL);
}
