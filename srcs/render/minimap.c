/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 00:28:00 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/22 21:51:26 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_minimap *map, int x, int y, int colour)
{
	int	y_b;
	int	x_b;

	y_b = 0;
	while (y + y_b < MINIMAP_HEIGHT && y_b < map->block_h)
	{
		x_b = 0;
		while (x + x_b < MINIMAP_WIDTH && x_b < map->block_w)
			img_pix_put(&map->img, x + x_b++, y + y_b, colour);
		y_b++;
	}
}

void	draw_player(t_minimap *map, int x, int y, int colour)
{
	int	y_b;
	int	x_b;

	y_b = 0;
	while (y + y_b < MINIMAP_HEIGHT && y_b < map->block_h/2)
	{
		x_b = 0;
		while (x + x_b < MINIMAP_WIDTH && x_b < map->block_h/2)
			img_pix_put(&map->img, x + x_b++, y + y_b, colour);
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
	map = cub->minimap;
	while (y < map->nb_line)
	{
		x = 0;
		len = ft_strlen(map->map[(int)y]);
		while (x < len)
		{
			if (ft_is_in_str("0NSEW", map->map[(int)y][(int)x]))
				draw_square(map, x * map->block_w, y * map->block_h, MINIMAP_RGB);
			else if (map->map[(int)y][(int)x] == '1')
				draw_square(map, x * map->block_w, y * map->block_h, MINIMAP_W_RGB);
			x++;
		}
		y++;
	}
	draw_fov(cub);
	draw_player(map, cub->player.px, cub->player.py, PLAYER_RGB);
}
