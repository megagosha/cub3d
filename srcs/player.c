/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 03:14:14 by edebi             #+#    #+#             */
/*   Updated: 2021/02/09 14:42:56 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		find_player_pos(char **map, int *result)
{
	int i;
	int j;

	i = 0;
	while (i < g_params->max_row)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (ft_strchr("NWES", map[i][j]) != NULL)
			{
				result[0] = i;
				result[1] = j;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int		check_valid_map(char **map, int y, int x)
{
	if (y > g_params->max_row || y < 0)
		exit_with_error(-3, "Map error\n");
	if (x < 0 || map[y][x] == '\0')
		exit_with_error(-3, "Map error\n");
	if (map[y][x] != '1' && map[y][x] != '3')
		map[y][x] = '3';
	if (map[y][x + 1] != '1' && map[y][x + 1] != '3')
		(check_valid_map(map, y, x + 1));
	if (map[y][x - 1] != '1' && map[y][x - 1] != '3')
		(check_valid_map(map, y, x - 1));
	if (map[y + 1][x + 1] != '1' && map[y + 1][x + 1] != '3')
		(check_valid_map(map, y + 1, x + 1));
	if (map[y - 1][x - 1] != '1' && map[y - 1][x - 1] != '3')
		(check_valid_map(map, y - 1, x - 1));
	if (map[y - 1][x + 1] != '1' && map[y - 1][x + 1] != '3')
		(check_valid_map(map, y - 1, x + 1));
	if (map[y - 1][x] != '1' && map[y - 1][x] != '3')
		(check_valid_map(map, y - 1, x));
	if (map[y + 1][x] != '1' && map[y + 1][x] != '3')
		(check_valid_map(map, y + 1, x));
	if (map[y + 1][x - 1] != '1' && map[y + 1][x - 1] != '3')
		(check_valid_map(map, y + 1, x - 1));
	return (1);
}

void	update_if_empty(t_pos *player, double x_update, double y_update)
{
	char	c;

	c = g_params->map[(int)(player->y_p + y_update)]
			[(int)(player->x_p + x_update)];
	if (c != '1' && c != '2')
	{
		player->x_p += x_update;
		player->y_p += y_update;
		return ;
	}
	else
	{
		c = g_params->map[(int)(player->y_p + y_update)][(int)(player->x_p)];
		if (c != '1' && c != '2')
		{
			player->y_p += y_update;
			return ;
		}
		c = g_params->map[(int)(player->y_p)][(int)(player->x_p + x_update)];
		if (c != '1' && c != '2')
			player->x_p += x_update;
	}
	return ;
}

void	update_player_pos(t_pos *player, double step, int lr_fb)
{
	double	angle;
	double	x_update;
	double	y_update;
	double	rad_angle;

	angle = player->deg_p;
	if (step < 0 && lr_fb == 1)
	{
		angle = normalize_angle(angle + 180);
		step = -step;
	}
	else if (step < 0 && lr_fb == 0)
	{
		angle = normalize_angle(angle + 90);
		step = -step;
	}
	else if (lr_fb == 0 && step > 0)
		angle = normalize_angle(angle - 90);
	rad_angle = to_radians(angle);
	x_update = step * cos(rad_angle);
	y_update = -step * sin(rad_angle);
	update_if_empty(player, x_update, y_update);
	return ;
}
