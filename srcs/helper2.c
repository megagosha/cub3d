/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 03:25:12 by edebi             #+#    #+#             */
/*   Updated: 2021/02/08 03:36:15 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	sqrt_pw(double one, double two, double three, double four)
{
	return (sqrt(pow((int)one - two, 2) + pow(three - four, 2)));
}

int		get_offset(int line_length)
{
	if (line_length >= g_params->resolution_y)
		return (0);
	return ((g_params->resolution_y - line_length) / 2);
}

int		get_tex_dir(double angle, int vertical, int horizontal)
{
	if (angle >= 0 && angle < 90 && vertical == 1)
		return (3);
	if (angle >= 90 && angle < 180 && vertical == 1)
		return (1);
	if (angle >= 0 && angle < 90 && horizontal == 1)
		return (0);
	if (angle >= 90 && angle < 180 && horizontal == 1)
		return (0);
	if (angle >= 180 && angle < 270 && vertical == 1)
		return (1);
	if (angle >= 270 && angle < 360 && vertical == 1)
		return (3);
	if (angle >= 180 && angle < 270 && horizontal == 1)
		return (2);
	if (angle >= 270 && angle < 360 && horizontal == 1)
		return (2);
	return (0);
}

int		loop_spr_border(t_spr *sprite, int step)
{
	if (step < 0 && step < sprite->s_column)
		sprite->s_column = step;
	else if (step >= g_params->resolution_x && step >= sprite->end_column)
		sprite->end_column = step;
	return (-1);
}

int		exit_with_error(int error, char *str)
{
	if (str != NULL)
		ft_putstr(str);
	exit(error);
	return (error);
}
