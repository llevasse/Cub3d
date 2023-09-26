/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:44:52 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/26 23:55:08 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fov(t_cub *cub)
{
	t_fov	fov;
	float	x;
	float	ca;				//angle of casted ray

	fov = get_fov(cub);
	ca = fov.cur_angle;		//get leftest angle of fow
	x = 0;
	while (ca != fov.end_angle && x < WINDOW_W)	//stop when current angle of ray is equal to the rightest angle of fov
	{
		get_player_new_pos(cub, ca, MMAP_H * 10, &fov.p);
		get_player_new_pos(cub, ca + 1, MMAP_H * 10, &fov.p2);
		fov.false_line = get_line(fov.p, fov.p2);
		while (fov.false_line.steps-- > 0)
		{
			cast(cub, draw_line(*cub, fov.p.x, fov.p.y, PLAYER_RGB), x, ca);
			fov.p.x += fov.false_line.x_step;
			fov.p.y += fov.false_line.y_step;
			x += fov.field_step;
		}
		ca = no_higher(ca + fov.field_step, 360, 0);	//increase angle to the right
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

	fov.beg_angle = no_higher(-(PLAYER_FOV / 2), 360, 0);	//angle of begining of fov
	fov.end_angle = no_higher(fov.beg_angle + PLAYER_FOV, 360, 0);	//angle of end of fov
	fov.cur_angle = fov.beg_angle;
	get_player_new_pos(cub, fov.beg_angle, MMAP_H * 10, &fov.leftest);
	get_player_new_pos(cub, fov.end_angle, MMAP_H * 10, &fov.rightest);
	fov.field_dist = get_dist_betw_points(fov.leftest, fov.rightest);
	fov.field_step = WINDOW_W / fov.field_dist;
//	printf("%f per steps (%f/%d)\n", fov.field_step, fov.field_dist, WINDOW_W);
	return (fov);
}
