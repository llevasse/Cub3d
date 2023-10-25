/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_coalission.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:58:31 by llevasse          #+#    #+#             */
/*   Updated: 2023/10/25 21:59:07 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		p.y =(cub.player.py/cub.mmap->block_s) * cub.mmap->block_s - 0.0001;
		p.x = ((cub.player.py - p.y) * Tan) + cub.player.px;
		xo = -yo * Tan;
	}
	else if (sin(pa * RADIAN) < -0.001)
	{
		yo = cub.mmap->block_s;
		p.y = (cub.player.py/cub.mmap->block_s) * cub.mmap->block_s + cub.mmap->block_s;
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
		img_pix_put(&cub.img, (int)p.x, (int)p.y, 0xff0000);
		if (pos_y >= cub.mmap->nb_line || !ft_is_in_str("NSEW0", cub.mmap->map[pos_y][pos_x]))
			break ;
		p.x += xo;
		p.y -= yo;
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
	float	Tan;

	Tan = tan(pa * RADIAN);
	dof = 8;	//check during 8 square
	if (cos(Tan) > 0.001)	// facing right
	{
		xo = cub.mmap->block_s;
		p.x = (int)(cub.player.px/cub.mmap->block_s) * cub.mmap->block_s + cub.mmap->block_s;
		p.y = cub.player.py + ((cub.player.px - p.x) * Tan);
		yo = -xo * Tan;
	}
	else if (cos(Tan) < -0.001)				// facing left
	{
		xo = -cub.mmap->block_s;
		p.x = (int)(cub.player.px/cub.mmap->block_s) * cub.mmap->block_s - 1;
		p.y = cub.player.py + ((cub.player.px - p.x) * Tan);
		yo = -xo * Tan;
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
		if (ca >= (PLAYER_FOV / 2) - 0.5 && ca <= (PLAYER_FOV / 2) + 0.5){
			printf("	vert xo %f	   yo %f\n", xo, yo);
			printf("	vert xb %d(%f) yb %d(%f)\n", pos_x, p.x, pos_y, p.y);
		}
		img_pix_put(&cub.img, (int)p.x, (int)p.y, 0x00ff00);
		if (pos_y >= cub.mmap->nb_line || pos_y < 0 || pos_x < 0 || !ft_is_in_str("NSEW0", cub.mmap->map[pos_y][pos_x]))
			break ;
		p.x -= xo;
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


