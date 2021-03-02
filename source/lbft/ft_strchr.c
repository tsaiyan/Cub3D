/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaiyan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:50:04 by tsaiyan           #+#    #+#             */
/*   Updated: 2020/10/29 20:50:05 by tsaiyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *str, int symbol)
{
	int i;

	i = 0;
	while ((str[i] != symbol) && (str[i]))
		i++;
	if (str[i] == symbol)
		return ((char*)&str[i]);
	else
		return (0);
}
