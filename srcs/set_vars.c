/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 03:29:26 by edebi             #+#    #+#             */
/*   Updated: 2021/02/09 15:48:45 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_texture(int step, int direction, const double *params)
{
	t_textures	*texture;

	if (step < 0 || step > g_params->resolution_x)
		return ;
	texture = &(g_params->frame->fov->trace_result[step]);
	texture->texture = direction;
	texture->t_position = params[0] - (int)params[0];
	texture->t_distance = params[1];
	texture->t_s_distance = params[2];
	return ;
}

t_calc	set_vars_in_tace_ray(t_calc vars)
{
	vars.distance_h = -1;
	vars.distance_v = -1;
	g_params->frame->fov->trace_result->angle = vars.rad_ray_angle;
	vars.x = (int)vars.x_0;
	vars.y = (int)vars.y_0;
	vars.dx = vars.x_0 - vars.x;
	vars.dy = vars.y_0 - vars.y;
	return (vars);
}

t_calc	set_vars_angle(t_calc vars)
{
	if (vars.ray_angle > 0 && vars.ray_angle <= 90)
		return (first_angle(vars));
	else if (vars.ray_angle > 90 && vars.ray_angle <= 180)
		return (second_angle(vars));
	else if (vars.ray_angle > 180 && vars.ray_angle <= 270)
		return (third_angle(vars));
	else
		return (fourth_angle(vars));
}

void	set_vars(t_calc *vars)
{
	vars->x = 0;
	vars->y = 0;
	vars->dx = 0;
	vars->dy = 0;
	vars->xstep = 0;
	vars->ystep = 0;
	vars->xh = 0;
	vars->yv = 0;
	vars->dirx = 0;
	vars->diry = 0;
	vars->distance_h = -1;
	vars->distance_v = -1;
}

void	calc_texture(t_calc vars, int step)
{
	if (vars.distance_v <= 0)
		return (result_one(vars, step));
	else if (vars.distance_h <= 0)
		return (result_two(vars, step));
	if (vars.distance_v < vars.distance_h)
		return (result_three(vars, step));
	else
		return (result_four(vars, step));
}
