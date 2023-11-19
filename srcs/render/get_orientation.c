/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_orientation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:34:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/11/19 18:21:31 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img *get_orient_horr(t_map *map, int block_s, int x, int *side)
{
	if (x % block_s == 0){
		*side = WE;
		return (&map->west_img);
	}
	*side = EA;
	return (&map->east_img);
}

t_img *get_orient_vert(t_map *map, int block_s, int y, int *side)
{
	if (y % block_s == 0){
		*side = NO;
		return (&map->north_img);
	}
	*side = SO;
	return (&map->south_img);
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
