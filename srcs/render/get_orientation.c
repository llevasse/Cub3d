/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_orientation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:34:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/17 11:38:37 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*get_orient_horr(t_map *map, float ca)
{
	if (ca > 180 && ca < 360)
		return (&map->north_img);
	return (&map->south_img);
}

t_img	*get_orient_vert(t_map *map, float ca)
{
	if (ca > 90 && ca < 270)
		return (&map->west_img);
	return (&map->east_img);
}
