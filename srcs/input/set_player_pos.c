/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:36:13 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/22 01:02:18 by llevasse         ###   ########.fr       */
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

void	set_player_new_pos(t_cub *cub, int angle, int distance)
{
	float	new_x;
	float	new_y;
	int		new_angle;

	new_angle = no_higher(cub->player.pa + angle, 360, 0);

	printf("angle : %d\n", new_angle);
	new_x = cub->player.px + distance * cos(new_angle * RADIAN); 
	new_y = cub->player.py + distance * sin(new_angle * RADIAN); 
	cub->player.px = new_x;
	cub->player.py = new_y;
}

float	get_player_new_pos(t_cub *cub, int angle, int distance, float *x)
{
	int		new_angle;

	new_angle = no_higher(cub->player.pa + angle, 360, 0);

	*x = cub->player.px + distance * cos(new_angle * RADIAN); 
	return (cub->player.py + distance * sin(new_angle * RADIAN)); 
}
