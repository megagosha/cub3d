/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 20:03:37 by edebi             #+#    #+#             */
/*   Updated: 2021/02/09 18:10:32 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		free_tab(char **tab, int nb)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (nb);
}

void	clean_g_params(void)
{
	int	i;

	i = 0;
	while (g_params->map[i] != NULL)
	{
		free(g_params->map[i]);
		i++;
	}
	free(g_params->map[i]);
	free(g_params->map);
	free(g_params);
}

void	init_textures(void)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		g_params->textures[i] = malloc(sizeof(t_data));
		if (g_params->textures[i] == NULL)
			exit_with_error(-2, "Error\nMem\n");
		g_params->texture_dims[i][0] = 0;
		g_params->texture_dims[i][1] = 0;
		i++;
	}
	g_params->floor_color[0] = -1;
	g_params->ceilling_color[0] = -1;
}

int		init_params(void *mlx)
{
	if ((g_params = malloc(sizeof(t_params))) == NULL)
		return (0);
	g_params->resolution_x = 0;
	g_params->resolution_y = 0;
	init_textures();
	g_params->num_sprites = 0;
	g_params->x_position = 0;
	g_params->y_position = 0;
	g_params->heading = 0;
	g_params->max_row = 0;
	g_params->map = NULL;
	g_params->start = 0;
	g_params->frame = malloc(sizeof(t_frame));
	if (g_params->frame == NULL)
		exit_with_error(-2, "Error\nMem\n");
	g_params->frame->vars = malloc(sizeof(t_vars));
	if (g_params->frame->vars == NULL)
		exit_with_error(-2, "Error\nMem\n");
	g_params->frame->vars->mlx = mlx;
	return (1);
}

int		alloc_map_rows(void)
{
	char	**buf;
	int		i;

	buf = malloc(sizeof(char *) * (g_params->max_row + 64) + 8);
	if (buf == NULL)
		return (-1);
	if (g_params->max_row != 0)
	{
		i = 0;
		while (g_params->map[i] != NULL)
		{
			buf[i] = g_params->map[i];
			i++;
		}
	}
	buf[g_params->max_row + 64] = NULL;
	free(g_params->map);
	g_params->map = buf;
	return (1);
}
