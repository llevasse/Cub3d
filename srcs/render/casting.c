/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:25:17 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/24 22:51:20 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast(t_cub *cub, int dist, int x)
{
	int	high_y;
	int	low_y;
	int	height;

	height = (WINDOW_H - dist) / 2;
	high_y = (WINDOW_H / 2) - height;
	low_y = (WINDOW_H / 2) + height;
	while (high_y < low_y)
	{
		if (get_pixel_colour(&cub->img, x, high_y) != MMAP_W_RGB && \
			get_pixel_colour(&cub->img, x, high_y) != MMAP_RGB)
			img_pix_put(&cub->img, x, high_y, 0x222222);
		high_y++;		
	}
}
