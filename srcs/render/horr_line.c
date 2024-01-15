/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horr_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:58:31 by llevasse          #+#    #+#             */
/*   Updated: 2024/01/15 22:55:49 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ray facing up pa > 180 && pa < 360
// ray facing down pa > 0 || pa < 180
//if ray is facing string up or down (pa == 90 || pa == 360 || pa == 0)
t_ray	init_horr(t_cub cub, float pa)
{
	float	tan_v;
	int		width;
	t_ray	ray;

	tan_v = 1.0 / tan(pa * RADIAN);
	width = cub.mmap->block_s;
	if (pa > 180 && pa < 360)
	{
		ray.line.y_step = width;
		ray.line.p_a.y = (((int)cub.player.py / width) * width) - 0.0001;
	}
	else if (pa > 0 && pa < 180)
	{
		ray.line.y_step = -width;
		ray.line.p_a.y = (((int)cub.player.py / width) * width) + width;
	}
	else
	{
		ray.line.p_a.x = cub.player.px;
		ray.line.p_a.y = cub.player.py;
		ray.dof = -42;
	}
	ray.line.p_a.x = ((cub.player.py - ray.line.p_a.y) * -tan_v) + cub.player.px;
	ray.line.x_step = -ray.line.y_step * tan_v;
	ray.dof = cub.mmap->dof;
	return (ray);
}

static void	get_wall_percent(t_cub *cub, t_line *line, float pa, int dof)
{
	*line = get_line(get_player_point(cub->player.px, cub->player.py),
			line->p_a, cub, pa);
	if (dof <= -42)
		line->dist = 0x7fffffff + 0.0;
	line->wall = &cub->south_img;
	if (pa > 180 && pa < 360)
		line->wall = &cub->north_img;
	line->wall_percent = ((int)line->p_b.x % line->wall->width);
	if (pa > 0 && pa < 180)
		line->wall_percent = ((line->wall->width - 1) - line->wall_percent);
	line->height = WINDOW_H;
	if (line->dist >= 1)
		line->height = ((cub->mmap->block_s * WINDOW_H) / line->dist);
	line->start = (WINDOW_H - line->height) / 2;
	line->stop = (WINDOW_H + line->height) / 2;
}

static void	get_door_percent(t_cub *cub, t_line *line, float pa, t_door *door)
{
	line->wall = &cub->door_img;
	line->wall_percent = ((int)line->p_b.x % line->wall->width);
	if (pa > 0 && pa < 180)
		line->wall_percent = ((line->wall->width - 1) - line->wall_percent);
	line->height = WINDOW_H;
	if (line->dist >= 1)
		line->height = ((cub->mmap->block_s * WINDOW_H) / line->dist);
	line->start = (WINDOW_H - line->height) / 2;
	line->stop = (WINDOW_H + line->height) / 2;
	*door = cross_door(*cub, line->p_b.x, line->p_b.y, 1);
}

t_line	get_horr(t_cub *cub, float pa)
{
	t_ray	ray;

	ray = init_horr(*cub, pa);
	ray.d = init_door();
	while (ray.dof-- > 0)
	{
		ray.p.x = (int)(ray.line.p_a.x / cub->mmap->block_s);
		ray.p.y = (int)(ray.line.p_a.y / cub->mmap->block_s);
		if (!is_pos_valid(*cub, (int)ray.p.x, (int)ray.p.y)
			|| !ft_is_in_str("NSEW0O", cub->mmap->map[(int)ray.p.y][(int)ray.p.x]))
			break ;
		if (cub->mmap->map[(int)ray.p.y][(int)ray.p.x] == 'O' && !ray.d.cross_door)
			ray.d = cross_door(*cub, ray.line.p_a.x, ray.line.p_a.y, 0);
		ray.line.p_a.x += ray.line.x_step;
		ray.line.p_a.y -= ray.line.y_step;
	}
	get_wall_percent(cub, &ray.line, pa, ray.dof);
	if (is_pos_valid(*cub, (int)ray.p.x, (int)ray.p.y)
		&& cub->mmap->map[(int)ray.p.y][(int)ray.p.x] == 'C' && !ray.d.cross_door)
		get_door_percent(cub, &ray.line, pa, &ray.d);
	ray.line.door = ray.d;
	return (ray.line);
}
