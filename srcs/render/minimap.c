/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 00:28:00 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/17 16:00:42 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_cub *cub, int x, int y, int colour)
{
	int	y_b;
	int	x_b;

	y_b = 0;
	while (y_b < MMAP_BLOCK_S)
	{
		x_b = 0;
		while (x_b < MMAP_BLOCK_S)
			img_pix_put(&cub->img, x + x_b++, y + y_b, colour);
		y_b++;
	}
}

void	draw_minimap(t_cub *cub)
{
	t_point	p;
	t_point print;
	t_point	tmp;
	t_point	player;

	player.y = (int)(cub->player.py / cub->mmap->block_s);
	player.x = (int)(cub->player.px / cub->mmap->block_s);
	tmp.x = player.x - MMAP_RANGE;
	tmp.y = player.y - MMAP_RANGE;
	p.y = tmp.y;
	print.y = 1;
	while (p.y <= tmp.y + (MMAP_RANGE * 2) && p.y < cub->mmap->nb_line)
	{
		print.x = 1;
		p.x = tmp.x;
		if (p.y >= 0)
		{
			while (p.x < (int)ft_strlen(cub->mmap->map[(int)p.y]) && p.x <= tmp.x + (MMAP_RANGE * 2))
			{
				if (p.x >= 0 && ft_is_in_str("0NSEW", cub->mmap->map[(int)p.y][(int)p.x]))
					draw_square(cub, print.x * MMAP_BLOCK_S, print.y * MMAP_BLOCK_S, MMAP_RGB);
				else if (p.x >= 0 && cub->mmap->map[(int)p.y][(int)p.x] == '1')
					draw_square(cub, print.x * MMAP_BLOCK_S, print.y * MMAP_BLOCK_S, MMAP_W_RGB);
				p.x++;
				print.x++;
			}
		}
		p.y++;
		print.y++;
	}
	draw_square(cub, (MMAP_RANGE + 1) * MMAP_BLOCK_S, (MMAP_RANGE + 1) * MMAP_BLOCK_S, 0xFF0000);
}
