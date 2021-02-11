/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   appender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 20:06:48 by edebi             #+#    #+#             */
/*   Updated: 2021/02/09 16:13:03 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			append_line(char *str)
{
	int		row;

	row = g_params->max_row;
	if (g_params->max_row % 64 == 0)
		alloc_map_rows();
	g_params->map[row] = str;
	g_params->map[row + 1] = NULL;
	g_params->max_row++;
	return (1);
}

void		add_ceilling(char **res)
{
	int i;

	i = 0;
	while (res[i] != NULL)
	{
		g_params->ceilling_color[i] = ft_atoi(res[i]);
		i++;
	}
	return ;
}

void		add_floor(char **res)
{
	int	i;

	i = 0;
	while (res[i] != NULL)
	{
		g_params->floor_color[i] = ft_atoi(res[i]);
		i++;
	}
	return ;
}

int			add_color(char **res, char c)
{
	int	i;

	i = 0;
	while (res[i] != NULL)
		i++;
	if (i != 3)
		return (0);
	else
	{
		i = 0;
		if (c == 'F')
			add_floor(res);
		else if (c == 'C')
			add_ceilling(res);
		else
			return (free_tab(res, 0));
		return (free_tab(res, 1));
	}
}

int			add_resolution(char *str, void *mlx_ptr)
{
	char	**res_tab;
	int		i;

	i = 0;
	res_tab = ft_split(str, ' ');
	free(str - 2);
	if (res_tab == NULL)
		return (0);
	while (res_tab[i] != NULL)
		i++;
	if (i != 2)
		return (free_tab(res_tab, 0));
	g_params->resolution_x = ft_atoi(res_tab[0]);
	g_params->resolution_y = ft_atoi(res_tab[1]);
	free_tab(res_tab, 0);
	if (g_params->resolution_x <= 50 || g_params->resolution_y <= 50)
		exit_with_error(-4, "Error\nresolutuion too low\n");
	check_resolution(mlx_ptr);
	return (1);
}
