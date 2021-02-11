/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 03:10:08 by edebi             #+#    #+#             */
/*   Updated: 2021/02/08 03:19:41 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_time(void)
{
	return (clock() / (double)CLOCKS_PER_SEC);
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

double	to_radians(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

double	normalize_angle(double x)
{
	x = fmod(x, 360);
	while (x < 0)
		x += 360;
	return (x);
}

int		sign(double x)
{
	return (x > 0) - (x < 0);
}
