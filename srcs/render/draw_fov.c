/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:44:52 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/18 00:35:00 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fov(t_cub *cub)
{
	float	x;
	float	ca;
	float	gained_angle;
	float	temp_x;

	ca = no_higher(cub->player.pa - (PLAYER_FOV / 2), 360, 0);
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
