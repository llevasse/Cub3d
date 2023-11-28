/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_orientation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:34:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/11/28 15:15:00 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*get_orient_horr(t_map *map, int block_s, float dy, int *side)
{
	// printf("x = %d\t block s = %d\n", v.p_b.x, block_s);
	(void)block_s;
	if (dy > 0){
		*side  = NO;
		return (&map->north_img);
	}
	*side  = SO;
	return (&map->south_img);
}

t_img	*get_orient_vert(t_map *map, int block_s, float dx, int *side)
{
	// printf("y = %d\t block s = %d\n", v.p_b.y, block_s);
	(void)block_s;
	if (dx > 0){
		*side  = EA;
		return (&map->east_img);
	}
	*side  = WE;
	return (&map->west_img);
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

 NO = jaune
 SO = mur gris
 EA = brown
 WE = rouge

+========+
#        |		les murs '=' (NO) et '#' (WE) de la map rencontrent des problemes de raycasting avec la projection :
#        |				sur la mini map : les rayons ont des mauvaises lines bleu claires et bleus foncé.
#        |
+--------+
				TODO : fixe la condition de get_orient_horr pour ne pas avoir
					NO SO scindé selon l'axe gauche droite mais haut bas. 
*/


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
