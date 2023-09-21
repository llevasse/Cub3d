/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:32:27 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/21 10:06:46 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_w_smaller_mov(t_cub *cub, int is_x, int *offset)
{
	if (*offset >= 0)
		*offset -= 1;
	else
		*offset += 1;
	return (check_collision(cub, is_x, offset));
}

// return 1 if player collides with wall
int	check_collision(t_cub *cub, int is_x, int *offset)
{
	int	x;
	int	y;
	
	x = cub->player.px;
	y = cub->player.py;
	if (*offset == 0)
		return (0);
	if (is_x)
		x += *offset;
	else
		y += *offset;
	if (x < 0 || y < 0 || x > MINIMAP_WIDTH || y > MINIMAP_HEIGHT)
		return (1);
	if (get_pixel_colour(&cub->minimap->img, x, y) == MINIMAP_W_RGB)
		return (check_w_smaller_mov(cub, is_x, offset));
	if (get_pixel_colour(&cub->minimap->img, x + cub->minimap->block_h/2, y) == MINIMAP_W_RGB)
		return (check_w_smaller_mov(cub, is_x, offset));
	if (get_pixel_colour(&cub->minimap->img, x, y + cub->minimap->block_h/2) == MINIMAP_W_RGB)
		return (check_w_smaller_mov(cub, is_x, offset));
	return (0);
}
