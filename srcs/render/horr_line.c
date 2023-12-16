/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horr_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:58:31 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/16 17:00:50 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ray facing up pa > 180 && pa < 360
// ray facing down pa > 0 || pa < 180
//if ray is facing string up or down (pa == 90 || pa == 360 || pa == 0)
int	init_horr(t_cub cub, float pa, t_line *line)
{
	float	tan_v;
	int		width;

	tan_v = 1.0 / tan(pa * RADIAN);
	width = cub.mmap->block_s;
	if (pa > 180 && pa < 360)
	{
		line->y_step = width;
		line->p_a.y = (((int)cub.player.py / width) * width) - 1;
	}
	else if (pa > 0 && pa < 180)
	{
		line->y_step = -width;
		line->p_a.y = (((int)cub.player.py / width) * width) + width;
	}
	else
	{
		line->p_a.x = cub.player.px;
		line->p_a.y = cub.player.py;
		return (-42);
	}
	line->p_a.x = ((cub.player.py - line->p_a.y) * -tan_v) + cub.player.px;
	line->x_step = -line->y_step * tan_v;
	return (cub.mmap->dof);
}

t_line	get_horr(t_cub cub, float pa)
{
	t_line	line;
	int		pos_x;
	int		pos_y;
	int		dof;

	dof = init_horr(cub, pa, &line);
	while (dof-- > 0)
	{
		pos_x = (line.p_a.x / cub.mmap->block_s);
		pos_y = (line.p_a.y / cub.mmap->block_s);
		if (pos_y >= cub.mmap->nb_line || pos_y < 0 || pos_x < 0 || pos_x >= (int)ft_strlen(cub.mmap->map[pos_y]) 
			|| !ft_is_in_str("NSEW0", cub.mmap->map[pos_y][pos_x]))
			break ;
		line.p_a.x += line.x_step;
		line.p_a.y -= line.y_step;
	}
	line = get_line(get_player_point(cub.player.px, cub.player.py), line.p_a);
	if (dof <= -42)
		line.dist = 0x7fffffff + 0.0;
	else
		line.dist *= cos((cub.player.pa - pa) * RADIAN);
	line.wall = get_orient_horr(cub.map, pa, &line.w_type);
	line.wall_percent = ((int)line.p_b.x % cub.mmap->block_s);
	if (pa > 0 && pa < 180)
		line.wall_percent = line.wall->width - line.wall_percent;
	if (line.dist >= 1)
		line.height = ((cub.mmap->block_s * WINDOW_H) / line.dist);
	line.start = (WINDOW_H - line.height) / 2;
	line.stop = (WINDOW_H + line.height) / 2;
	return (line);
}
