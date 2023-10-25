/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:04:28 by llevasse          #+#    #+#             */
/*   Updated: 2023/10/25 09:58:58 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_line	get_horr(t_cub cub, float pa, float ca);
t_line	get_vert(t_cub cub, float pa, float ca);

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
float	draw_line(t_cub cub, t_fov *fov, int colour, float ca)
{
	t_line		line;
	t_line		horr;
	t_line		vert;
	int			pos_x;
	int			pos_y;
	t_player	nb;

	line = get_line(get_player_point(cub.player.px, cub.player.py), fov->p);
	nb.px = cub.player.px;
	nb.py = cub.player.py;
	nb.pa = 0;
	while (nb.pa <= line.steps && nb.px >= 0 && nb.px <= WINDOW_W && \
			nb.py >= 0 && nb.py <= WINDOW_H)
	{
		if (ca >= (PLAYER_FOV / 2) - 0.5 && ca <= (PLAYER_FOV / 2) + 0.5){
//			printf("	x : %f | y : %f (pa : %f)\n", nb.px, nb.py, cub.player.pa);
		}
		pos_x = (nb.px / cub.mmap->block_s);
		pos_y = (nb.py / cub.mmap->block_s);
		if (pos_y >= cub.mmap->nb_line)
			break ;
		if (!ft_is_in_str("NSEW0", cub.mmap->map[pos_y][pos_x]))
			break ;
//		img_pix_put(&cub.img, (int)nb.px, (int)nb.py, colour);
		(void)colour;
		nb.px += line.x_step;
		nb.py += line.y_step;
		nb.pa += 1;
	}
	fov->p.x = nb.px;
	fov->p.y = nb.py;
	if (ca >= (PLAYER_FOV / 2) - 1 && ca <= (PLAYER_FOV / 2) + 1){
		ca = no_higher(fov->beg_angle + ca, 360, 0);
		horr = get_horr(cub, no_higher(cub.player.pa, 360, 0), ca);
		vert = get_vert(cub, no_higher(cub.player.pa, 360, 0), ca);
		printf("(pa %f)horr xb %f yb %f\n", cub.player.pa, horr.p_b.x, horr.p_b.y); // horr yb is right wall position in pixel
		printf("(pa %f)vert xb %f yb %f\n", cub.player.pa, vert.p_b.x, vert.p_b.y); // horr yb is right wall position in pixel
	}
	return (sqrt(pow(nb.py - cub.player.py, 2) + pow(nb.px - cub.player.px, 2)));
}

t_line	get_horr(t_cub cub, float pa, float ca)
{
	t_point	p;
	t_line	line;
	float	yo;
	float	xo;
	int		pos_x;
	int		pos_y;
	int		dof;
	float	Tan;

	Tan = 1.0/tan(pa * RADIAN);
	dof = 8;	//check during 8 square
	if (sin(pa * RADIAN) > 0.001)
	{
		yo = -cub.mmap->block_s;
		p.y = (int)((int)cub.player.py/cub.mmap->block_s) * cub.mmap->block_s - 0.0001;
	p.x = ((cub.player.py - p.y) * Tan) + cub.player.px;
	xo = -yo * Tan;
	}
	else if (sin(pa * RADIAN) < -0.001)
	{
		yo = cub.mmap->block_s;
		p.y = (int)((int)cub.player.py/cub.mmap->block_s) * cub.mmap->block_s + cub.mmap->block_s;
	p.x = ((cub.player.py - p.y) * Tan) + cub.player.px;
	xo = -yo * Tan;
	}
	else
	{
		p.x = cub.player.px;
		p.y = cub.player.py;
		yo = 0;
		xo = 0;
		dof = -42;
	}
	while (dof-- > 0){
		pos_x = (p.x / cub.mmap->block_s);
		pos_y = (p.y / cub.mmap->block_s);
		printf("%d %d (%f)\n", pos_x, pos_y, Tan);
		if (ca >= (PLAYER_FOV / 2) - 0.5 && ca <= (PLAYER_FOV / 2) + 0.5){
			printf("	horr xo %f	   yo %f\n", xo, yo);
			printf("	horr xb %d(%f) yb %d(%f)\n", pos_x, p.x, pos_y, p.y);
		}
		if (pos_y >= cub.mmap->nb_line || !ft_is_in_str("NSEW0", cub.mmap->map[pos_y][pos_x]))
			break ;
		img_pix_put(&cub.img, (int)p.x, (int)p.y, 0xff0000);
		p.x += xo;
		p.y += yo;
	}
	line = get_line(get_player_point(cub.player.px, cub.player.py), p);
	while (line.steps > 0 && line.p_a.x >= 0 && line.p_a.x <= WINDOW_W && \
			line.p_a.y >= 0 && line.p_a.y <= WINDOW_H)
	{
		pos_x = (line.p_a.x / cub.mmap->block_s);
		pos_y = (line.p_a.y / cub.mmap->block_s);
		if (pos_y >= cub.mmap->nb_line || pos_y < 0 || pos_x < 0 || !ft_is_in_str("NSEW0", cub.mmap->map[pos_y][pos_x]))
			break ;
		img_pix_put(&cub.img, (int)line.p_a.x, (int)line.p_a.y, 0xff0000);
		line.p_a.x += line.x_step;
		line.p_a.y += line.y_step;
		line.steps--;
	}
	line = get_line(get_player_point(cub.player.px, cub.player.py), p);
	if (dof == -42)
		line.dist = (float)0x7fffffff;
	return(line);
}

t_line	get_vert(t_cub cub, float pa, float ca)
{
	t_point	p;
	t_line	line;
	float	yo;
	float	xo;
	int		pos_x;
	int		pos_y;
	int		dof;

	if (pa <= 270 && pa >= 90)	// facing right
	{
		xo = cub.mmap->block_s;
		p.x = (int)(cub.player.px/cub.mmap->block_s) * cub.mmap->block_s + cub.mmap->block_s;
	}
	else						// facing left
	{
		xo = -cub.mmap->block_s;
		p.x = (int)(cub.player.px/cub.mmap->block_s) * cub.mmap->block_s - 1;
	}
	p.y = cub.player.py + ((cub.player.px - p.x) * tan(pa * RADIAN));
	yo = cub.mmap->block_s * tan(pa * RADIAN);
	dof = 8;	//check during 8 square
	while (dof-- > 0){
		pos_x = (p.x / cub.mmap->block_s);
		pos_y = (p.y / cub.mmap->block_s);
		if (ca >= (PLAYER_FOV / 2) - 0.5 && ca <= (PLAYER_FOV / 2) + 0.5){
			printf("	vert xo %f	   yo %f\n", xo, yo);
			printf("	vert xb %d(%f) yb %d(%f)\n", pos_x, p.x, pos_y, p.y);
		}
		if (pos_y >= cub.mmap->nb_line || pos_y < 0 || pos_x < 0 || !ft_is_in_str("NSEW0", cub.mmap->map[pos_y][pos_x]))
			break ;
		img_pix_put(&cub.img, (int)p.x, (int)p.y, 0x00ff00);
		p.x += xo;
		p.y += yo;
	}
	line = get_line(get_player_point(cub.player.px, cub.player.py), p);
	while (line.steps > 0 && line.p_a.x >= 0 && line.p_a.x <= WINDOW_W && \
			line.p_a.y >= 0 && line.p_a.y <= WINDOW_H)
	{
		pos_x = (line.p_a.x / cub.mmap->block_s);
		pos_y = (line.p_a.y / cub.mmap->block_s);
		if (pos_y >= cub.mmap->nb_line || !ft_is_in_str("NSEW0", cub.mmap->map[pos_y][pos_x]))
			break ;
		img_pix_put(&cub.img, (int)line.p_a.x, (int)line.p_a.y, 0x00ff00);
		line.p_a.x += line.x_step;
		line.p_a.y += line.y_step;
		line.steps--;
	}
	return (get_line(get_player_point(cub.player.px, cub.player.py), p));
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
