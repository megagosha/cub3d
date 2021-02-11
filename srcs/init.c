/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 03:16:48 by edebi             #+#    #+#             */
/*   Updated: 2021/02/09 18:09:36 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_frame	*init_frame(void)
{
	t_frame	*frame;

	frame = g_params->frame;
	frame->move_fw = 0;
	frame->move_bw = 0;
	frame->move_l = 0;
	frame->move_r = 0;
	frame->rotate_r = 0;
	frame->rotate_l = 0;
	return (frame);
}

void	init_fov(t_frame *frame)
{
	frame->fov = malloc(sizeof(t_fov));
	if (frame->fov == NULL)
		exit_with_error(-2, "Mem error\n");
	frame->fov_size = g_params->resolution_x;
	frame->fov->size = g_params->resolution_x;
	frame->fov->trace_result = malloc(sizeof(t_textures) *
	(frame->fov_size + 1));
	if (frame->fov->trace_result == NULL)
		exit_with_error(-2, "Mem error\n");
	frame->fov->sprites = malloc(sizeof(t_spr) * g_params->num_sprites);
	if (frame->fov->sprites == NULL)
		exit_with_error(-2, "Mem error\n");
	return ;
}

void	init_player(t_frame *frame)
{
	frame->player = malloc(sizeof(t_pos) + 1);
	if (frame->player == NULL)
		exit_with_error(-2, "Mem error\n");
	frame->player->angle_step = (double)FOV / g_params->resolution_x;
	frame->player->x_p = g_params->x_position + 0.5;
	frame->player->y_p = g_params->y_position + 0.5;
	if (g_params->heading == 'N')
		frame->player->deg_p = 90;
	else if (g_params->heading == 'W')
		frame->player->deg_p = 180;
	else if (g_params->heading == 'E')
		frame->player->deg_p = 0;
	else if (g_params->heading == 'S')
		frame->player->deg_p = 270;
	return ;
}

void	calc_max_x(void)
{
	int	i;

	g_params->max_x = malloc(sizeof(int) * g_params->max_row);
	if (g_params->max_x == NULL)
		exit_with_error(-2, "Mem error\n");
	i = 0;
	while (i < g_params->max_row)
	{
		g_params->max_x[i] = (int)ft_strlen(g_params->map[i]);
		i++;
	}
}

void	check_resolution(void *mlx_ptr)
{
	int	sizex;
	int	sizey;

	mlx_get_screen_size(mlx_ptr, &sizex, &sizey);
	if (g_params->resolution_x > sizex)
		g_params->resolution_x = sizex;
	if (g_params->resolution_y >= sizey)
		g_params->resolution_y = sizey;
}
