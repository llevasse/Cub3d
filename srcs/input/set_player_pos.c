/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:36:13 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/22 12:35:23 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	no_higher(int nb, int highest, int lowest)
{
	if (nb < lowest)
		return (no_higher(nb + highest, highest, lowest));
	if (nb > highest)
		return (no_higher(nb - highest, highest, lowest));
	return (nb);
}


/*@brief Set player new position given distance
 *@param *cub Pointer to cub
 *@param angle Should always pass 0 unless need an offset (like when going left or right)
 *@param distance Distance of which to put the new point from the old one
 */
void	set_player_new_pos(t_cub *cub, int angle, float distance)
{
	int		new_angle;

	new_angle = no_higher(cub->player.pa + angle, 360, 0);			//just make sure that the angle is not out of bound

	cub->player.px = cub->player.px + distance * cos(new_angle * RADIAN); 
	cub->player.py = cub->player.py + distance * sin(new_angle * RADIAN); 
}

/*@brief Get player new position given distance
 *@param *cub Pointer to cub
 *@param angle Should always pass 0 unless need an offset (like when going left or right)
 *@param distance Distance of which to put the new point from the old one
 *@param *x Pointer to a float var
 *@return Return value of new y pos
 */
float	get_player_new_pos(t_cub *cub, int angle, float distance, float *x)
{
	int		new_angle;

	new_angle = no_higher(cub->player.pa + angle, 360, 0);

	*x = cub->player.px + distance * cos(new_angle * RADIAN); 
	return (cub->player.py + distance * sin(new_angle * RADIAN)); 
}
