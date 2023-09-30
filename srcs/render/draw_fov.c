/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:44:52 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/30 23:05:34 by llevasse         ###   ########.fr       */
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

	fov = get_fov(cub);
	ca = fov.cur_angle;
	x = 0;
	gained_angle = 0;
	while (gained_angle < PLAYER_FOV)
	{
		get_player_new_pos(cub, no_higher(ca + gained_angle, 360, 0), MMAP_H * 5, &fov.p);
		temp_x = x + ((WINDOW_W / PLAYER_FOV) * fov.field_step);
		while (x < temp_x)
			cast(cub, draw_line(*cub, fov.p.x, fov.p.y, PLAYER_RGB), x++, ca);
		gained_angle += fov.field_step;
		get_player_new_pos(cub, no_higher(ca + gained_angle, 360, 0), MMAP_H * 5, &fov.p2);
		fov.false_line = get_line(fov.p, fov.p2);
		while (fov.false_line.steps-- > 0)
		{
			draw_line(*cub, fov.p.x, fov.p.y, PLAYER_RGB);
			fov.p.x += fov.false_line.x_step;
			fov.p.y += fov.false_line.y_step;
		}
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

t_fov	get_fov(t_cub *cub)
{
	t_fov	fov;

	fov.player_dist = (WINDOW_W / 2) / tan(PLAYER_FOV / 2);
	fov.beg_angle = no_higher(-(PLAYER_FOV / 2), 360, 0);	//angle of begining of fov
	fov.end_angle = no_higher(fov.beg_angle + PLAYER_FOV, 360, 0);	//angle of end of fov
	fov.cur_angle = fov.beg_angle;
	fov.field_step = ((float)PLAYER_FOV / WINDOW_W);
	(void)cub;
	return (fov);
}
