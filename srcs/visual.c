/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 20:08:06 by edebi             #+#    #+#             */
/*   Updated: 2021/02/09 15:50:32 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_params(int *height_offset, double *cur_row, int *line_length,
double row_step)
{
	if (*line_length > g_params->resolution_y)
	{
		*cur_row = (double)(*line_length - g_params->resolution_y)
				/ 2 * row_step;
		*height_offset = 0;
		*line_length = g_params->resolution_y;
	}
	else
	{
		*cur_row = 0;
		*height_offset = (g_params->resolution_y - *line_length) / 2;
	}
	return ;
}

t_frame	*set_frame(void)
{
	t_frame *frame;

	frame = init_frame();
	frame->vars->win = mlx_new_window(frame->vars->mlx, g_params->resolution_x,
	g_params->resolution_y, "Georgenstein7d!");
	frame->img = malloc(sizeof(t_data));
	if (frame->img == NULL)
		exit_with_error(-2, "Mem error\n");
	frame->img->img = mlx_new_image(frame->vars->mlx,
	g_params->resolution_x, g_params->resolution_y);
	frame->img->addr = mlx_get_data_addr(frame->img->img,
	&frame->img->bits_per_pixel, &frame->img->line_length, &frame->img->endian);
	frame->size_x = g_params->resolution_x;
	frame->size_y = g_params->resolution_y;
	init_player(frame);
	init_fov(frame);
	return (frame);
}

void	run(void)
{
	t_frame	*frame;

	frame = set_frame();
	g_params->frame = frame;
	mlx_hook(frame->vars->win, EVENT_KEY_PRESS, 0, &key, frame);
	mlx_hook(frame->vars->win, EVENT_KEY_RELEASE, 0, &key_release, frame);
	mlx_hook(frame->vars->win, EVENT_EXIT, 0, &red_cross, NULL);
	mlx_loop_hook(frame->vars->mlx, &render_frame, frame);
	mlx_loop(frame->vars->mlx);
}

void	rotate(t_frame *frame)
{
	if (frame->rotate_l)
		frame->player->deg_p = normalize_angle(frame->player->deg_p + DEG_STEP *
				g_params->resolution_x / 300);
	if (frame->rotate_r)
		frame->player->deg_p = normalize_angle(frame->player->deg_p - DEG_STEP *
g_params->resolution_x / 300);
}
