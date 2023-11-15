/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:44:52 by llevasse          #+#    #+#             */
/*   Updated: 2023/11/15 12:00:51 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//float	ca is angle of casted ray
//second while loop : draw value of one cast as a column on window
//third while oop : fill radar on minimap
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
		temp_x = x + fov.column_width;
		while (x < temp_x)
			cast(cub, x++, ca);
		gained_angle += fov.field_step;
		ca = no_higher(ca + fov.field_step, 360, 0);
		get_player_new_pos(cub, ca, MMAP_S * 5, &fov.p2);
		fov.fl = get_line(fov.p, fov.p2);
/*		while (gained_angle < PLAYER_FOV - 1 && fov.fl.steps-- > 0 && draw_line(*cub, fov.p, PLAYER_RGB, gained_angle))
		{
			fov.p.x += fov.fl.x_step;
			fov.p.y += fov.fl.y_step;
		}*/
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

	fov.player_dist = (WINDOW_W / 2) / tan(PLAYER_FOV / 2);
	fov.beg_angle = no_higher(*ca - ((PLAYER_FOV - 1) / 2), 360, 0);
	fov.end_angle = no_higher(fov.beg_angle + (PLAYER_FOV - 1), 360, 0);
	*ca = fov.beg_angle;
	fov.field_step = ((float)(PLAYER_FOV - 1) / WINDOW_W / 16);
	fov.column_width = (WINDOW_W / PLAYER_FOV) * fov.field_step;
	return (fov);
}



/*

peut etre que les bordures differente proviennent selon l'ordre des confitions dans get_otientation
*/
