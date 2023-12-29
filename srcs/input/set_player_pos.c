/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:36:13 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/29 17:06:42 by llevasse         ###   ########.fr       */
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
void	check_collision(t_cub *cub, int angle, float h_offset, float v_offset)
{
	t_point	new_p;
	int		x;
	int		y;

	new_p = get_player_new_pos(cub, angle, h_offset, v_offset);
	x = new_p.x / cub->avg_h_block_s;
	y = new_p.y / cub->avg_v_block_s;
	if (y < 0 || y >= cub->mmap->nb_line
		|| x < 0 || x >= (int)ft_strlen(cub->mmap->map[y]))
		return ;
	if (ft_is_in_str("NSWE0O",
			cub->mmap->map[(int)(cub->player.py / cub->avg_v_block_s)][x]))
		cub->player.px = new_p.x;
	if (ft_is_in_str("NSWE0O",
			cub->mmap->map[y][(int)(cub->player.px / cub->avg_h_block_s)]))
		cub->player.py = new_p.y;
}

///@brief Get player new position given distance
///@param *cub Pointer to cub
///@param angle Should always pass 0 unless need an offset 
///(like when going left or right)
///@param distance Distance of which to put the new point from the old one
///@param *x Pointer to a float var
///@return Return value of new y pos

t_point	get_player_new_pos(t_cub *cub, int angle, float h_dist, float v_dist)
{
	int		new_angle;
	t_point	p;

	if (h_dist < 0)
		h_dist--;
	else
		h_dist++;
	if (v_dist < 0)
		v_dist--;
	else
		v_dist++;
	new_angle = no_higher(cub->player.pa + angle, 360, 0);
	p.x = cub->player.px + h_dist * cos(new_angle * RADIAN);
	p.y = cub->player.py + v_dist * sin(new_angle * RADIAN);
	return (p);
}
