/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:44:52 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/23 15:45:53 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fov(t_cub *cub)
{
	float	fov_angle;
	float	fov_end_a;
	float	y;
	float	x;
	int		ite;
	
	fov_angle = no_higher((cub->player.pa - (PLAYER_FOV/2)), 360, 0);
	fov_end_a = no_higher(fov_angle + PLAYER_FOV, 360, 0);
	x = 0;
	ite = 0;
	while (fov_angle != fov_end_a)
	{
		y = get_player_new_pos(cub, fov_angle, MINIMAP_HEIGHT * 10, &x);
		if (ite)
			draw_line(*cub, (int)x, (int)y, 0x222222);
		else
			draw_line(*cub, (int)x, (int)y, PLAYER_RGB);
		ite++;
		fov_angle = no_higher(fov_angle + 1, 360, 0);
	}
}
// fov_end_a for fov_end_angle!
