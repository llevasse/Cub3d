/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 00:28:00 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/24 15:53:07 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_cub *cub, int x, int y, int colour)
{
	int	y_b;
	int	x_b;

	y_b = 0;
	while (y + y_b < MMAP_H && y_b < cub->mmap->block_h)
	{
		x_b = 0;
		while (x + x_b < MMAP_W && x_b < cub->mmap->block_w)
			img_pix_put(&cub->img, x + x_b++, y + y_b, colour);
		y_b++;
	}
}

void	draw_player(t_cub *cub, int x, int y, int colour)
{
	int	y_b;
	int	x_b;

	y_b = 0;
	x -= cub->mmap->block_w/4;
	y -= cub->mmap->block_h/4;
	while (y + y_b < MMAP_H && y_b < cub->mmap->block_h/2)
	{
		x_b = 0;
		while (x + x_b < MMAP_W && x_b < cub->mmap->block_h/2)
			img_pix_put(&cub->img, x + x_b++, y + y_b, colour);
		y_b++;
	}
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
