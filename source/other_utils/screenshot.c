/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaiyan <tsaiyan@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 18:29:13 by tsaiyan           #+#    #+#             */
/*   Updated: 2021/01/28 18:29:15 by tsaiyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
**	BMP
** Bit Map file header - 14 bytes
**
** 2 [0-1] 2 bytes  -> in FileType
** 6 [2-5] 4 bytes  -> unsigned integer in File size
** 10 [6 -9] 4 bytes -> 	 RESERVED!!!
** 11 [10]   1 bytes -> FILE_HEADER_SIZE(14) + INFO_HEADER_SIZE(40)
*/

/*
**	BMP
**	Bit Map INFO_HEADER_SIZE - 40-bytes
**
**	12 [11 - 14] 4 bytes -> size of the header in bytes(40)
**	16 [15 - 18] 4 bytes ->	the width of the final image in pixels
**	20 [19 - 22] 4 bytes ->	the height of the final image in pixels
**	24 [23 - 24] 2 bytes -> plane the number of color planes
**		of the target device. Should be '1' in decimal.
** 	26 [25 - 26] 2 bytes  -> BitsPerPixel
** 	28 [27 - 30] 4 bytes ->	Compression
** 	32 [31 - 34] 4 bytes -> ImageSize
** 	36 [35 - 38] 4 bytes -> XpixelsPerMeter
** 	40 [39 - 42] 4 bytes -> YpixelsPerMeter
** 	44 [43 - 46] 4 bytes -> TotalColors
** 	48 [47 - 50] 4 bytes -> ImportantColors
*/

void	bit_move(int n, unsigned char *str)
{
	str[0] = n;
	str[1] = n >> 8;
	str[2] = n >> 16;
	str[3] = n >> 24;
}

void	create_header(int fd, t_all *s)
{
	unsigned char	header[54];
	int				size_file;

	size_file = 54 + 4 * (s->win.h + s->win.w);
	ft_bzero(header, 54);
	header[0] = 'B';
	header[1] = 'M';
	bit_move(size_file, header + 2);
	header[10] = 54;
	header[14] = 40;
	bit_move(s->win.w, header + 18);
	bit_move(s->win.h, header + 22);
	header[26] = 1;
	header[28] = 24;
	write(fd, header, 54);
}

void	write_pixels(t_all *s, int fd)
{
	int color;
	int j;
	int i;

	i = s->win.h - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < s->win.w)
		{
			color = *(int*)(s->win.addr + \
							(i * s->win.line_l + j * (s->win.bpp / 8)));
			write(fd, &color, 3);
			j++;
		}
		i--;
	}
}

void	screenshot(t_all *s)
{
	int fd;

	if (!(fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0666)))
		ft_exit("can't create a file for screenshot", s);
	while(s->win.w % 4 != 0)
		s->win.w--;
	lodev(s);
	create_header(fd, s);
	write_pixels(s, fd);
	close(fd);
	exit(0);
}
