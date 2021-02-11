/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 20:40:02 by edebi             #+#    #+#             */
/*   Updated: 2021/02/09 19:39:18 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_calc	loop_vertical(t_calc vars, char **map, int *v_success, int step)
{
	while (vars.x >= 0 &&
	(int)vars.yv < g_params->max_row &&
	(int)vars.yv >= 0 && g_params->max_x[(int)vars.yv] > vars.x)
	{
		if (map[(int)vars.yv][vars.x] != '0')
		{
			if (map[(int)vars.yv][vars.x] == '1')
			{
				if (vars.ray_angle < 270 && vars.ray_angle > 90)
					vars.x += 1;
				vars.distance_v = sqrt((vars.x - vars.x_0) * (vars.x -
				vars.x_0) + (vars.yv - vars.y_0) * (vars.yv - vars.y_0))
				* fabs(cos(vars.rad_ray_angle - vars.rad_player_angle));
				*v_success = 1;
				break ;
			}
			if (map[(int)vars.yv][vars.x] == '2')
				check_sprites(vars.x, (int)vars.yv, step, vars.ray_angle);
		}
		vars.x += vars.dirx;
		vars.yv += vars.ystep;
	}
	return (vars);
}

t_calc	loop_horizontal(t_calc vars, char **map, int *h_success, int step)
{
	while (vars.y < g_params->max_row && vars.y >= 0 &&
	(int)vars.xh >= 0 && g_params->max_x[vars.y] > (int)vars.xh)
	{
		if (map[vars.y][(int)vars.xh] != '0')
		{
			if (map[vars.y][(int)vars.xh] == '1')
			{
				if (vars.ray_angle > 0 && vars.ray_angle < 180)
					vars.y += 1;
				vars.distance_h = sqrt((vars.xh - vars.x_0) * (vars.xh -
				vars.x_0) + (vars.y - vars.y_0) * (vars.y - vars.y_0)) *
				fabs(cos(vars.rad_ray_angle - vars.rad_player_angle));
				*h_success = 1;
				break ;
			}
			if (map[vars.y][(int)vars.xh] == '2')
				check_sprites((int)vars.xh, vars.y, step, vars.ray_angle);
		}
		vars.y += vars.diry;
		vars.xh += vars.xstep;
	}
	return (vars);
}

void	trace_ray(char **map, t_calc vars, int step)
{
	int v_success;
	int h_success;

	vars = set_vars_in_tace_ray(vars);
	vars = set_vars_angle(vars);
	v_success = 0;
	h_success = 0;
	vars = loop_vertical(vars, map, &v_success, step);
	vars = loop_horizontal(vars, map, &h_success, step);
	calc_texture(vars, step);
	return ;
}

void	process_frame(double max_angle, double step_deg, char **map)
{
	int		i;
	t_fov	*fov;

	i = 0;
	fov = g_params->frame->fov;
	while (i <= fov->size)
	{
		fov->vars.ray_angle = max_angle;
		fov->vars.rad_ray_angle = to_radians(max_angle);
		set_vars(&fov->vars);
		trace_ray(map, fov->vars, i);
		max_angle = normalize_angle(max_angle - step_deg);
		i++;
	}
}

t_fov	*calculate_fov(t_params *map, t_fov *fov,
double x0, double y0)
{
	double	max_angle;
	double	min_angle;
	int		i;
	int		prev_column;
	int		step;

	prepare_data(&min_angle, &max_angle, x0, y0);
	process_frame(max_angle, g_params->frame->player->angle_step, map->map);
	cal_spr(fov->sprites, fov->vars.x_0, fov->vars.y_0, fov->found_sprites);
	step = 0;
	i = 1;
	sort_sprites(fov->sprites, fov->found_sprites, i);
	i = 0;
	while (i < fov->found_sprites)
	{
		process_l_sprites(max_angle, &step, i, &prev_column);
		process_r_sprites(min_angle, &step, i, &prev_column);
		i++;
	}
	return (fov);
}
