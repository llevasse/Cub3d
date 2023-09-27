/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 00:28:00 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/28 00:29:08 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_cub *cub, int x, int y, int colour)
{
	int	y_b;
	int	x_b;

	y_b = 0;
	while (y_b <= cub->mmap->block_h)
	{
		x_b = 0;
		while (x_b <= cub->mmap->block_w)
		{
			printf("print pxl at (%d:%d)\n", x + x_b, y + y_b);
			printf("square size (%d:%d)\n", x_b, y_b);
			img_pix_put(&cub->img, x + x_b++, y + y_b, colour);
		}
		y_b++;
	}
//	exit(0);
}

void	draw_minimap(t_cub *cub)
{
	float		x;
	float		y;
	float		len;
	t_minimap	*map;

	y = 0;
	map = cub->mmap;
	while (y < map->nb_line)
	{
		x = 0;
		len = ft_strlen(map->map[(int)y]);
		while (x < len)
		{
			if (ft_is_in_str("0NSEW", map->map[(int)y][(int)x]))
				draw_square(cub, x * map->block_w, y * map->block_h, MMAP_RGB);
			else if (map->map[(int)y][(int)x] == '1')
				draw_square(cub, x * map->block_w, y * map->block_h, MMAP_W_RGB);
			x++;
		}
		y++;
	}
	draw_fov(cub);
}
