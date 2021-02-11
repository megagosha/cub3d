/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 03:25:12 by edebi             #+#    #+#             */
/*   Updated: 2021/02/08 03:36:15 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		replace_sprites(t_spr *buf, t_spr *a, t_spr *b)
{
	*buf = *a;
	*a = *b;
	*b = *buf;
	return (1);
}

void	sort_sprites(t_spr *sprites, int num_spr, int i)
{
	t_spr	buf;
	double	distance_prev;
	int		loop_complete;

	distance_prev = sprites[0].distance;
	i = 1;
	loop_complete = 0;
	while (1)
	{
		if (i + 1 > num_spr)
		{
			if (loop_complete == 0)
				break ;
			i = 1;
			distance_prev = sprites[0].distance;
			loop_complete = 0;
		}
		if (sprites[i].distance < distance_prev)
			loop_complete = replace_sprites(&buf, &sprites[i - 1], &sprites[i]);
		distance_prev = sprites[i].distance;
		i++;
	}
}
