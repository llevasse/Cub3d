/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:36:13 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/18 21:49:45 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	no_higher(float nb, float highest, float lowest)
{
	if (nb < lowest)
		return (no_higher(nb + highest, highest, lowest));
	if (nb > highest)
		return (no_higher(nb - highest, highest, lowest));
	return (nb);
}

// return 1 if player collides with wall
void	check_collision(t_cub *cub, int angle, float offset)
{
	t_point	new_p;
	int		x;
	int		y;
	int		block_s;

	get_player_new_pos(cub, angle, offset, &new_p);
	x = new_p.x / cub->mmap->block_s;
	y = new_p.y / cub->mmap->block_s;
	block_s = cub->mmap->block_s;
	if (y < 0 || y >= cub->mmap->nb_line
		|| x < 0 || x >= (int)ft_strlen(cub->mmap->map[y]))
		return ;
	if (ft_is_in_str("NSWE0", cub->mmap->map[(int)cub->player.py / block_s][x]))
		cub->player.px = new_p.x;
	if (ft_is_in_str("NSWE0", cub->mmap->map[y][(int)cub->player.px / block_s]))
		cub->player.py = new_p.y;
}

///@brief Get player new position given distance
///@param *cub Pointer to cub
///@param angle Should always pass 0 unless need an offset 
///(like when going left or right)
///@param distance Distance of which to put the new point from the old one
///@param *x Pointer to a float var
///@return Return value of new y pos

void	get_player_new_pos(t_cub *cub, int angle, float dist, t_point *p)
{
	int		new_angle;

	if (dist < 0)
		dist--;
	else
		dist++;
	new_angle = no_higher(cub->player.pa + angle, 360, 0);
	p->x = cub->player.px + dist * cos(new_angle * RADIAN);
	p->y = cub->player.py + dist * sin(new_angle * RADIAN);
}
