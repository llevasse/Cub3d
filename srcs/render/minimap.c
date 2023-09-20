/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 00:28:00 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/20 15:51:39 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	paint_minimap_bg(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	if (!cub->win_ptr)
		return ;
	while (y < MINIMAP_HEIGHT)
	{
		x = 0;
		while (x < MINIMAP_WIDTH)
			img_pix_put(&cub->minimap->img, x++, y, cub->map->f_rgb);
		y++;
	}
}

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

	//paint_minimap_bg(cub);
	y = 0;
	map = cub->minimap;
	while (y < map->nb_line)
	{
		x = 0;
		len = ft_strlen(map->map[y]);
		while (x < len)
		{
			if (map->map[y][x] == '0')
				draw_square(map, x * map->block_w, y * map->block_h, cub->map->f_rgb);
			else if (map->map[y][x] == '1')
				draw_square(map, x * map->block_w, y * map->block_h, cub->map->c_rgb);
//			ft_printf("%d:%d : %c\n", x, y, map->map[y][x]);
			x++;
		}
		y++;
	}
}
