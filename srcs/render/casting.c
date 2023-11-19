/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:25:17 by llevasse          #+#    #+#             */
/*   Updated: 2023/11/19 20:06:20 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//fisheye : angle of ray from player angle
float	get_fisheye(t_cub *cub, float ca)
{
	float	fisheye;

	fisheye = cub->player.pa - ca;
/*	if (fisheye < 0)
		fisheye += 2 * PI;
	if (fisheye > 2 * PI)
		fisheye -= 2 * PI;*/
	return (cos(fisheye * RADIAN));
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
		cast.wall = get_orient_horr(cub->map, cub->mmap->block_s, h.p_b.x, &cast.w_type);
		draw_given_line(*cub, h, 0x00ffff);
		cast.wall_percent = h.p_b.x * h.dist;
	}
	else
	{
		cast.dist = v.dist;
		cast.wall = get_orient_vert(cub->map, cub->mmap->block_s, h.p_b.y, &cast.w_type);
		draw_given_line(*cub, v, 0x0000ff);
		cast.wall_percent = v.p_b.y * v.dist;
	}
	cast.dist *= get_fisheye(cub, ca);
	if (cast.dist == 0)
		cast.height = WINDOW_H / 2;
	else
		cast.height = WINDOW_H / 2 / cast.dist;
	cast.start = (WINDOW_H / 2) - cast.height;
	cast.stop = (WINDOW_H / 2) + cast.height;
	cast.wall_percent -= floor(cast.wall_percent);
	return (cast);
}

int	get_texture_colour(t_cast c, int height, int wall_type){
	int	y;
	int	x;
	
	y = (int)(height * c.wall->height / c.height) % c.wall->height * c.wall->line_len;
	if (wall_type == SO || wall_type == WE)
		x = ((int)((1.0f - c.wall_percent) * c.wall->width));
	else
		x = ((int)(c.wall_percent * c.wall->width));
	x *= c.wall->bpp / 8;
	return (*(int *)(c.wall->addr + y + x));
}

void	cast(t_cub *cub, int x, float ca)
{
	int		rgb;
	int		current;
	t_cast	c;

	c = get_cast_data(cub, ca);
	if (!c.wall)
		return ;
	current = c.start;
	while (current < c.stop)
	{
		rgb = get_pixel_colour(&cub->img, x, c.start);
		if (rgb != MMAP_W_RGB && rgb != MMAP_RGB && rgb != PLAYER_RGB)
			img_pix_put(&cub->img, x, c.start,
				get_texture_colour(c, current - c.start, c.w_type));
		current++;
	}
}
