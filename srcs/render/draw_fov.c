/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:44:52 by llevasse          #+#    #+#             */
/*   Updated: 2023/11/27 13:56:08 by tdutel           ###   ########.fr       */
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
	while (gained_angle < PLAYER_FOV)	// remove PLAYER_FOV - 1
	{
		get_player_new_pos(cub, ca, MMAP_S * 5, &fov.p);
		temp_x = x + COLUMN_WIDTH;
		while (x < temp_x)
			cast(cub, x++, ca);
		gained_angle += FIELD_R_STEP;
		ca = no_higher(ca + FIELD_R_STEP, 360, 0);
		get_player_new_pos(cub, ca, MMAP_S * 5, &fov.p2);
		fov.fl = get_line(fov.p, fov.p2);
	}
}

float	get_dist_betw_points(t_point p_a, t_point p_b)
{
	float	dx;
	float	dy;

	dx = p_b.x - p_a.x;
	dy = p_b.y - p_a.y;
	return (sqrt(pow(dy, 2) + pow(dx, 2)));
}

t_fov	get_fov(float *ca)
{
	t_fov	fov;

	fov.beg_angle = no_higher(*ca - ((PLAYER_FOV - 1) / 2), 360, 0);
	fov.end_angle = no_higher(fov.beg_angle + (PLAYER_FOV - 1), 360, 0);
	*ca = fov.beg_angle;
	return (fov);
}

