/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:25:17 by llevasse          #+#    #+#             */
/*   Updated: 2023/11/04 19:03:47 by llevasse         ###   ########.fr       */
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

void	cast(t_cub *cub, float dist, int x, float ca)
{
	int		high_y;
	int		low_y;
	int		height;
	int		colour;
	int		center = 0;
	int		img_x;
	float	img_y_ratio;
	int		img_y = 0;
	t_line	horr;
	t_line	vert;
	t_line	line;
	t_img	*wall;
	
	horr = get_horr(*cub, ca);
	vert = get_vert(*cub, ca);
	if (horr.dist < vert.dist)
	{
		dist = horr.dist;
		line = horr;
		wall = get_orientation(cub->map, cub->mmap->block_s, horr.p_b.x, horr.p_b.y);
		img_x= get_x(horr.p_b.x, horr.p_b.y, cub->mmap->block_s);
		draw_given_line(*cub, horr, 0x00ffff);
	}
	else
	{
		dist = vert.dist;
		line = vert;
		wall = get_orientation(cub->map, cub->mmap->block_s, vert.p_b.x, vert.p_b.y);
		img_x= get_x(vert.p_b.x, vert.p_b.y, cub->mmap->block_s);
		draw_given_line(*cub, vert, 0x0000ff);
	}
	if (!wall)
		return ;
//	dist *= cos(get_fisheye(cub, ca));
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
	img_y_ratio = height / 64;
	int	tmp_y;
	while (high_y < low_y)
	{
		tmp_y=0;
		while (high_y < low_y && tmp_y <= img_y_ratio)
		{
			colour = get_pixel_colour(&cub->img, x, high_y);
//			printf("%f\n",img_y_ratio * img_y);
			if (colour != MMAP_W_RGB && colour != MMAP_RGB && colour != PLAYER_RGB){
				if (!center)
					img_pix_put(&cub->img, x, high_y, get_pixel_colour(wall, img_x, img_y));
				else
					img_pix_put(&cub->img, x, high_y, 0x222222);
			}
			high_y++;
			tmp_y++;
		}
		img_y++;
	}
}
