/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 03:11:11 by edebi             #+#    #+#             */
/*   Updated: 2021/02/09 18:48:41 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_header(char *header)
{
	unsigned int k;

	k = 40;
	ft_memcpy((header + 14), &k, 4);
	k = g_params->resolution_x;
	ft_memcpy((header + 18), &k, 4);
	k = g_params->resolution_y;
	ft_memcpy((header + 22), &k, 4);
	k = 1;
	ft_memcpy((header + 26), &k, 2);
	k = 32;
	ft_memcpy((header + 28), &k, 2);
	k = 5000;
	ft_memcpy((header + 38), &k, 4);
	ft_memcpy((header + 42), &k, 4);
}

void	set_file_header(char *header)
{
	unsigned int	size;
	int				i;

	i = 53;
	size = 54 + g_params->frame->img->line_length * g_params->resolution_y;
	while (i >= 0)
	{
		header[i] = 0;
		i--;
	}
	header[0] = 'B';
	header[1] = 'M';
	ft_memcpy((header + 2), &size, sizeof(unsigned int));
	size = 54;
	ft_memcpy((header + 10), &size, sizeof(int));
}

void	write_data(int fd)
{
	int				i;
	int				j;
	unsigned int	color;

	i = g_params->resolution_y - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < g_params->resolution_x)
		{
			color = get_color(g_params->frame->img, j, i);
			if (write(fd, &color, 4) < 0)
				exit_with_error(-5, "Error\nSaving file\n");
			j++;
		}
		i--;
	}
	return ;
}

void	save_image(void)
{
	int					fd;
	char				header[54];

	fd = open("file_name.bmp", O_RDWR);
	if (fd < 0)
		exit_with_error(-5, "Error\nunable to open file\n");
	set_file_header(header);
	set_header(header);
	write(fd, &header, 54);
	write_data(fd);
	close(fd);
	exit(0);
}
