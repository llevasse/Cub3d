/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:25:17 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/05 22:05:58 by llevasse         ###   ########.fr       */
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
	}
	else
	{
		cast.line = &cast.v;
		draw_given_line(*cub, cast.v, 0x0000ff);
		cast.type = 0;
	}
	return (cast);
}

int	get_texture_colour(t_cast c, int height){
	int	y;
	int	x;

	printf("%d\n", height);
	y = (int)(height * c.line->wall->height / c.line->height) % c.line->wall->height * c.line->wall->line_len;
	x = c.line->wall_percent * (c.line->wall->bpp / 8);
	return (*(int *)(c.line->wall->addr + y + x));
}

void	cast(t_cub *cub, t_cast c, int x)
{
	int		rgb;
	int		current;
	t_line	line;

	line = *c.line;
	current = 0;
	if (line.start < 0)
		current += -line.start;
	while (line.start + current < line.stop && line.start + current < WINDOW_H)
	{
		rgb = get_pixel_colour(&cub->img, x, line.start + current);
		if (rgb != MMAP_W_RGB && rgb != MMAP_RGB && rgb != PLAYER_RGB)
			img_pix_put(&cub->img, x, line.start + current,
				get_texture_colour(c, current));
		current++;
	}
}
