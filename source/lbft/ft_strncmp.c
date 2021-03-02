/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaiyan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 19:39:48 by tsaiyan           #+#    #+#             */
/*   Updated: 2020/09/20 19:39:52 by tsaiyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t			i;
	unsigned char	*uc_s1;
	unsigned char	*uc_s2;

	uc_s1 = (unsigned char*)s1;
	uc_s2 = (unsigned char*)s2;
	i = 0;
	while ((uc_s1[i] || (uc_s2[i])) && (i < n))
	{
		if (uc_s1[i] != uc_s2[i])
			return (uc_s1[i] - uc_s2[i]);
		i++;
	}
	return (0);
}
