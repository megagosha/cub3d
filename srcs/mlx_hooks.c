/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 03:11:11 by edebi             #+#    #+#             */
/*   Updated: 2021/02/09 18:48:41 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		render_frame(t_frame *frame)
{
	int		floor_color;
	int		sky_color;
	int		update;

	update = get_update(frame);
	if (!update)
		return (1);
	sky_color = create_trgb(50, g_params->ceilling_color[0],
	g_params->ceilling_color[1], g_params->ceilling_color[2]);
	floor_color = create_trgb(0, g_params->floor_color[0],
	g_params->floor_color[1], g_params->floor_color[2]);
	frame->fov->player_angle = frame->player->deg_p;
	color_fill(frame, sky_color, floor_color, *frame->img);
	print_fov(calculate_fov(g_params, frame->fov,
	frame->player->x_p, frame->player->y_p));
	mlx_put_image_to_window(frame->vars->mlx, frame->vars->win,
	(*frame->img).img, 0, 0);
	g_params->frame = frame;
	if (g_params->start == -1)
		save_image();
	mlx_do_sync(frame->vars->mlx);
	return (1);
}

int		key(int keycode, t_frame *frame)
{
	if (keycode == KEY_Q || keycode == KEY_LEFT)
		frame->rotate_l = 1;
	else if (keycode == KEY_E || keycode == KEY_RIGHT)
		frame->rotate_r = 1;
	else if (keycode == KEY_W || keycode == KEY_UP)
		frame->move_fw = 1;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		frame->move_bw = 1;
	else if (keycode == KEY_ESCAPE || keycode == EVENT_EXIT)
		exit_with_error(0, "Bye\n");
	else if (keycode == KEY_A)
		frame->move_l = 1;
	else if (keycode == KEY_D)
		frame->move_r = 1;
	return (keycode);
}

int		key_release(int keycode, t_frame *frame)
{
	if (keycode == KEY_Q || keycode == KEY_LEFT)
		frame->rotate_l = 0;
	else if (keycode == KEY_E || keycode == KEY_RIGHT)
		frame->rotate_r = 0;
	else if (keycode == KEY_W || keycode == KEY_UP)
		frame->move_fw = 0;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		frame->move_bw = 0;
	else if (keycode == KEY_A)
		frame->move_l = 0;
	else if (keycode == KEY_D)
		frame->move_r = 0;
	return (0);
}

int		get_update_two(t_frame *frame, int update)
{
	if (frame->move_bw)
	{
		update_player_pos(frame->player, -0.2 * 3, 1);
		update = 1;
	}
	if (frame->rotate_l || frame->rotate_r)
	{
		rotate(frame);
		update = 1;
	}
	if (g_params->start == 0 || g_params->start == -1)
	{
		if (g_params->start == 0)
			g_params->start = 1;
		return (1);
	}
	return (update);
}

int		get_update(t_frame *frame)
{
	int	update;

	update = 0;
	if (frame->move_r)
	{
		update_player_pos(frame->player, 0.2 * 3, 0);
		update = 1;
	}
	if (frame->move_l)
	{
		update_player_pos(frame->player, -0.2 * 3, 0);
		update = 1;
	}
	if (frame->move_fw)
	{
		update_player_pos(frame->player, 0.2 * 3, 1);
		update = 1;
	}
	return (get_update_two(frame, update));
}
