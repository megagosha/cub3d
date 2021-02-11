/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 16:06:34 by edebi             #+#    #+#             */
/*   Updated: 2021/02/09 16:05:20 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_params	*g_params;

char		**map_cpy(void)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * g_params->max_row);
	if (res == NULL)
		exit_with_error(-2, "Error\nmem\n");
	i = 0;
	while (i < g_params->max_row)
	{
		res[i] = ft_strdup(g_params->map[i]);
		i++;
	}
	return (res);
}

int			str_cmp(char *str, char *str1)
{
	int	len;
	int len2;
	int i;

	len = ft_strlen(str);
	len2 = ft_strlen(str1);
	if (len != len2)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != str1[i])
			return (0);
		i++;
	}
	return (1);
}

int			main(int argc, char **argv)
{
	void	*mlx;
	char	**map_cp;

	if ((mlx = mlx_init()) == NULL || init_params(mlx) == 0)
		exit_with_error(-2, "Error\nmem\n");
	if (argc < 2)
		exit_with_error(-2, "Error\nSpecify map file\n");
	if (init_map(argv[1], mlx) == 0)
		return (exit_with_error(-1, "Error\nmem\n"));
	if (argc == 3 && str_cmp(argv[2], "--save") == 1)
		g_params->start = -1;
	if (argc == 2 || g_params->start == -1)
	{
		map_cp = map_cpy();
		check_for_valid_map(map_cp);
		run();
		clean_g_params();
	}
	exit(0);
}
