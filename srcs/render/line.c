/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:04:28 by llevasse          #+#    #+#             */
/*   Updated: 2023/10/20 11:30:49 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	check_horizontal(t_cub cub, t_fov *fov, float ca);
t_point	check_vertical(t_cub cub, t_fov *fov, float ca);

t_line	get_line(t_point p_a, t_point p_b)
{
	t_line	line;

	line.p_a = p_a;
	line.p_b = p_b;
	line.dx = p_b.x - p_a.x;
	line.dy = p_b.y - p_a.y;
	line.steps = fabs(line.dy);
	if (fabs(line.dx) > fabs(line.dy))
		line.steps = fabs(line.dx);
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

t_point	get_distance_from_block_center(float x, float y, int block_s, int ca){
	float	center_x;
	float	center_y;
	t_point	diff;

	center_x = ((int)(x / block_s) + 0.5) * block_s;
	center_y = ((int)(y / block_s) + 0.5) * block_s;
	if (x > center_x)
		diff.x = x - center_x;
	else
		diff.x = center_x - x;
	if (y > center_y)
		diff.y = y - center_y;
	else
		diff.y = center_y - y;
	if (ca >= (PLAYER_FOV / 2) - 0.5 && ca <= (PLAYER_FOV / 2) + 0.5){
//		printf("	%f:%f (%f-%f)\n", center_x, center_y, diff.x, diff.y);
	}
	return (diff);
}

// Fonction pour tracer une ligne avec la minilibX
float	draw_line(t_cub cub, t_fov *fov, int colour, float ca)
{
	t_line		line;
	int			pos_x;
	int			pos_y;
	t_player	nb;
	t_point		diff;
	t_line		horr;
	t_line		vert;

	nb.px = cub.player.px;
	nb.py = cub.player.py;
	diff = get_distance_from_block_center(cub.player.px, cub.player.py, cub.mmap->block_s, ca);
	horr = get_line(get_player_point(nb.px - diff.x, nb.py - diff.y), check_horizontal(cub, fov, ca));
	vert = get_line(get_player_point(nb.px - diff.x, nb.py - diff.y), check_vertical(cub, fov, ca));
	line = get_line(get_player_point(nb.px - diff.x, nb.py - diff.y), fov->p);
	nb.pa = 0;
	while (nb.pa <= line.steps && nb.px >= 0 && nb.px <= WINDOW_W && \
			nb.py >= 0 && nb.py <= WINDOW_H)
	{
		if (ca >= (PLAYER_FOV / 2) - 0.5 && ca <= (PLAYER_FOV / 2) + 0.5){
			printf("	x : %f | y : %f\n", nb.px, nb.py);
			colour = 0x222222;
		}
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
	if (horr.dist < vert.dist){
		fov->p.x = horr.p_b.x;
		fov->p.y = horr.p_b.y;
		return (horr.dist);
	}
	fov->p.x = vert.p_b.x;
	fov->p.y = vert.p_b.y;
	return (vert.dist);
}

t_point	check_horizontal(t_cub cub, t_fov *fov, float ca)
{
	t_point	p;
	float	xo;
	float	yo;
	float	aTan;
	int		pos_x;
	int		pos_y;
	int		dof = 0;

	ca = no_higher(fov->beg_angle + ca, 360, 0);
	aTan = -1/tan(ca);
	if (ca > 180 && ca < 360)
	{
		p.y = (cub.player.py / cub.mmap->block_s) * cub.mmap->block_s - 1;
		yo = -cub.mmap->block_s;
		p.x = (cub.player.py - p.y) *aTan + cub.player.px;
		xo = -yo*aTan;
	}
	else
	{
		p.y = (cub.player.py / cub.mmap->block_s) * cub.mmap->block_s + cub.mmap->block_s;
		yo = cub.mmap->block_s;
		p.x = (cub.player.py - p.y) *aTan + cub.player.px;
		xo = -yo*aTan;
	}
	if (ca == 180 || ca == 360){
		p.x = cub.player.px;
		p.y = cub.player.py;
		dof = 8;
	}
	while (dof < 8){
		pos_x = (p.x / cub.mmap->block_s);
		pos_y = (p.y / cub.mmap->block_s);
		if (pos_y >= cub.mmap->nb_line || !ft_is_in_str("NSEW0", cub.mmap->map[pos_y][pos_x]))
			break ;
		p.x += xo;
		p.y += yo;
		dof++;
	}
	if (ca >= (fov->beg_angle + (PLAYER_FOV / 2)) - 0.5 && ca <= (fov->beg_angle + (PLAYER_FOV / 2)) + 0.5){
		printf("		horr : x : %f | y : %f\n", p.x, p.y);
	}
	return (p);
}

t_point	check_vertical(t_cub cub, t_fov *fov, float ca)
{
	t_point	p;
	float	xo;
	float	yo;
	float	nTan;
	int		pos_x;
	int		pos_y;
	int		dof = 0;

	ca = no_higher(fov->beg_angle + ca, 360, 0);
	nTan = -tan(ca);
	printf("\n");
	if (ca > 90 && ca < 270)
	{
		p.x = (cub.player.px / cub.mmap->block_s) * cub.mmap->block_s - 1;
		xo = -cub.mmap->block_s;
		p.y = (cub.player.px -  p.x) * nTan + cub.player.py;
		yo = -xo*nTan;
	}
	else
	{
		p.x = (cub.player.px / cub.mmap->block_s) * cub.mmap->block_s + cub.mmap->block_s;
		xo = cub.mmap->block_s;
		p.y = (cub.player.px - p.x) * nTan + cub.player.py;
		yo = -xo * nTan;
	}
	if (ca == 90 || ca == 270){
		p.x = cub.player.px;
		p.y = cub.player.py;
		dof = 8;
	}
	while (dof < 8){
		pos_x = (p.x / cub.mmap->block_s);
		pos_y = (p.y / cub.mmap->block_s);
		printf("check x%d(%f) y%d(%f) a%f\n", pos_x, p.x, pos_y, p.y, ca);
		if (pos_y >= cub.mmap->nb_line || !ft_is_in_str("NSEW0", cub.mmap->map[pos_y][pos_x]))
			break ;
		p.x += xo;
		p.y += yo;
		dof++;
	}
	if (ca >= (fov->beg_angle + (PLAYER_FOV / 2)) - 0.5 && ca <= (fov->beg_angle + (PLAYER_FOV / 2)) + 0.5){
		printf("		horr : x : %f | y : %f\n", p.x, p.y);
	}
	return (p);
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
