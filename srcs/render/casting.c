/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:25:17 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/05 21:46:44 by llevasse         ###   ########.fr       */
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
		cast.line = &h;
		draw_given_line(*cub, h, 0x00ffff);
		cast.type = 1;
	}
	else
	{
		cast.line = &v;
		draw_given_line(*cub, v, 0x0000ff);
		cast.type = 0;
	}
	return (cast);
}

int	get_texture_colour(t_cast c, int height){
	int	y;
	int	x;
	
	y = (int)(height * c.line->wall->height / c.line->height) % c.line->wall->height * c.line->wall->line_len;
	x = c.line->wall_percent * (c.line->wall->bpp / 8);
	return (*(int *)(c.line->wall->addr + y + x));
}

void	cast(t_cub *cub, t_cast c, int x)
{
	int		rgb;
	int		current;

	if (!c.line->wall)
		return ;
	current = 0;
	if (c.line->start < 0)
		current += -c.line->start;
	while (c.line->start + current < c.line->stop && c.line->start + current < WINDOW_H)
	{
		rgb = get_pixel_colour(&cub->img, x, c.line->start + current);
		if (rgb != MMAP_W_RGB && rgb != MMAP_RGB && rgb != PLAYER_RGB)
			img_pix_put(&cub->img, x, c.line->start + current,
				get_texture_colour(c, current));
		current++;
	}
}
