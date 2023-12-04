/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:25:17 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/04 15:41:02 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	simulcast(t_cub cub, float ca);

t_cast	get_cast_data(t_cub *cub, float ca)
{
	t_cast	cast;
	t_line	h;
	t_line	v;

	h = get_horr(*cub, ca);
	v = get_vert(*cub, ca);
	/*
		Le v est mal calculé et chaque rayon bleu foncé correspond aux pics sur les murs.
	*/
	if (h.dist < v.dist)
	{
		if (((simulcast(*cub, no_higher(ca - FIELD_R_STEP, 360, 0)) == 'v' && cub->hv == 0)
		|| (simulcast(*cub, no_higher(ca - FIELD_R_STEP, 360, 0)) == 'h' && cub->hv == 1))
		&& simulcast(*cub, no_higher(ca + FIELD_R_STEP, 360, 0)) == 'v')
		{
			cast.dist = v.dist * cos((cub->player.pa - ca) * RADIAN);
			cast.wall = get_orient_vert(cub->map, ca, &cast.w_type);
			draw_given_line(*cub, v, 0x0000ff);	//blue ray v
			cast.wall_percent = ((int)v.p_b.y % cast.wall->width);
			cub->hv = 1;
		}
		else
		{
			cast.dist = h.dist * cos((cub->player.pa - ca) * RADIAN);
			cast.wall = get_orient_horr(cub->map, ca, &cast.w_type);
			draw_given_line(*cub, h, 0x00ffff);	//cyan ray h
			cast.wall_percent = ((int)h.p_b.x % cast.wall->width);
			cub->hv = 0;
		}
	}
	else
	{
		if (((simulcast(*cub, no_higher(ca - FIELD_R_STEP, 360, 0)) == 'h' && cub->hv == 0)
			|| (simulcast(*cub, no_higher(ca - FIELD_R_STEP, 360, 0)) == 'v' && cub->hv == 1))
			&& simulcast(*cub, no_higher(ca + FIELD_R_STEP, 360, 0)) == 'h')
		{
			cast.dist = h.dist * cos((cub->player.pa - ca) * RADIAN);
			cast.wall = get_orient_horr(cub->map, ca, &cast.w_type);
			draw_given_line(*cub, h, 0x00ffff);	//cyan ray h
			cast.wall_percent = ((int)h.p_b.x % cast.wall->width);
			cub->hv = 1;
		}
		else
		{
			cast.dist = v.dist * cos((cub->player.pa - ca) * RADIAN);
			cast.wall = get_orient_vert(cub->map, ca, &cast.w_type);
			draw_given_line(*cub, v, 0x0000ff);	//blue ray v
			cast.wall_percent = ((int)v.p_b.y % cast.wall->width);
			cub->hv = 0;
		}
	}
	if (cast.dist < 1) //if player is almost inside the wall
		cast.height = WINDOW_H;
	else
		cast.height = ((cub->mmap->block_s * WINDOW_H) / cast.dist);
	cast.start = (WINDOW_H - cast.height) / 2;
	cast.stop = (WINDOW_H + cast.height) / 2;
	return (cast);
}

int	get_texture_colour(t_cast c, int height){
	int	y;
	int	x;

	// printf("height : %d\t wall->height : %d\t c.height : %d\t wall->line_len : %d\n\n", height, c.wall->height, c.height, c.wall->line_len);
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
	current = 0;
	if (c.start < 0)
		current += -c.start;
	while (c.start + current < c.stop && c.start + current < WINDOW_H)
	{
		rgb = get_pixel_colour(&cub->img, x, c.start + current);
		if (rgb != MMAP_W_RGB && rgb != MMAP_RGB && rgb != PLAYER_RGB)
			img_pix_put(&cub->img, x, c.start + current,
				get_texture_colour(c, current));
		current++;
	}
}


char	simulcast(t_cub cub, float ca)
{
	t_line	h;
	t_line	v;

	h = get_horr(cub, ca);
	v = get_vert(cub, ca);
	if (h.dist < v.dist)
		return ('h');
	else if (v.dist < h.dist)
		return ('v');
	else
		return ('0');
}
