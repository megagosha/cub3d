/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 20:02:38 by edebi             #+#    #+#             */
/*   Updated: 2021/02/09 16:11:12 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_map(char *line, int fd)
{
	int	i;

	i = 0;
	append_line(line);
	while (get_next_line(fd, &line) > 0)
	{
		if (line_is_map(line))
			append_line(line);
		else
			exit_with_error(9, "Error\nWrong symbols in map");
	}
}

int		line_is_empty(const char *line)
{
	if (line == NULL || line[0] == '\0' || line[0] == 0)
		return (1);
	return (0);
}

void	get_params(int fd, void *mlx_ptr)
{
	int		i;
	char	*line;

	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (line_is_empty(line))
			continue;
		if (line_is_param(line, mlx_ptr))
			continue;
		if (line_is_map(line))
		{
			check_params();
			parse_map(line, fd);
		}
		else
			exit_with_error(-2, "Error\nUnexpected symbols in map");
	}
	if (g_params->map == NULL)
		exit_with_error(-2, "Error\nMap error");
}

int		init_map(char *str, void *mlx_ptr)
{
	int		fd;

	if (!check_name(str))
		return (0);
	else
	{
		fd = open(str, O_RDONLY);
		if (fd < 0)
			exit_with_error(-2, "Unable to open map\n");
		g_params->max_row = 0;
		get_params(fd, mlx_ptr);
		close(fd);
	}
	return (1);
}

void	check_for_valid_map(char **map)
{
	int	*player_pos;
	int	i;

	player_pos = malloc(sizeof(int) * 2);
	if (player_pos == NULL)
		exit_with_error(-2, "Mem error\n");
	if (find_player_pos(map, player_pos))
	{
		check_valid_map(map, player_pos[0], player_pos[1]);
		i = 0;
		while (i < g_params->max_row)
			i++;
		calc_max_x();
	}
}
