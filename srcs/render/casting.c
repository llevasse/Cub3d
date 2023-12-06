/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:25:17 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/06 23:26:44 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cast	get_cast_data(t_cub *cub, float ca)
{
	t_cast	cast;

	cast.h = get_horr(*cub, ca);
	cast.v = get_vert(*cub, ca);
	if (cast.h.dist < cast.v.dist)
	{
		cast.line = &cast.h;
		draw_given_line(*cub, cast.h, 0x00ffff);
		cast.type = 1;
		cast.dist = cast.h.dist;
	}
	else
	{
		cast.line = &cast.v;
		draw_given_line(*cub, cast.v, 0x0000ff);
		cast.type = 0;
		cast.dist = cast.v.dist;
	}
	return (cast);
}

//bug : block display left half of texture and and other block the right half
int	get_texture_colour(t_line line, int height){
	int	y;
	int	x;

	y = (int)(height * line.wall->height / line.height) % line.wall->height * line.wall->line_len;
	x = line.wall_percent * (line.wall->bpp / 8);
	return (*(int *)(line.wall->addr + y + x));
}



//bug : on west and north side, corners of most block display south or east texture
void	cast(t_cub *cub, t_cast c, int x)
{
	int		rgb;
	int		current;

	current = 0;
	if (c.type == 1){
		if (c.h.start < 0)
			current += -c.h.start;
		while (c.h.start + current < c.h.stop && c.h.start + current < WINDOW_H)
		{
			rgb = get_pixel_colour(&cub->img, x, c.h.start + current);
			if (rgb != MMAP_W_RGB && rgb != MMAP_RGB && rgb != PLAYER_RGB)
				img_pix_put(&cub->img, x, c.h.start + current,
					get_texture_colour(c.h, current));
			current++;
		}
	}
	else {
		if (c.v.start < 0)
			current += -c.v.start;
		while (c.v.start + current < c.v.stop && c.v.start + current < WINDOW_H)
		{
			rgb = get_pixel_colour(&cub->img, x, c.v.start + current);
			if (rgb != MMAP_W_RGB && rgb != MMAP_RGB && rgb != PLAYER_RGB)
				img_pix_put(&cub->img, x, c.v.start + current,
					get_texture_colour(c.v, current));
			current++;
		}
	}
}
