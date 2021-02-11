/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 20:02:38 by edebi             #+#    #+#             */
/*   Updated: 2021/02/09 16:11:12 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_name(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i < 5)
		exit_with_error(6, "File name is not correct\n");
	if (ft_strncmp(str + i - 4, ".cub", 4))
		exit_with_error(6, "File format is not supported\n");
	return (1);
}

int		line_is_map(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_strrchr(" 012NSEW", str[i]))
	{
		if (str[i] == '2')
			g_params->num_sprites++;
		if (ft_strrchr("NSEW", str[i]))
		{
			g_params->heading = str[i];
			g_params->x_position = i;
			g_params->y_position = g_params->max_row;
		}
		i++;
	}
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}

int		line_is_param(char *str, void *mlx_ptr)
{
	char	**res;
	char	c;

	if (str[0] == 'F' || str[0] == 'C')
	{
		res = ft_split(str, ' ');
		c = str[0];
		free(str);
		return (add_color(ft_split(res[1], ','), c));
	}
	else if (ft_strrchr("NSWE", str[0]))
		return (add_sprite(ft_split(str, ' '), mlx_ptr));
	else if (str[0] == 'R')
		return (add_resolution(str + 2, mlx_ptr));
	return (0);
}

void	check_params(void)
{
	int	i;

	if (g_params->resolution_x == 0 || g_params->resolution_y == 0)
		exit_with_error(9, "Error\nResolution is not set");
	if (g_params->floor_color[0] == -1)
		exit_with_error(9, "Error\nFloor color is not set");
	if (g_params->ceilling_color[0] == -1)
		exit_with_error(9, "Error\nCeiling color is not set");
	i = 0;
	while (i < 5)
	{
		if (g_params->texture_dims[i][0] == 0 ||
		g_params->texture_dims[i][1] == 0)
			exit_with_error(9, "Error\nTexture is not loaded");
		i++;
	}
}
