/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:32:27 by llevasse          #+#    #+#             */
/*   Updated: 2023/10/13 22:53:06 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_w_smaller_mov(t_cub *cub, int angle, float *offset)
{
	if (*offset >= 0)
		*offset -= 1;
	else
		*offset += 1;
	if (*offset == 0)
		return (1);
	return (check_collision(cub, angle, offset));
}

// return 1 if player collides with wall
int	check_collision(t_cub *cub, int angle, float *offset)
{
	t_point	new_p;
	float	px;
	float	py;

	get_player_new_pos(cub, angle, *offset, &new_p);
	if (new_p.x < 0 || new_p.y < 0 || new_p.x > MMAP_S || new_p.y > MMAP_S)
		return (1);
	px = cub->player.px;
	py = cub->player.py;
	if (get_pixel_colour(&cub->img, new_p.x, new_p.y) == MMAP_W_RGB)
	{
		if (get_pixel_colour(&cub->img, new_p.x, py) != MMAP_W_RGB)
			cub->player.px = new_p.x;
		else if (get_pixel_colour(&cub->img, px, new_p.y) != MMAP_W_RGB)
			cub->player.py = new_p.y;
		else
			return (check_w_smaller_mov(cub, angle, offset));
		return (1);
	}
	return (0);
}
