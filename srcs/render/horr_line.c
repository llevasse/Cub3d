/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horr_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:58:31 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/15 15:25:29 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ray facing up pa > 180 && pa < 360
// ray facing down pa > 0 || pa < 180
//if ray is facing string up or down (pa == 90 || pa == 360 || pa == 0)
int	init_horr(t_cub cub, float pa, t_line *mini_line, t_line *line)
{
	float	tan_v;
	int		block_s;
	int		width;

	tan_v = 1.0 / tan(pa * RADIAN);
	block_s = cub.mmap->block_s;
	width = cub.map->north_img.width;
	if (pa > 180 && pa < 360)
	{
		line->y_step = width;
		mini_line->y_step = block_s;
		mini_line->p_a.y = (((int)cub.mini_player.py / block_s) * block_s) - 0.001;
		line->p_a.y = (((int)cub.player.py / width) * width) - 1;
	}
	else if (pa > 0 && pa < 180)
	{
		line->y_step = -width;
		mini_line->y_step = -block_s;
		mini_line->p_a.y = (((int)cub.mini_player.py / block_s) * block_s) + block_s;
		line->p_a.y = (((int)cub.player.py / width) * width) + width;
	}
	else
	{
		mini_line->p_a.x = cub.mini_player.px;
		mini_line->p_a.y = cub.mini_player.py;
		line->p_a.x = cub.player.px;
		line->p_a.y = cub.player.py;
		return (-42);
	}
	mini_line->p_a.x = ((cub.mini_player.py - mini_line->p_a.y) * -tan_v) + cub.mini_player.px;
	line->p_a.x = ((cub.player.py - line->p_a.y) * -tan_v) + cub.player.px;
	mini_line->x_step = -mini_line->y_step * tan_v;
	line->x_step = -line->y_step * tan_v;
	return (cub.mmap->dof);
}

t_line	get_horr(t_cub cub, float pa)
{
	t_line	mini_line;
	t_line	line;
	int		pos_x;
	int		pos_y;
	int		dof;

	dof = init_horr(cub, pa, &mini_line, &line);
	while (dof-- > 0)
	{
		pos_x = (line.p_a.x / cub.map->north_img.width);
		pos_y = (line.p_a.y / cub.map->north_img.width);
		if (pos_y >= cub.mmap->nb_line || pos_y < 0 || pos_x < 0 || pos_x >= (int)ft_strlen(cub.mmap->map[pos_y]) 
			|| !ft_is_in_str("NSEW0", cub.mmap->map[pos_y][pos_x]))
			break ;
		mini_line.p_a.x += mini_line.x_step;
		mini_line.p_a.y -= mini_line.y_step;
		line.p_a.x += line.x_step;
		line.p_a.y -= line.y_step;
	}
	mini_line = get_line(get_player_point(cub.mini_player.px, cub.mini_player.py), mini_line.p_a);
	if (dof <= -42)
		mini_line.dist = 0x7fffffff + 0.0;
	else
		mini_line.dist *= cos((cub.mini_player.pa - pa) * RADIAN);
	mini_line.wall = get_orient_horr(cub.map, pa, &mini_line.w_type);
	mini_line.wall_percent = ((int)line.p_a.x % mini_line.wall->width);
	if (pa > 0 && pa < 180)
		mini_line.wall_percent = mini_line.wall->width - mini_line.wall_percent;
	if (mini_line.dist >= 1)
		mini_line.height = ((cub.mmap->block_s * WINDOW_H) / mini_line.dist);
	mini_line.start = (WINDOW_H - mini_line.height) / 2;
	mini_line.stop = (WINDOW_H + mini_line.height) / 2;
	return (mini_line);
}
