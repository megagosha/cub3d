/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 03:04:57 by edebi             #+#    #+#             */
/*   Updated: 2021/02/09 18:51:16 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_line_height(double distance)
{
	double	result;

	result = g_params->resolution_y / distance;
	return (result);
}

void	print_sprites(t_fov *fov, int i)
{
	int		end_column;
	int		k;
	double	s_step;
	double	s_column;

	while (i >= 0)
	{
		k = fov->sprites[i].s_column < 0 ? 0 : fov->sprites[i].s_column;
		end_column = fov->sprites[i].end_column > fov->size ? fov->size :
		fov->sprites[i].end_column;
		s_step = (double)g_params->texture_dims[4][0] /
		abs(fov->sprites[i].end_column - fov->sprites[i].s_column);
		s_column = fov->sprites[i].s_column < 0 ?
		s_step * abs(fov->sprites[i].s_column) : 0;
		while (k < end_column)
		{
			if (fov->sprites[i].distance < fov->trace_result[k].t_s_distance)
				print_line(k,
				get_line_height(fov->sprites[i].distance), 4, (int)s_column);
			s_column += s_step;
			k++;
		}
		i--;
	}
}

void	print_fov(t_fov *fov)
{
	int		i;
	double	texture_column;
	int		texture;

	i = 0;
	texture = fov->trace_result[i].texture;
	texture_column = fov->trace_result[i].t_position *
	g_params->texture_dims[texture][0];
	while (i <= g_params->resolution_x)
	{
		if (texture_column >= g_params->texture_dims[texture][0])
			texture_column = 0;
		print_line(i, get_line_height(fov->trace_result[i].t_distance),
		texture, (int)texture_column);
		texture = fov->trace_result[i].texture;
		texture_column = fov->trace_result[i].t_position *
		g_params->texture_dims[texture][0];
		i++;
	}
	print_sprites(fov, fov->found_sprites);
}

void	color_fill(t_frame *frame, int sky, int floor, t_data img)
{
	int	x;
	int	y;
	int	middle;
	int	color;

	x = 0;
	middle = frame->size_y / 2;
	while (x < frame->size_x)
	{
		y = 0;
		while (y < frame->size_y)
		{
			if (y > middle)
				color = sky;
			else
				color = floor;
			my_mlx_pixel_put(&img, x, y, color);
			y++;
		}
		x++;
	}
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}
