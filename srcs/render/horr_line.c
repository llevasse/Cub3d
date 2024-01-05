/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horr_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:58:31 by llevasse          #+#    #+#             */
/*   Updated: 2024/01/05 22:40:12 by llevasse         ###   ########.fr       */
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
		line->p_a.y = (((int)cub.player.py / width) * width) - 0.001;
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

static void	get_wall_percent(t_cub cub, t_line *line, float pa, int dof)
{
	*line = get_line(get_player_point(cub.player.px, cub.player.py), line->p_a);
	line->dist *= cos((cub.player.pa - pa) * RADIAN);
	if (dof <= -42)
		line->dist = 0x7fffffff + 0.0;
	line->wall = &cub.south_img;
	if (pa > 180 && pa < 360)
		line->wall = &cub.north_img;
	line->wall_percent = ((int)line->p_b.x % line->wall->width);
	if (pa > 0 && pa < 180)
		line->wall_percent = ((line->wall->width - 1) - line->wall_percent);
	line->height = WINDOW_H;
	if (line->dist >= 1)
		line->height = ((cub.mmap->block_s * WINDOW_H) / line->dist);
	line->start = (WINDOW_H - line->height) / 2;
	line->stop = (WINDOW_H + line->height) / 2;
}

static void	get_door_percent(t_cub cub, t_line *line, float pa, t_door *door)
{
	line->wall = &cub.door_img;
	line->wall_percent = ((int)line->p_b.x % line->wall->width);
	if (pa > 0 && pa < 180)
		line->wall_percent = ((line->wall->width - 1) - line->wall_percent);
	line->height = WINDOW_H;
	if (line->dist >= 1)
		line->height = ((cub.mmap->block_s * WINDOW_H) / line->dist);
	line->start = (WINDOW_H - line->height) / 2;
	line->stop = (WINDOW_H + line->height) / 2;
	*door = cross_door(cub, line->p_b.x, line->p_b.y, 1);
}

t_line	get_horr(t_cub cub, float pa)
{
	t_line	line;
	int		x;
	int		y;
	int		dof;
	t_door	d;

	dof = init_horr(cub, pa, &line);
	d = init_door();
	while (dof-- > 0)
	{
		x = (line.p_a.x / cub.mmap->block_s);
		y = (line.p_a.y / cub.mmap->block_s);
		if (!is_pos_valid(cub, x, y)
			|| !ft_is_in_str("NSEW0O", cub.mmap->map[y][x]))
			break ;
		if (cub.mmap->map[y][x] == 'O' && !d.cross_door)
			d = cross_door(cub, line.p_a.x, line.p_a.y, 0);
		line.p_a.x += line.x_step;
		line.p_a.y -= line.y_step;
	}
	get_wall_percent(cub, &line, pa, dof);
	if (is_pos_valid(cub, x, y) && cub.mmap->map[y][x] == 'C' && !d.cross_door)
		get_door_percent(cub, &line, pa, &d);
	line.door = d;
	return (line);
}
