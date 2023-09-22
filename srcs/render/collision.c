/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:32:27 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/22 11:34:46 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_w_smaller_mov(t_cub *cub, int angle, int *offset)
{
	if (*offset >= 0)
		*offset -= 1;
	else
		*offset += 1;
	return (check_collision(cub, angle, offset));
}

// return 1 if player collides with wall
int	check_collision(t_cub *cub, int angle, int *offset)
{
	float	x;
	float	y;

	x = 0;	
	y = get_player_new_pos(cub, angle, *offset, &x);		//get new possition without setting them to the player
	if (*offset == 0)
		return (0);
	if (x < 0 || y < 0 || x > MINIMAP_WIDTH || y > MINIMAP_HEIGHT)
		return (1);
	if (get_pixel_colour(&cub->minimap->img, x, y) == MINIMAP_W_RGB)
		return (check_w_smaller_mov(cub, angle, offset));
	if (get_pixel_colour(&cub->minimap->img, x + cub->minimap->block_h/2, y) == MINIMAP_W_RGB)
		return (check_w_smaller_mov(cub, angle, offset));
	if (get_pixel_colour(&cub->minimap->img, x, y + cub->minimap->block_h/2) == MINIMAP_W_RGB)
		return (check_w_smaller_mov(cub, angle, offset));
	return (0);
}
