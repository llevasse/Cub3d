/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:25:17 by llevasse          #+#    #+#             */
/*   Updated: 2023/11/24 23:12:34 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cast	get_cast_data(t_cub *cub, float ca)
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
		cast.wall_percent = ((int)h.p_b.x % cub->mmap->block_s);
	}
	else
	{
		cast.dist = v.dist;
		cast.wall = get_orient_vert(cub->map, cub->mmap->block_s, h.p_b.y, &cast.w_type);
		draw_given_line(*cub, v, 0x0000ff);
		cast.wall_percent = ((int)v.p_b.y % cub->mmap->block_s);
	}
	printf("%f\n", cast.wall_percent);
	cast.dist *= cos((cub->player.pa - ca) * RADIAN);		//apply fisheye
	if (cast.dist == 0)
		cast.height = WINDOW_H;
	else
		cast.height = ((cub->mmap->block_s * WINDOW_H) / cast.dist);
	cast.start = (WINDOW_H / 2) - (cast.height/2);
	cast.stop = (WINDOW_H / 2) + (cast.height/2);
	if (cast.start < 0)
		cast.start = 0;
	if (cast.stop > WINDOW_H)
		cast.stop = WINDOW_H;
	return (cast);
}

int	get_texture_colour(t_cast c, int height){
	int	y;
	int	x;
	
	y = (int)(height * c.wall->height / c.height) % c.wall->height * c.wall->line_len;
	x = c.wall_percent * (c.wall->bpp / 8);
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
			img_pix_put(&cub->img, x, current,
				get_texture_colour(c, current - c.start));
		current++;
	}
}
