/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 03:26:20 by edebi             #+#    #+#             */
/*   Updated: 2021/02/09 19:43:55 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_sprites(t_fov *fov)
{
	int	i;

	i = 0;
	while (i < g_params->num_sprites)
	{
		fov->sprites[i].sprite_x = -1;
		fov->sprites[i].sprite_y = -1;
		fov->sprites[i].s_column = -1;
		fov->sprites[i].end_column = 0;
		fov->sprites[i].distance = -1;
		fov->sprites[i].pos_counter = 0;
		fov->sprites[i].angle = 0;
		i++;
	}
	return ;
}

void	process_l_sprites(double max_angle, int *step, int i, int *prev_column)
{
	t_fov	*fov;
	double	step_deg;

	step_deg = g_params->frame->player->angle_step;
	fov = g_params->frame->fov;
	*step = 0;
	if (fov->sprites[i].s_column == 0)
	{
		*prev_column = 0;
		while (*prev_column != fov->sprites[i].pos_counter)
		{
			*prev_column = fov->sprites[i].pos_counter;
			max_angle = normalize_angle(max_angle + step_deg);
			(*step)--;
			fov->vars.ray_angle = max_angle;
			fov->vars.rad_ray_angle = to_radians(max_angle);
			trace_ray(g_params->map, fov->vars, *step);
		}
	}
}

void	process_r_sprites(double max_angle, int *step, int i, int *prev_column)
{
	t_fov	*fov;
	double	step_deg;

	step_deg = g_params->frame->player->angle_step;
	fov = g_params->frame->fov;
	if (fov->sprites[i].end_column == fov->size)
	{
		*step = fov->size;
		*prev_column = 0;
		while (*prev_column != fov->sprites[i].pos_counter)
		{
			*prev_column = fov->sprites[i].pos_counter;
			max_angle = normalize_angle(max_angle - step_deg);
			fov->vars.ray_angle = max_angle;
			fov->vars.rad_ray_angle = to_radians(max_angle);
			trace_ray(g_params->map, fov->vars, *step);
			(*step)++;
		}
	}
}

void	check_sprites(int x, int y, int step, double angle)
{
	int		ix;
	t_spr	*spr;

	spr = g_params->frame->fov->sprites;
	if ((ix = loop_spr(spr, x, y, step)) != -1)
	{
		g_params->frame->fov->found_sprites++;
		spr[ix].sprite_y = y;
		spr[ix].sprite_x = x;
		spr[ix].end_column = step;
		spr[ix].s_column = step;
		spr[ix].angle = angle;
		return ;
	}
	return ;
}

int		loop_spr(t_spr *sprites, int x, int y, int step)
{
	int	k;

	k = 0;
	while (k < g_params->frame->fov->found_sprites)
	{
		if (sprites[k].sprite_x == x && sprites[k].sprite_y == y)
		{
			sprites[k].pos_counter += 1;
			if (step < 0 || step > g_params->resolution_x)
				return (loop_spr_border(&sprites[k], step));
			if (step < sprites[k].s_column)
				sprites[k].s_column = step;
			else
				sprites[k].end_column = step;
			return (-1);
		}
		k++;
	}
	return (k);
}
