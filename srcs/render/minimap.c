/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 00:28:00 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/21 00:32:50 by llevasse         ###   ########.fr       */
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

void	draw_minimap(t_cub *cub)
{
	int			x;
	int			y;
	int			len;
	t_minimap	*map;

	y = 0;
	map = cub->minimap;
	img_pix_put(&map->img, 0, 0, 0x010203);
	get_pixel_colour(&map->img, 0, 0);
	while (y < map->nb_line)
	{
		x = 0;
		len = ft_strlen(map->map[y]);
		while (x < len)
		{
			if (ft_is_in_str("0NSEW", map->map[y][x]))
				draw_square(map, x * map->block_w, y * map->block_h, MINIMAP_RGB);
			else if (map->map[y][x] == '1')
				draw_square(map, x * map->block_w, y * map->block_h, MINIMAP_W_RGB);
			x++;
		}
		y++;
	}
	draw_square(map, cub->player.px, cub->player.py, PLAYER_RGB);
}

// return 1 if player collides with wall
int	check_collision(t_minimap *map, int px, int py)
{
	int	x;
	int	y;
	
	if (px < 0 || py < 0 || px > MINIMAP_WIDTH || py > MINIMAP_HEIGHT)
		return (0);
	x = px;
	y = py;
	while (x < px + map->block_w)
	{
		if (get_pixel_colour(&map->img, x++, y) == MINIMAP_W_RGB)
			return (1);
	}
	while (y < py + map->block_h)
	{
		if (get_pixel_colour(&map->img, x, y++) == MINIMAP_W_RGB)
			return (1);
	}
	x = px;
	y = py;
	while (y < py + map->block_h)
	{
		if (get_pixel_colour(&map->img, x, y++) == MINIMAP_W_RGB)
			return (1);
	}
	while (x < px + map->block_w)
	{
		if (get_pixel_colour(&map->img, x++, y) == MINIMAP_W_RGB)
			return (1);
	}
	return (0);
}
