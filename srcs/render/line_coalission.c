/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_coalission.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:58:31 by llevasse          #+#    #+#             */
/*   Updated: 2023/10/29 14:37:46 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		init_horr(t_cub cub, float pa, t_line *line){
	float	Tan;

	printf("pa %f\n", pa);
	Tan = 1.0/tan(pa * RADIAN);
	if (pa > 180 && pa < 360) //if ray is facing up
	{
		line->y_step = cub.mmap->block_s;
		line->p_a.y =((int)cub.player.py/cub.mmap->block_s) * cub.mmap->block_s - 1;
		line->p_a.x = ((cub.player.py - line->p_a.y) * Tan + cub.player.px);
		line->x_step = -line->y_step * Tan;
		return (8);
	}
	else if (pa > 0 && pa < 180) // if ray is facing down
	{
		line->y_step = -cub.mmap->block_s;
		line->p_a.y =((int)cub.player.py/cub.mmap->block_s) * cub.mmap->block_s + cub.mmap->block_s;
		line->p_a.x = ((cub.player.py - line->p_a.y) * Tan + cub.player.px);
		line->x_step = -line->y_step * Tan;
		return (8);
	}
	else // if ray is facing straight up or down (pa == 180 || pa == 360 || pa == 0)
	{
		line->p_a.x = cub.player.px;
		line->p_a.y = cub.player.py;
		line->y_step = 0;
		line->x_step = 0;
		return (-42);
	}
}

t_line	get_horr(t_cub cub, float pa, float ca)
{
	t_line	line;
	int		pos_x;
	int		pos_y;
	int		dof;

	dof = init_horr(cub, pa, &line);	//check during 8 square
	printf("		beg point %f %f\n", line.p_a.x, line.p_a.y);
	while (dof-- > 0){
		pos_x = (line.p_a.x / cub.mmap->block_s);
		pos_y = (line.p_a.y / cub.mmap->block_s);
		if (ca >= (PLAYER_FOV / 2) - 1 && ca <= (PLAYER_FOV / 2) + 1){
//			printf("	horr xo %f	   yo %f(%d block size)\n", line.x_step, line.y_step, cub.mmap->block_s);
//			printf("	horr xb %d(%f) yb %d(%f)\n", pos_x, line.p_a.x, pos_y, line.p_a.y);
		}
		img_pix_put(&cub.img, (int)line.p_a.x, (int)line.p_a.y, 0xff0000);
		if (pos_y >= cub.mmap->nb_line || !ft_is_in_str("NSEW0", cub.mmap->map[pos_y][pos_x]))
			break ;
		line.p_a.x += line.x_step;
		line.p_a.y -= line.y_step;
	}
	line = get_line(get_player_point(cub.player.px, cub.player.py), line.p_a);
	if (dof == -42)
		line.dist = (float)0x7fffffff;
	return(line);
}


int		init_vert(t_cub cub, float pa, t_line *line){
	float	Tan;

	Tan = tan(pa * RADIAN);
	if (pa > 90 && pa < 270)	// if ray is facing left
	{
		line->x_step = -cub.mmap->block_s;
		line->p_a.x = (((int)cub.player.px/cub.mmap->block_s) * cub.mmap->block_s) - 1;
		line->p_a.y = ((cub.player.px - line->p_a.x) * -Tan) + cub.player.py;
		line->y_step = -line->x_step * -Tan;
		return (8);
	}
	else if (pa > 270 || pa < 90) // if ray is facing right
	{
		line->x_step = cub.mmap->block_s;
		line->p_a.x = (((int)cub.player.px/cub.mmap->block_s) * cub.mmap->block_s) + cub.mmap->block_s;
		line->p_a.y = ((cub.player.px - line->p_a.x) * -Tan) + cub.player.py;
		line->y_step = -line->x_step * -Tan;
		return (8);
	}
	else	//if ray is facing string left or right (pa == 90 || pa == 270)
	{
		line->p_a.x = cub.player.px;
		line->p_a.y = cub.player.py;
		line->y_step = 0;
		line->x_step = 0;
		return (-42);
	}
}

t_line	get_vert(t_cub cub, float pa, float ca)
{
	t_line	line;
	t_line	ret;
	int		pos_x;
	int		pos_y;
	int		dof;						//dof = depth of field

	dof = init_vert(cub, pa, &line);	//check during 8 square
	printf("		beg point %f %f\n", line.p_a.x, line.p_a.y);
	while (dof-- > 0){
		pos_x = (line.p_a.x / cub.mmap->block_s);
		pos_y = (line.p_a.y / cub.mmap->block_s);
		if (ca >= (PLAYER_FOV / 2) - 0.5 && ca <= (PLAYER_FOV / 2) + 0.5){
//			printf("	vert xo %f	   yo %f\n", line.x_step, line.y_step);
//			printf("	vert xb %d(%f) yb %d(%f)\n", pos_x, line.p_a.x, pos_y, line.p_a.y);
		}
		img_pix_put(&cub.img, (int)line.p_a.x, (int)line.p_a.y, 0x00ffff);
		img_pix_put(&cub.img, (int)line.p_a.x - 1, (int)line.p_a.y - 1, 0x00ffff);
		img_pix_put(&cub.img, (int)line.p_a.x - 2, (int)line.p_a.y - 2, 0x00ffff);
		img_pix_put(&cub.img, (int)line.p_a.x + 1, (int)line.p_a.y - 1, 0x00ffff);
		img_pix_put(&cub.img, (int)line.p_a.x + 2, (int)line.p_a.y - 2, 0x00ffff);
		img_pix_put(&cub.img, (int)line.p_a.x - 1, (int)line.p_a.y + 1, 0x00ffff);
		img_pix_put(&cub.img, (int)line.p_a.x - 2, (int)line.p_a.y + 2, 0x00ffff);
		img_pix_put(&cub.img, (int)line.p_a.x + 1, (int)line.p_a.y + 1, 0x00ffff);
		img_pix_put(&cub.img, (int)line.p_a.x + 2, (int)line.p_a.y + 2, 0x00ffff);
		if (pos_y >= cub.mmap->nb_line || pos_y < 0 || pos_x < 0 || !ft_is_in_str("NSEW0", cub.mmap->map[pos_y][pos_x]))
			break ;
		line.p_a.x += line.x_step;
		line.p_a.y += line.y_step;
	}
	line = get_line(get_player_point(cub.player.px, cub.player.py), line.p_a);
	ret = line;
/*	while (line.steps > 0 && line.p_a.x >= 0 && line.p_a.x <= WINDOW_W && \
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
	}*/
	if (dof == -42)
		ret.dist = (float)0x7fffffff;
	return (ret);
}


