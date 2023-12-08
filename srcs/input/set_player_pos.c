/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:36:13 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/08 15:06:26 by llevasse         ###   ########.fr       */
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
int	check_collision(t_cub *cub, int angle, float offset)
{
	t_point	new_p;
	int		px;
	int		py;
	int		merge;				// 1 unit of distance to prevent player from being inside the wall

	merge = 1;
	if (offset < 0)
		merge = -1;
	get_player_new_pos(cub, angle, offset + merge, &new_p);
	if (new_p.x < 0 || new_p.y < 0 || new_p.x > MMAP_S || new_p.y > MMAP_S)
		return (1);
	px = cub->player.px / cub->mmap->block_s;
	py = cub->player.py / cub->mmap->block_s;
	new_p.x /= cub->mmap->block_s;
	new_p.y /= cub->mmap->block_s;
	if (py >= 0 && py < cub->mmap->nb_line && 
			new_p.x >= 0 && new_p.x < (int)ft_strlen(cub->mmap->map[py]) && ft_is_in_str("NSWE0", cub->mmap->map[py][(int)new_p.x]))
		cub->player.px = new_p.x * cub->mmap->block_s;
	if (new_p.y >= 0 && new_p.y < cub->mmap->nb_line && 
			px >= 0 && px < (int)ft_strlen(cub->mmap->map[(int)new_p.y]) && ft_is_in_str("NSWE0", cub->mmap->map[(int)new_p.y][px]))
		cub->player.py = new_p.y * cub->mmap->block_s;
	return (1);
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

	new_angle = no_higher(cub->player.pa + angle, 360, 0);
	p->x = cub->player.px + dist * cos(new_angle * RADIAN);
	p->y = cub->player.py + dist * sin(new_angle * RADIAN);
}
