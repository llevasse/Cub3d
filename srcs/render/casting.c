/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:25:17 by llevasse          #+#    #+#             */
/*   Updated: 2023/11/14 13:08:37 by tdutel           ###   ########.fr       */
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

static t_cast	get_cast_data(t_cub *cub, float ca)
{
	t_cast	cast;
	t_line	h;
	t_line	v;

	h = get_horr(*cub, ca);
	v = get_vert(*cub, ca);
	if (h.dist < v.dist)
	{
		cast.dist = h.dist;
		cast.wall = get_orient(cub->map, cub->mmap->block_s, h.p_b.x, h.p_b.y);
		cast.x = get_x(h.p_b.x, h.p_b.y, cub->mmap->block_s);
		draw_given_line(*cub, h, 0x00ffff);
	}
	else
	{
		cast.dist = v.dist;
		cast.wall = get_orient(cub->map, cub->mmap->block_s, v.p_b.x, v.p_b.y);
		cast.x = get_x(v.p_b.x, v.p_b.y, cub->mmap->block_s);
		draw_given_line(*cub, v, 0x0000ff);
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
	int		rgb;
	int		tmp_y;
	t_cast	c;

	c = get_cast_data(cub, ca);
	if (!c.wall)
		return ;
	if (c.high < 0)
		c.high = 0;
	if (c.low > WINDOW_H)
		c.low = WINDOW_H;
	while (c.high < c.low)
	{
		tmp_y = 0;
		while (c.high < c.low && tmp_y <= c.y_ratio)
		{
			rgb = get_pixel_colour(&cub->img, x, c.high);
			if (rgb != MMAP_W_RGB && rgb != MMAP_RGB && rgb != PLAYER_RGB)
				img_pix_put(&cub->img, x, c.high,
					get_pixel_colour(c.wall, c.x, c.y));
			c.high++;
			tmp_y++;
		}
		c.y++;
	}
}
