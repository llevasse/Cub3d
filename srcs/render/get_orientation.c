/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_orientation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:34:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/11/04 19:08:29 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img *get_orientation(t_map *map, int block_s, int x, int y)
{
	if (y % block_s == 0)
		return (&map->north_img);
	if ((y + 1) % block_s == 0)
		return (&map->south_img);
	if (x % block_s == 0)
		return (&map->west_img);
	if ((x + 1) % block_s == 0)
		return (&map->east_img);
	return (&map->north_img);	
}

int	get_x(int x, int y, int block_s){
	if (y % block_s == 0)
		return (x%64);
	if ((y + 1) % block_s == 0)
		return (x%64);
	if (x % block_s == 0)
		return (y%64);
	if ((x + 1) % block_s == 0)
		return (y%64);
	return (0);
}
