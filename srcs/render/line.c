/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:04:28 by llevasse          #+#    #+#             */
/*   Updated: 2023/10/19 16:12:25 by llevasse         ###   ########.fr       */
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
	return (line);
}

t_point	get_player_point(float x, float y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}

t_point	get_distance_from_block_center(float x, float y, int block_s){
	float	center_x;
	float	center_y;
	t_point	diff;

	center_x = ((x / block_s) + 0.5) * block_s;
	center_y = ((y / block_s) + 0.5) * block_s;
	diff.x = fabsf(center_x - x);
	diff.y = fabsf(center_y - y);
	return (diff);
}

// Fonction pour tracer une ligne avec la minilibX
float	draw_line(t_cub cub, t_point *dest_p, int colour, float ca)
{
	t_line		line;
	int			pos_x;
	int			pos_y;
	t_player	nb;
	t_point		diff;

	line = get_line(get_player_point(cub.player.px, cub.player.py), *dest_p);
	nb.px = cub.player.px;
	nb.py = cub.player.py;
	diff = get_distance_from_block_center(nb.px, nb.py, cub.mmap->block_s);
	nb.pa = 0;
	while (nb.pa <= line.steps && nb.px >= 0 && nb.px <= WINDOW_W && \
			nb.py >= 0 && nb.py <= WINDOW_H)
	{
		if (ca >= (PLAYER_FOV / 2) - 0.5 && ca <= (PLAYER_FOV / 2) + 0.5)
			printf("	x : %f | y : %f\n", nb.px, nb.py);
		pos_x = (nb.px / cub.mmap->block_s);
		pos_y = (nb.py / cub.mmap->block_s);
		if (pos_y >= cub.mmap->nb_line)
			break ;
		if (!ft_is_in_str("NSEW0", cub.mmap->map[pos_y][pos_x]))
			break ;
		img_pix_put(&cub.img, (int)nb.px, (int)nb.py, colour);
		nb.px += line.x_step;
		nb.py += line.y_step;
		nb.pa += 1;
	}
	dest_p->x = nb.px - diff.x;
	dest_p->y = nb.py - diff.y;
	return (sqrt(pow(nb.py - cub.player.py, 2) + pow(nb.px - cub.player.px, 2)));
}

int	get_line_dist(t_cub cub, t_point dest_p)
{
	t_line		line;
	int			pos_x;
	int			pos_y;
	t_player	nb;

	line = get_line(get_player_point(cub.player.px, cub.player.py), dest_p);
	nb.px = cub.player.px;
	nb.py = cub.player.py;
	nb.pa = 0;
	while (nb.pa <= line.steps && nb.px >= 0 && nb.px <= WINDOW_W && \
			nb.py >= 0 && nb.py <= WINDOW_H)
	{
		pos_x = (int)(nb.px / cub.mmap->block_s);
		pos_y = (int)(nb.py / cub.mmap->block_s);
		if (pos_y >= cub.mmap->nb_line)
			break ;
		if (!ft_is_in_str("NSEW0", cub.mmap->map[pos_y][pos_x]))
			break ;
		nb.px += line.x_step;
		nb.py += line.y_step;
		nb.pa += 1;
	}
	return (sqrt(pow(nb.py - cub.player.py, 2) + pow(nb.px - cub.player.px, 2)));
}

/*void	drawRays3D(t_cub cub)
{
	t_math	var;

	var.ra = cub.player.pa;
	var.r = 0;
	while (var.r < 1)
	{
		var.dof = 0;
		var.aTan = -1 / tan(var.ra);
		if (var.ra > PI)
		{
			printf("ry = %f\n", var.ry);
			var.ry = (((int)cub.player.py >> 6) << 6) - 0.0001;
			printf("ry = %f\n", var.ry);
			var.rx = (cub.player.py - var.ry) * var.aTan + cub.player.px;
			var.yo = -cub.mmap->maps;
			var.xo = -var.yo * var.aTan;
		}
		if (var.ra < PI)
		{
			var.ry = (((int)cub.player.py >> 6) << 6) + cub.mmap->maps;
			var.rx = (cub.player.py - var.ry) * var.aTan + cub.player.px;
			var.yo = cub.mmap->maps;
			var.xo = -var.yo * var.aTan;
		}
		if (var.ra == 0 || var.ra == PI)
		{
			var.rx = cub.player.px;
			var.ry = cub.player.py;
			var.dof = cub.mmap->mapy;
		}
		printf("raPI\n");
		while (var.dof < cub.mmap->mapy)
		{
			var.mx = (int)(var.rx) >> 6;
			var.my = (int)(var.ry) >> 6;
			printf("my = %d\n", cub.mmap->mapx[var.dof]);
			var.mp = var.my * cub.mmap->mapx[var.dof] + var.mx;
			if ((var.mp < cub.mmap->maps) && (cub.mmap->map[var.dof][var.mp % cub.mmap->mapy] == '1'))
				var.dof = cub.mmap->mapy;
			else
			{
				var.rx += var.xo;
				var.ry += var.yo;
				var.dof += 1;
			}
		}
		draw_line(cub, var.rx, var.ry, 0x222222);
		var.r++;
	}
}*/
