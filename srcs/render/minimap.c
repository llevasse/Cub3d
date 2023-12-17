/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 00:28:00 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/17 15:28:42 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_cub *cub, int x, int y, int colour)
{
	int	y_b;
	int	x_b;

	y_b = 0;
	while (y_b < cub->mmap->block_s)
	{
		x_b = 0;
		while (x_b < cub->mmap->block_s)
			img_pix_put(&cub->img, x + x_b++, y + y_b, colour);
		y_b++;
	}
}

void	draw_minimap(t_cub *cub)
{
	int			x;
	int			y;
	int			len;
	int			tmp_x;
	int			tmp_y;

	tmp_y = (cub->player.py / cub->mmap->block_s) - MMAP_RANGE;
	tmp_x = (cub->player.px / cub->mmap->block_s) - MMAP_RANGE;
	y = tmp_y;
	while (y <= tmp_y + (MMAP_RANGE * 2))
	{
		x = tmp_x;
		if (y >= 0 && y < cub->mmap->nb_line)
		{
			len = ft_strlen(cub->mmap->map[y]);
			while (x < len && x <= tmp_x + (MMAP_RANGE * 2))
			{
				if (x >= 0 && ft_is_in_str("0NSEW", cub->mmap->map[y][x]))
					draw_square(cub, x * MMAP_BLOCK_S, y * MMAP_BLOCK_S, MMAP_RGB);
				else if (x >= 0 && cub->mmap->map[y][x] == '1')
					draw_square(cub, x * MMAP_BLOCK_S, y * MMAP_BLOCK_S, MMAP_W_RGB);
				x++;
			}
		}
		y++;
	}
}
