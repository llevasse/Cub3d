/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:25:17 by llevasse          #+#    #+#             */
/*   Updated: 2023/11/04 19:26:35 by llevasse         ###   ########.fr       */
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

static	t_cast get_cast_data(t_cub *cub, float ca)
{
	t_cast	cast;
	t_line	horr;
	t_line	vert;

	horr = get_horr(*cub, ca);
	vert = get_vert(*cub, ca);
	if (horr.dist < vert.dist)
	{
		cast.dist = horr.dist;
		cast.wall = get_orientation(cub->map, cub->mmap->block_s, horr.p_b.x, horr.p_b.y);
		cast.x= get_x(horr.p_b.x, horr.p_b.y, cub->mmap->block_s);
		draw_given_line(*cub, horr, 0x00ffff);
	}
	else
	{
		cast.dist = vert.dist;
		cast.wall = get_orientation(cub->map, cub->mmap->block_s, vert.p_b.x, vert.p_b.y);
		cast.x= get_x(vert.p_b.x, vert.p_b.y, cub->mmap->block_s);
		draw_given_line(*cub, vert, 0x0000ff);
	}
	if (cast.dist == 0)
		cast.dist = 1;
	cast.height = (cub->mmap->block_s * WINDOW_H) / cast.dist;
	if (cast.height > WINDOW_H)
		cast.height = WINDOW_H;
	cast.high = (WINDOW_H / 2) - cast.height / 2;
	cast.low = (WINDOW_H / 2) + cast.height / 2;
	cast.y_ratio = cast.height / 64;
	cast.y = 0;
	return (cast);
}

void	cast(t_cub *cub, int x, float ca)
{
	int		colour;
	int		tmp_y;
	t_cast	cast;
	
	cast = get_cast_data(cub, ca);
	if (!cast.wall)
		return ;
//	dist *= cos(get_fisheye(cub, ca));
	if (cast.high < 0)
		cast.high = 0;
	if (cast.low > WINDOW_H)
		cast.low = WINDOW_H;
	while (cast.high < cast.low)
	{
		tmp_y=0;
		while (cast.high < cast.low && tmp_y <= cast.y_ratio)
		{
			colour = get_pixel_colour(&cub->img, x, cast.high);
			if (colour != MMAP_W_RGB && colour != MMAP_RGB && colour != PLAYER_RGB){
				img_pix_put(&cub->img, x, cast.high, get_pixel_colour(cast.wall, cast.x, cast.y));
			}
			cast.high++;
			tmp_y++;
		}
		cast.y++;
	}
}
