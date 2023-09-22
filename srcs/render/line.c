/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:04:28 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/22 20:21:40 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Fonction pour tracer une ligne avec la minilibX
void	draw_line(t_cub cub, int x2, int y2)
{
	int			dx;
	int			dy;
	int			steps;
	t_player	nb;

	dx = x2 - cub.player.px;
	dy = y2 - cub.player.py;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	nb.pdx = (float) dx / steps;
	nb.pdy = (float) dy / steps;
	nb.px = cub.player.px;
	nb.py = cub.player.py;
	nb.pa = 0;
	while(nb.pa <= steps + 100 && (get_pixel_colour(&cub.minimap->img, nb.px, nb.py) == MINIMAP_RGB || \
				get_pixel_colour(&cub.minimap->img, nb.px, nb.py) == 0x222222))
	{
		img_pix_put(&cub.minimap->img, (int)nb.px, (int)nb.py, 0x222222);
		nb.px += nb.pdx;
		nb.py += nb.pdy;
		nb.pa += 1;
	}
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
			var.yo = -cub.minimap->maps;
			var.xo = -var.yo * var.aTan;
		}
		if (var.ra < PI)
		{
			var.ry = (((int)cub.player.py >> 6) << 6) + cub.minimap->maps;
			var.rx = (cub.player.py - var.ry) * var.aTan + cub.player.px;
			var.yo = cub.minimap->maps;
			var.xo = -var.yo * var.aTan;
		}
		if (var.ra == 0 || var.ra == PI)
		{
			var.rx = cub.player.px;
			var.ry = cub.player.py;
			var.dof = cub.minimap->mapy;
		}
		printf("raPI\n");
		while (var.dof < cub.minimap->mapy)
		{
			var.mx = (int)(var.rx) >> 6;
			var.my = (int)(var.ry) >> 6;
			printf("my = %d\n", cub.minimap->mapx[var.dof]);
			var.mp = var.my * cub.minimap->mapx[var.dof] + var.mx;
			if ((var.mp < cub.minimap->maps) && (cub.minimap->map[var.dof][var.mp % cub.minimap->mapy] == '1'))
				var.dof = cub.minimap->mapy;
			else
			{
				var.rx += var.xo;
				var.ry += var.yo;
				var.dof += 1;
			}
		}
		draw_line(cub, var.rx, var.ry);
		var.r++;
	}
}
