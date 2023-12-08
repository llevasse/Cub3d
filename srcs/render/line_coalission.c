/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_coalission.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:58:31 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/08 12:20:55 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ray facing up pa > 180 && pa < 360
// ray facing down pa > 0 || pa < 180
//if ray is facing string up or down (pa == 90 || pa == 360 || pa == 0)
int	init_horr(t_cub cub, float pa, t_line *line)
{
	float	tan_v;
	int		block_s;

	tan_v = 1.0 / tan(pa * RADIAN);
	block_s = cub.mmap->block_s;
	if (pa > 180 && pa < 360)
	{
		line->y_step = block_s;
		line->p_a.y = ((int)cub.player.py / block_s) * block_s - 1;
	}
	else if (pa > 0 && pa < 180)
	{
		line->y_step = -block_s;
		line->p_a.y = ((int)cub.player.py / block_s) * block_s + block_s;
	}
	else
	{
		line->p_a.x = cub.player.px;
		line->p_a.y = cub.player.py;
		return (-42);
	}
	line->p_a.x = ((cub.player.py - line->p_a.y) * -tan_v + cub.player.px);
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
	while (dof > 0)
	{
		pos_x = (line.p_a.x / cub.mmap->block_s);
		pos_y = (line.p_a.y / cub.mmap->block_s);
		if (pos_y >= cub.mmap->nb_line || pos_y < 0 || pos_x < 0 || pos_x >= (int)ft_strlen(cub.mmap->map[pos_y]) \
			|| !ft_is_in_str("NSEW0", cub.mmap->map[pos_y][pos_x]))
			break ;
		line.p_a.x += line.x_step;
		line.p_a.y -= line.y_step;
		dof--;
	}
	line = get_line(get_player_point(cub.player.px, cub.player.py), line.p_a);
	if (dof == -42)
		line.dist = 0x7fffffff + 0.0;
	return (line);
}

// ray facing left pa > 90 && pa < 270
// ray facing right pa < 270 || pa < 90
//if ray is facing string left or right (pa == 90 || pa == 270)
int	init_vert(t_cub cub, float pa, t_line *line)
{
	float	tan_v;
	int		block_s;

	tan_v = tan(pa * RADIAN);
	block_s = cub.mmap->block_s;
	if (pa > 90 && pa < 270)
	{
		line->x_step = -block_s;
		line->p_a.x = (((int)cub.player.px / block_s) * block_s) - 1;
	}
	else if (pa > 270 || pa < 90)
	{
		line->x_step = block_s;
		line->p_a.x = (((int)cub.player.px / block_s) * block_s) + block_s;
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

//dof == depth of field
t_line	get_vert(t_cub cub, float pa)
{
	t_line	line;
	int		pos_x;
	int		pos_y;
	int		dof;

	dof = init_vert(cub, pa, &line);
	while (dof > 0)
	{
		pos_x = (line.p_a.x / cub.mmap->block_s);
		pos_y = (line.p_a.y / cub.mmap->block_s);
		if (pos_y >= cub.mmap->nb_line || pos_y < 0 || pos_x < 0 || pos_x >= (int)ft_strlen(cub.mmap->map[pos_y]) \
			|| !ft_is_in_str("NSEW0", cub.mmap->map[pos_y][pos_x]))
			break ;
		line.p_a.x += line.x_step;
		line.p_a.y += line.y_step;
		dof--;
	}
	line = get_line(get_player_point(cub.player.px, cub.player.py), line.p_a);
	if (dof == -42)
		line.dist = 0x7fffffff + 0.0;
	return (line);
}
