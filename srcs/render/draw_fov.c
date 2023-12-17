/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:44:52 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/17 22:08:28 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fov(t_cub *cub)
{
	t_fov	fov;
	float	x;
	float	ca;
	float	gained_angle;
	float	temp_x;

	ca = cub->player.pa;
	fov = get_fov(&ca);
	x = 0;
	gained_angle = 0;
	while (gained_angle < PLAYER_FOV)
	{
		temp_x = x + cub->column_width;
		while (x < temp_x && x < WINDOW_W)
			cast(cub, get_cast_data(cub, ca), x++);
		gained_angle += cub->field_step;
		ca = no_higher(ca + cub->field_step, 360, 0);
	}
	x = -1;
	draw_minimap(cub);
}

t_fov	get_fov(float *ca)
{
	t_fov	fov;

	fov.beg_angle = no_higher(*ca - ((PLAYER_FOV) / 2), 360, 0);
	fov.end_angle = no_higher(fov.beg_angle + (PLAYER_FOV - 1), 360, 0);
	*ca = fov.beg_angle;
	return (fov);
}
