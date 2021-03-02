/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaiyan <tsaiyan@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 20:09:10 by tsaiyan           #+#    #+#             */
/*   Updated: 2020/11/26 20:09:13 by tsaiyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1
# include <unistd.h>
# include <stdlib.h>

int					get_next_line(int fd, char **line);
char				*ft_gstrjoin(char *s1, char *s2);
int					freeturn(char **str, int flag);
void				ft_free_plus_dup(char **buffer);
size_t				ft_gstrlen(char *str);
char				*ft_gstrdup(char *src);
void				*ft_gcalloc(size_t number, size_t size);
#endif
