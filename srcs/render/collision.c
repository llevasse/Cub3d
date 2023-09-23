/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:32:27 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/23 15:57:48 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_w_smaller_mov(t_cub *cub, int angle, float *offset)
{
	if (*offset >= 0)
		*offset -= 1;
	else
		*offset += 1;
	return (check_collision(cub, angle, offset));
}

// return 1 if player collides with wall
int	check_collision(t_cub *cub, int angle, float *offset)
{
	t_point	p;
	int		w;

	get_player_new_pos(cub, angle, *offset, &p);		//get new possition without setting them to the player
	if (*offset == 0)
		return (0);
	if (p.x < 0 || p.y < 0 || p.x > MINIMAP_WIDTH || p.y > MINIMAP_HEIGHT)
		return (1);
	w = cub->minimap->block_h / 4;
	if (get_pixel_colour(&cub->minimap->img, p.x - w, p.y - w) == MINIMAP_W_RGB)
		return (check_w_smaller_mov(cub, angle, offset));
	if (get_pixel_colour(&cub->minimap->img, p.x + w, p.y - w) == MINIMAP_W_RGB)
		return (check_w_smaller_mov(cub, angle, offset));
	if (get_pixel_colour(&cub->minimap->img, p.x - w, p.y + w) == MINIMAP_W_RGB)
		return (check_w_smaller_mov(cub, angle, offset));
	if (get_pixel_colour(&cub->minimap->img, p.x + w, p.y + w)== MINIMAP_W_RGB)
		return (check_w_smaller_mov(cub, angle, offset));
	return (0);
}
