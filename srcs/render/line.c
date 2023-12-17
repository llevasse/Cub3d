/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:04:28 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/17 11:32:53 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_line	get_line(t_point p_a, t_point p_b)
{
	t_line	line;

	line.p_a = p_a;
	line.p_b = p_b;
	line.dx = p_b.x - p_a.x;
	line.dy = p_b.y - p_a.y;
	line.steps = fabsf(line.dy);
	if (fabsf(line.dx) > fabsf(line.dy))
		line.steps = fabsf(line.dx);
	line.x_step = line.dx / line.steps;
	line.y_step = line.dy / line.steps;
	line.dist = sqrt(pow(line.dy, 2) + pow(line.dx, 2));
	return (line);
}

t_point	get_player_point(float x, float y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}

void	draw_line(t_cub cub, t_line line, int colour)
{
	while (line.steps > 0 && line.p_a.x >= 0 && line.p_a.x <= WINDOW_W && \
			line.p_a.y >= 0 && line.p_a.y <= WINDOW_H)
	{
		img_pix_put(&cub.img, (int)line.p_a.x, (int)line.p_a.y, colour);
		line.p_a.x += line.x_step;
		line.p_a.y += line.y_step;
		line.steps--;
	}
}
