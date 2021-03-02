/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaiyan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:50:12 by tsaiyan           #+#    #+#             */
/*   Updated: 2020/11/04 15:50:13 by tsaiyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count(long n)
{
	int i;

	i = 0;
	if (n == 0)
		return (0);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static char		*return_null(void)
{
	char	*result;

	if (!(result = malloc(2)))
		return (NULL);
	result[0] = 48;
	result[1] = '\0';
	return (result);
}

char			*ft_itoa(int number)
{
	char	*result;
	int		n;
	long	lumber;

	lumber = number;
	n = ft_count(lumber);
	if (number == 0)
		return (return_null());
	if (!(result = (char*)malloc(n + 1)))
		return (NULL);
	if (lumber < 0)
	{
		result[0] = '-';
		lumber *= -1;
	}
	result[n] = '\0';
	while (n-- && result[n] != '-')
	{
		result[n] = lumber % 10 + 48;
		lumber /= 10;
	}
	return (result);
}
