/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:32:27 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/26 11:58:57 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_w_smaller_mov(t_cub *cub, int angle)
{
	return (check_collision(cub, angle));
}

// return 1 if player collides with wall
int	check_collision(t_cub *cub, int angle)
{
	t_point	new_p;
	float	px;
	float	py;

	get_player_new_pos(cub, angle, &new_p);
	if (new_p.x < 0 || new_p.y < 0 || new_p.x > MMAP_W || new_p.y > MMAP_H)
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
			return (check_w_smaller_mov(cub, angle));
		return (1);
	}
	return (0);
}
