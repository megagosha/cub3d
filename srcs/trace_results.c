/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_results.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 03:22:08 by edebi             #+#    #+#             */
/*   Updated: 2021/02/08 03:45:05 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	result_one(t_calc vars, int step)
{
	double params[3];

	params[0] = vars.xh;
	params[1] = vars.distance_h;
	params[2] = sqrt_pw(vars.xh, vars.x_0, vars.y, vars.y_0);
	return (set_texture(step, get_tex_dir(vars.ray_angle, 0, 1), params));
}

void	result_two(t_calc vars, int step)
{
	double params[3];

	params[0] = vars.yv;
	params[1] = vars.distance_v;
	params[2] = sqrt_pw(vars.x, vars.x_0, vars.yv, vars.y_0);
	return (set_texture(step, get_tex_dir(vars.ray_angle, 1, 0), params));
}

void	result_three(t_calc vars, int step)
{
	double params[3];

	params[0] = vars.yv;
	params[1] = vars.distance_v;
	params[2] = sqrt_pw(vars.x, vars.x_0, vars.yv, vars.y_0);
	return (set_texture(step, get_tex_dir(vars.ray_angle, 1, 0), params));
}

void	result_four(t_calc vars, int step)
{
	double params[3];

	params[0] = vars.xh;
	params[1] = vars.distance_h;
	params[2] = sqrt_pw(vars.xh, vars.x_0, vars.y, vars.y_0);
	return (set_texture(step, get_tex_dir(vars.ray_angle, 0, 1), params));
}
