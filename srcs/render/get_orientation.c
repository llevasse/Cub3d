/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_orientation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:34:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/11/30 11:34:20 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*get_orient_horr(t_map *map, float ca, int *side)
{
	if (ca > 180 && ca < 360)
	{
		*side = NO;
		return (&map->north_img);
	}
	*side = SO;
	return (&map->south_img);
}

t_img	*get_orient_vert(t_map *map, float ca, int *side)
{
	if (ca > 90 && ca < 270)
	{
		*side = WE;
		return (&map->west_img);
	}
	*side = EA;
	return (&map->east_img);
}
