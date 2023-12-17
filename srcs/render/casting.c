/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:25:17 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/17 11:37:03 by llevasse         ###   ########.fr       */
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
		cast.line = cast.h;
		cast.dist = cast.h.dist;
	}
	else
	{
		cast.line = cast.v;
		cast.dist = cast.v.dist;
	}
	return (cast);
}

int	get_texture_colour(t_line line, int height)
{
	int	y;
	int	x;

	y = (int)(height * line.wall->height / line.height)
		% line.wall->height * line.wall->line_len;
	x = line.wall_percent * (line.wall->bpp / 8);
	return (*(int *)(line.wall->addr + y + x));
}

void	cast(t_cub *cub, t_cast c, int x)
{
	int		rgb;
	int		current;

	current = 0;
	if (c.line.start < 0)
		current += -c.line.start;
	while (c.line.start + current < c.line.stop
		&& c.line.start + current < WINDOW_H)
	{
		rgb = get_pixel_colour(&cub->img, x, c.line.start + current);
		if (rgb != MMAP_W_RGB && rgb != MMAP_RGB && rgb != PLAYER_RGB)
			img_pix_put(&cub->img, x, c.line.start + current,
				get_texture_colour(c.line, current));
		current++;
	}
}
