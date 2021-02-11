/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing_sprites2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 03:33:11 by edebi             #+#    #+#             */
/*   Updated: 2021/02/09 19:00:19 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	prepare_data(double *min_angle, double *max_angle, double x0, double y0)
{
	t_fov	*fov;

	fov = g_params->frame->fov;
	*min_angle = normalize_angle(fov->player_angle - FOV / 2);
	*max_angle = normalize_angle(fov->player_angle + FOV / 2);
	fov->vars.rad_player_angle = to_radians(fov->player_angle);
	fov->vars.x_0 = x0;
	fov->vars.y_0 = y0;
	fov->found_sprites = 0;
	set_sprites(fov);
}

int		cal_spr(t_spr *spr, double x_0, double y_0, int max_spr)
{
	int i;
	int	x;
	int	y;

	i = 0;
	while (i < max_spr)
	{
		if (spr[i].sprite_x != -1)
		{
			x = spr[i].sprite_x;
			y = spr[i].sprite_y;
			if (spr[i].angle < 270 && spr[i].angle > 90)
				x += 1;
			if (spr[i].angle > 0 && spr[i].angle < 180)
				y += 1;
			spr[i].distance = (sqrt(pow(x_0 - x, 2) + pow(y_0 - y, 2)));
		}
		i++;
	}
	return (i);
}

int		red_cross(void)
{
	ft_putstr("Bye\n");
	exit(0);
}

int		get_color(t_data *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}
