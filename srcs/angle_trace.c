/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_trace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 03:20:30 by edebi             #+#    #+#             */
/*   Updated: 2021/02/08 03:46:47 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_calc	first_angle(t_calc vars)
{
	vars.xstep = 1 / tan(vars.rad_ray_angle);
	vars.ystep = -tan(vars.rad_ray_angle);
	vars.yv = vars.y + vars.dy - (C_S - vars.dx) * tan(vars.rad_ray_angle);
	vars.xh = vars.x + vars.dx + vars.dy / tan(vars.rad_ray_angle);
	vars.dirx = 1;
	vars.diry = -1;
	vars.x += vars.dirx;
	vars.y += vars.diry;
	return (vars);
}

t_calc	second_angle(t_calc vars)
{
	vars.xstep = 1 / tan(vars.rad_ray_angle);
	vars.ystep = tan(vars.rad_ray_angle);
	vars.yv = vars.y + vars.dy + vars.dx * tan(vars.rad_ray_angle);
	vars.xh = vars.x + vars.dx + vars.dy / tan(vars.rad_ray_angle);
	vars.dirx = -1;
	vars.diry = -1;
	vars.x += vars.dirx;
	vars.y += vars.diry;
	return (vars);
}

t_calc	third_angle(t_calc vars)
{
	vars.xstep = -1 / tan(vars.rad_ray_angle);
	vars.ystep = tan(vars.rad_ray_angle);
	vars.yv = vars.y + vars.dy + vars.dx * tan(vars.rad_ray_angle);
	vars.xh = vars.x + vars.dx - (C_S - vars.dy) / tan(vars.rad_ray_angle);
	vars.dirx = -1;
	vars.diry = 1;
	vars.x += vars.dirx;
	vars.y += vars.diry;
	return (vars);
}

t_calc	fourth_angle(t_calc vars)
{
	vars.xstep = -1 / tan(vars.rad_ray_angle);
	vars.ystep = -tan(vars.rad_ray_angle);
	vars.yv = vars.y + vars.dy - (C_S - vars.dx) * tan(vars.rad_ray_angle);
	vars.xh = vars.x + vars.dx - (1 - vars.dy) / tan(vars.rad_ray_angle);
	vars.dirx = 1;
	vars.diry = 1;
	vars.x += vars.dirx;
	vars.y += vars.diry;
	return (vars);
}
