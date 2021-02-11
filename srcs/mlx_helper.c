/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 03:02:11 by edebi             #+#    #+#             */
/*   Updated: 2021/02/08 03:04:17 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_sprite_as_img(int texture, void *img)
{
	g_params->textures[texture]->img = img;
	g_params->textures[texture]->addr = mlx_get_data_addr(
	g_params->textures[texture]->img,
	&g_params->textures[texture]->bits_per_pixel,
	&g_params->textures[texture]->line_length,
	&g_params->textures[texture]->endian);
}

void	*if_img_loaded(void *mlx_ptr, const char *str, int *width, int *height)
{
	void *ptr;

	if (str == NULL)
		exit_with_error(10, "Error\nTexture file name\n");
	if ((ptr = mlx_xpm_file_to_image(mlx_ptr, realpath(str, NULL),
width, height)) == NULL)
		exit_with_error(10, "Error\nTexture not found\n");
	return (ptr);
}

int		add_sprite(char **str, void *mlx_ptr)
{
	if (str[0][0] == 'N' && str[0][1] == 'O')
		load_sprite_as_img(0, if_img_loaded(mlx_ptr, str[1],
&g_params->texture_dims[0][0], &g_params->texture_dims[0][1]));
	else if (str[0][0] == 'S' && str[0][1] == 'O')
		load_sprite_as_img(2, if_img_loaded(mlx_ptr, str[1],
&g_params->texture_dims[2][0], &g_params->texture_dims[2][1]));
	else if (str[0][0] == 'W' && str[0][1] == 'E')
		load_sprite_as_img(1, if_img_loaded(mlx_ptr, str[1],
&g_params->texture_dims[1][0], &g_params->texture_dims[1][1]));
	else if (str[0][0] == 'E' && str[0][1] == 'A')
		load_sprite_as_img(3, if_img_loaded(mlx_ptr, str[1],
	&g_params->texture_dims[3][0], &g_params->texture_dims[3][1]));
	else if (str[0][0] == 'S')
		load_sprite_as_img(4, if_img_loaded(mlx_ptr, str[1],
	&g_params->texture_dims[4][0], &g_params->texture_dims[4][1]));
	else
		return (0);
	return (1);
}

void	print_line(int x, int line_length, int texture, int texture_column)
{
	int		height_offset;
	double	row_step;
	double	cur_row;
	int		color;
	int		i;

	row_step = (double)g_params->texture_dims[texture][1] / line_length;
	i = 0;
	set_params(&height_offset, &cur_row, &line_length, row_step);
	while (i < line_length)
	{
		color = get_color(g_params->textures[texture], texture_column,
		(int)cur_row);
		if (texture == 4 && ((color & 0x00FFFFFF) == 0))
		{
			i++;
			cur_row += row_step;
			continue;
		}
		my_mlx_pixel_put(g_params->frame->img, x, i + height_offset, color);
		i++;
		cur_row += row_step;
	}
	return ;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
