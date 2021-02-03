/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaiyan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:25:58 by tsaiyan           #+#    #+#             */
/*   Updated: 2020/11/05 18:26:01 by tsaiyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char *str, char (*f)(unsigned int, char))
{
	char			*mall;
	unsigned int	i;

	if (!str || !f || (!(mall = malloc(sizeof(char) * ft_strlen(str) +
			1))))
		return (NULL);
	i = 0;
	while (str[i])
	{
		mall[i] = (*f)(i, str[i]);
		i++;
	}
	mall[i] = '\0';
	return (mall);
}
