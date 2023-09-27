/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:04:28 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/28 00:31:26 by llevasse         ###   ########.fr       */
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
	line.x_step = (float)line.dx / line.steps;
	line.y_step = (float)line.dy / line.steps;
	return (line);
}

// Fonction pour tracer une ligne avec la minilibX
int	draw_line(t_cub cub, int x2, int y2, int colour)
{
	int			dx;
	int			dy;
	int			steps;
	int			pix_colour;
	t_player	nb;

	dx = x2 - cub.player.px;		//get X distance of two points
	dy = y2 - cub.player.py;		//get Y distance of two points
	steps = abs(dy);
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	nb.pdx = (float) dx / steps;	//get steps for the X axis
	nb.pdy = (float) dy / steps;	//get steps for the Y axis
	nb.px = cub.player.px;
	nb.py = cub.player.py;
	nb.pa = 0;
	while (nb.pa <= steps && nb.px >= 0 && nb.px <= WINDOW_W && \
		   	nb.py >= 0 && nb.py <= WINDOW_H)
	{
		if (!((int)nb.px % cub.mmap->block_w) || !((int)nb.py % cub.mmap->block_h) || \
			!((int)nb.px % (cub.mmap->block_w-1)) || !((int)nb.py % (cub.mmap->block_h-1)) || \
			!((int)nb.px % (cub.mmap->block_w+1)) || !((int)nb.py % (cub.mmap->block_h+1)))
		{	//to yse get_pixel_colour() less
			pix_colour = get_pixel_colour(&cub.img, nb.px, nb.py);
			if (pix_colour != MMAP_RGB && pix_colour != PLAYER_RGB)
				break ;
		}
		img_pix_put(&cub.img, (int)nb.px, (int)nb.py, colour);
		nb.px += nb.pdx;
		nb.py += nb.pdy;
		nb.pa += 1;
	}
	return (sqrt(pow(nb.py - cub.player.py,2) + pow(nb.px - cub.player.px, 2)));
}

int	get_line_dist(t_cub cub, int x2, int y2)
{
	int			dx;
	int			dy;
	int			steps;
	int			pix_colour;
	t_player	nb;

	dx = x2 - cub.player.px;		//get X distance of two points
	dy = y2 - cub.player.py;		//get Y distance of two points
	steps = abs(dy);
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	nb.pdx = (float) dx / steps;	//get steps for the X axis
	nb.pdy = (float) dy / steps;	//get steps for the Y axis
	nb.px = cub.player.px;
	nb.py = cub.player.py;
	nb.pa = 0;
	while (nb.pa <= steps && nb.px >= 0 && nb.px <= WINDOW_W && \
		   	nb.py >= 0 && nb.py <= WINDOW_H)
	{
		if ((int)nb.px % cub.mmap->block_w == 0 || (int)nb.py % cub.mmap->block_h == 0)
		{	//to yse get_pixel_colour() less
			pix_colour = get_pixel_colour(&cub.img, nb.px, nb.py);
			if (pix_colour != MMAP_RGB && pix_colour != PLAYER_RGB)
				break ;
		}
		nb.px += nb.pdx;
		nb.py += nb.pdy;
		nb.pa += 1;
	}
	return (sqrt(pow(nb.py - cub.player.py,2) + pow(nb.px - cub.player.px, 2)));
}

void	drawRays3D(t_cub cub)
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
}
