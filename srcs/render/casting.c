/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:25:17 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/24 23:08:21 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast(t_cub *cub, int dist, int x)
{
	int	high_y;
	int	low_y;
	int	height;

	height = (cub->mmap->block_h * WINDOW_H) / dist;
	high_y = (WINDOW_H / 2) - height;
	low_y = (WINDOW_H / 2) + height;
	if (high_y < 0)
		high_y = 0;
	if (low_y > WINDOW_H)
		low_y = WINDOW_H;
	while (high_y < low_y)
	{
		if (get_pixel_colour(&cub->img, x, high_y) != MMAP_W_RGB && \
			get_pixel_colour(&cub->img, x, high_y) != MMAP_RGB)
			img_pix_put(&cub->img, x, high_y, 0x222222);
		high_y++;		
	}
}
