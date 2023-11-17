/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_orientation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:34:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/11/17 13:42:45 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img *get_orient(t_map *map, int block_s, int x, int y)
{
	if (y % block_s == 0) //&& ((y + 1) % block_s != 0) && (x % block_s != 0) && ((x + 1) % block_s != 0))
		return (&map->north_img);
	if ((y + 1) % block_s == 0) //&& (y % block_s != 0) && (x % block_s != 0) && ((x + 1) % block_s != 0))
		return (&map->south_img);
	if (x % block_s == 0) //&& (y % block_s != 0) && ((y + 1) % block_s != 0) && ((x + 1) % block_s != 0))
		return (&map->west_img);
	if ((x + 1) % block_s == 0) //&& (y % block_s != 0) && ((y + 1) % block_s != 0) && (x % block_s != 0))
		return (&map->east_img);
	return (NULL);
}

/*
transformer la fonction get_orient en 2 pour vert et horr
(on l'appelerai depuis get_horr et get_vert avec une variable
side qui servirait de boolean pour auguiller la fonction get_orient).
*/

int	get_x(int x, int y, int block_s){
	if (y % block_s == 0)
		return (x % 64);
	if ((y + 1) % block_s == 0)
		return (x % 64);
	if (x % block_s == 0)
		return (y % 64);
	if ((x + 1) % block_s == 0)
		return (y % 64);
	return (0);
}


/*
if (y % block_s == 0 && ((x + 1) % block_s != 0 && (y + 1) % block_s != 0 && x % block_s != 0))
		return (&map->south_img);
	if ((y + 1) % block_s == 0 && ((x + 1) % block_s != 0 && y % block_s != 0 && x % block_s != 0))
		return (&map->north_img);
	if (x % block_s == 0 && ((x + 1) % block_s != 0 && y % block_s != 0 && (y + 1) % block_s != 0))
		return (&map->east_img);
	if ((x + 1) % block_s == 0 && y % block_s != 0 && (y + 1) % block_s != 0 && (x % block_s != 0))
		return (&map->west_img);
	return (NULL);*/
