/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_orientation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:34:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/10/17 15:17:39 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img get_orientation(t_map *map, int block_s, int x, int y)
{
	if (y % block_s == 0)
		return (map->north_img);
	if ((y + 1) % block_s == 0)
		return (map->south_img);
	if ((x + 1) % block_s == 0)
		return (map->east_img);
	if (x % block_s == 0)
		return (map->west_img);
	return (map->north_img);	
}

//NORTH STOP	: X134 Y128 = 128.0 / 16 = 8.0
//SOUTH	STOP	: X138 Y79 = (79.0 + 1) / 16 = 5.0
//EAST	STOP	: X111 Y103 = (111.0 + 1) / 16 = 7.0
//WEST	STOP	: X160 Y106	= 160.0 / 16 = 10.0