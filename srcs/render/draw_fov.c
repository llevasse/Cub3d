/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:44:52 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/23 21:52:40 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fov(t_cub *cub)
{
	float	fov_angle;
	float	fov_end_a;
	t_point	p;
	t_point	p2;
	t_line	false_line;

	fov_angle = no_higher(-(PLAYER_FOV / 2), 360, 0);
	fov_end_a = no_higher(fov_angle + PLAYER_FOV, 360, 0);
	while (fov_angle != fov_end_a)
	{
		get_player_new_pos(cub, fov_angle, MMAP_H * 10, &p);
		fov_angle = no_higher(fov_angle + 1, 360, 0);
		get_player_new_pos(cub, fov_angle, MMAP_H * 10, &p2);
		false_line = get_line(p, p2);
		while (false_line.steps-- > 0)
		{
			draw_line(*cub, (int)p.x, (int)p.y, PLAYER_RGB);
			p.x += false_line.x_step;
			p.y += false_line.y_step;
		}
	}
}
// fov_end_a for fov_end_angle!
