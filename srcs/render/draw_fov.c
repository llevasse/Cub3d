/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:44:52 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/24 16:49:18 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fov(t_cub *cub)
{
	t_fov	fov;

	fov = get_fov(cub);
	while (fov.cur_angle != fov.end_angle)
	{
		get_player_new_pos(cub, fov.cur_angle, MMAP_H * 10, &fov.p);
		fov.cur_angle = no_higher(fov.cur_angle + 1, 360, 0);
		get_player_new_pos(cub, fov.cur_angle, MMAP_H * 10, &fov.p2);
		fov.false_line = get_line(fov.p, fov.p2);
		while (fov.false_line.steps-- > 0)
		{
			draw_line(*cub, (int)fov.p.x, (int)fov.p.y, PLAYER_RGB);
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

	fov.beg_angle = no_higher(-(PLAYER_FOV / 2), 360, 0);
	fov.end_angle = no_higher(fov.beg_angle + PLAYER_FOV, 360, 0);
	fov.cur_angle = fov.beg_angle;
	get_player_new_pos(cub, fov.beg_angle, MMAP_H * 10, &fov.leftest);
	get_player_new_pos(cub, fov.end_angle, MMAP_H * 10, &fov.rightest);
	fov.field_dist = get_dist_betw_points(fov.leftest, fov.rightest);
	return (fov);
}
