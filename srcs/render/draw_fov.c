/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:44:52 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/28 15:56:52 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fov(t_cub *cub)
{
	t_fov	fov;
	float	x;
	float	ca;				//angle of casted ray
	float	gained_angle;
	float	temp;

	fov = get_fov(cub);
	ca = fov.cur_angle;		//get leftest angle of fow
	x = 0;
	gained_angle = 0;
	printf("player angle : %f\n", cub->player.pa);
	while (gained_angle < PLAYER_FOV)	//stop when current angle of ray is equal to the rightest angle of fov
	{
		get_player_new_pos(cub, ca, MMAP_H * 5, &fov.p);
		temp = ca + 1;
		while (ca < temp)
		{
			cast(cub, draw_line(*cub, fov.p.x, fov.p.y, PLAYER_RGB), x, ca);
			x += 1;
			ca += fov.field_step;
			gained_angle += fov.field_step;
		}
		ca = no_higher(ca, 360, 0);	//increase angle to the right
		get_player_new_pos(cub, ca, MMAP_H * 5, &fov.p2);
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
	get_player_new_pos(cub, fov.beg_angle, WINDOW_H, &fov.leftest);
	get_player_new_pos(cub, fov.end_angle, WINDOW_W, &fov.rightest);
	get_player_new_pos(cub, fov.beg_angle, get_line_dist(*cub, fov.leftest.x, fov.leftest.y), &fov.leftest);
	get_player_new_pos(cub, fov.end_angle, get_line_dist(*cub, fov.rightest.x, fov.rightest.y), &fov.rightest);
	fov.field_dist = get_dist_betw_points(fov.leftest, fov.rightest);
	fov.field_step = ((float)PLAYER_FOV / WINDOW_W);
	fov.field_dist = (PLAYER_FOV / fov.field_dist);
	return (fov);
}
