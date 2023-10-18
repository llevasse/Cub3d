/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:25:17 by llevasse          #+#    #+#             */
/*   Updated: 2023/10/18 13:10:51 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//fisheye : angle of ray from player angle
float	get_fisheye(t_cub *cub, float ca)
{
	float	fisheye;

	fisheye = cub->player.pa - ca;
	if (fisheye < 0)
		fisheye += 2 * PI;
	if (fisheye > 2 * PI)
		fisheye -= 2 * PI;
	return (fisheye);
}

void	cast(t_cub *cub, double dist, int x, float ca, t_point end_point)
{
	int		high_y;
	int		low_y;
	int		height;
	int		colour;
	t_img	wall;

	ca = no_higher(ca, 360, 0);
	wall = get_orientation(cub->map, cub->mmap->block_s, end_point.x, end_point.y);
//	dist *= cos(get_fisheye(cub, ca));
	printf("%f\n", dist);
	if (dist == 0)
		dist = 1;
	height = (cub->mmap->block_s * WINDOW_H) / dist;
	if (height > WINDOW_H)
		height = WINDOW_H;
	high_y = (WINDOW_H / 2) - height / 2;
	low_y = (WINDOW_H / 2) + height / 2;
	if (high_y < 0)
		high_y = 0;
	if (low_y > WINDOW_H)
		low_y = WINDOW_H;
	while (high_y < low_y)
	{
		colour = get_pixel_colour(&cub->img, x, high_y);
		if (colour != MMAP_W_RGB && colour != MMAP_RGB && colour != PLAYER_RGB)
			img_pix_put(&cub->img, x, high_y, get_pixel_colour(&wall, x % 64, high_y % 64));
		high_y++;
	}
}
