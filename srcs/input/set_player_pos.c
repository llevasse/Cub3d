/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:36:13 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/11 13:55:44 by llevasse         ###   ########.fr       */
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
void	check_collision(t_cub *cub, int angle, float mini_offset, float offset)
{
	t_point	new_p;
	t_point	new_mini_p;
	int		x;
	int		y;
	int		block_s;

	get_player_new_pos(cub, angle, offset, &new_p);
	get_mini_player_new_pos(cub, angle, mini_offset, &new_mini_p);
	x = new_mini_p.x / cub->mmap->block_s;
	y = new_mini_p.y / cub->mmap->block_s;
	block_s = cub->mmap->block_s;
	if (y < 0 || y >= cub->mmap->nb_line ||
			x < 0 || x >= (int)ft_strlen(cub->mmap->map[y]))
		return ;
	if (ft_is_in_str("NSWE0", cub->mmap->map[(int)cub->mini_player.py / block_s][x]))
	{
		cub->mini_player.px = new_mini_p.x;
		cub->player.px = new_p.x;
	}
	if (ft_is_in_str("NSWE0", cub->mmap->map[y][(int)cub->mini_player.px / block_s]))
	{
		cub->mini_player.py = new_mini_p.y;
		cub->player.py = new_p.y;
	}
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

	if (dist < 0)		//unit of distance to prevent player from being inside the wall
		dist--;
	else
		dist++;
	new_angle = no_higher(cub->mini_player.pa + angle, 360, 0);
	p->x = cub->player.px + dist * cos(new_angle * RADIAN);
	p->y = cub->player.py + dist * sin(new_angle * RADIAN);
}

void	get_mini_player_new_pos(t_cub *cub, int angle, float dist, t_point *p)
{
	int		new_angle;

	if (dist < 0)		//unit of distance to prevent player from being inside the wall
		dist--;
	else
		dist++;
	new_angle = no_higher(cub->mini_player.pa + angle, 360, 0);
	p->x = cub->mini_player.px + dist * cos(new_angle * RADIAN);
	p->y = cub->mini_player.py + dist * sin(new_angle * RADIAN);
}
