/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:44:52 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/22 21:51:58 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fov(t_cub *cub)
{
	float	fov_angle;
	float	fov_end_a;
	float	y;
	float	x;

	fov_angle = no_higher(cub->player.pa - (PLAYER_FOV/2), 360, 0);
	fov_end_a = fov_angle + PLAYER_FOV;
	x = 0;
	while (fov_angle != fov_end_a)
	{
		y = get_player_new_pos(cub, fov_angle, 10, &x);
		printf("draw from  (%d:%d) to (%d:%d)\n", (int)cub->player.px, (int)cub->player.py, (int)x, (int)y);
		draw_line(*cub, (int)x, (int)y);
		fov_angle = no_higher(fov_angle + 1, 360, 0);
		printf("FOV : %f/%f\n", fov_angle, fov_end_a);
	}
}
