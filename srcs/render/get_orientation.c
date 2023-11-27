/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_orientation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:34:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/11/27 13:53:36 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*get_orient_horr(t_map *map, int block_s, t_line v, t_cast *cast)
{
	// printf("x = %d\t block s = %d\n", v.p_b.x, block_s);
	if ((int)v.p_b.x % block_s == 0 && cast->dist > 0){
		cast->w_type = NO;
		return (&map->north_img);
	}
	cast->w_type = SO;
	return (&map->south_img);
}

t_img	*get_orient_vert(t_map *map, int block_s, t_line v, t_cast *cast)
{
	// printf("y = %d\t block s = %d\n", v.p_b.y, block_s);
	if ((int)v.p_b.x % block_s == 0 && cast->dist > 0){
		cast->w_type = EA;
		return (&map->east_img);
	}
	cast->w_type = WE;
	return (&map->west_img);
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
