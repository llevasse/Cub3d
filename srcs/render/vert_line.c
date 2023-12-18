/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vert_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:58:31 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/18 21:27:36 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ray facing left pa > 90 && pa < 270
// ray facing right pa < 270 || pa < 90
//if ray is facing string left or right (pa == 90 || pa == 270)
int	init_vert(t_cub cub, float pa, t_line *line)
{
	float	tan_v;
	int		width;

	tan_v = tan(pa * RADIAN);
	width = cub.mmap->block_s;
	if (pa > 90 && pa < 270)
	{
		line->x_step = -width;
		line->p_a.x = (((int)cub.player.px / width) * width) - 0.001;
	}
	else if ((pa > 270 && pa < 360) || (pa < 90 && pa > 0))
	{
		line->x_step = width;
		line->p_a.x = (((int)cub.player.px / width) * width) + width;
	}
	else
	{
		line->p_a.x = cub.player.px;
		line->p_a.y = cub.player.py;
		return (-42);
	}
	line->p_a.y = ((cub.player.px - line->p_a.x) * -tan_v) + cub.player.py;
	line->y_step = -line->x_step * -tan_v;
	return (cub.mmap->dof);
}

static void	get_wall_percent(t_cub cub, t_line *line, float pa, int dof)
{
	*line = get_line(get_player_point(cub.player.px, cub.player.py), line->p_a);
	line->dist *= cos((cub.player.pa - pa) * RADIAN);
	if (dof <= -42)
		line->dist = 0x7fffffff + 0.0;
	line->wall = get_orient_vert(cub.map, pa);
	line->wall_percent = ((int)line->p_b.y % line->wall->width);
	if (pa > 90 && pa < 270)
		line->wall_percent = ((line->wall->width - 1) - line->wall_percent);
	line->height = WINDOW_H;
	if (line->dist >= 1)
		line->height = ((cub.mmap->block_s * WINDOW_H) / line->dist);
	line->start = (WINDOW_H - line->height) / 2;
	line->stop = (WINDOW_H + line->height) / 2;
}

t_line	get_vert(t_cub cub, float pa)
{
	t_line	line;
	int		pos_x;
	int		pos_y;
	int		dof;

	dof = init_vert(cub, pa, &line);
	while (dof-- > 0)
	{
		pos_x = (line.p_a.x / cub.mmap->block_s);
		pos_y = (line.p_a.y / cub.mmap->block_s);
		if (pos_y >= cub.mmap->nb_line || pos_y < 0 || pos_x < 0
			|| pos_x >= (int)ft_strlen(cub.mmap->map[pos_y])
			|| !ft_is_in_str("NSEW0", cub.mmap->map[pos_y][pos_x]))
			break ;
		line.p_a.x += line.x_step;
		line.p_a.y += line.y_step;
	}
	get_wall_percent(cub, &line, pa, dof);
	return (line);
}
