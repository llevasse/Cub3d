/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:32:27 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/08 10:30:30 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_w_smaller_mov(t_cub *cub, int angle, float *offset)
{
	if (*offset >= 0)
		*offset -= 1;
	else
		*offset += 1;
	if (*offset == 0)
		return (1);
	return (check_collision(cub, angle, offset));
}

// return 1 if player collides with wall
int	check_collision(t_cub *cub, int angle, float *offset)
{
	t_point	new_p;
	int		px;
	int		py;
	int		merge;				// 1 unit of distance to prevent player from being inside the wall

	merge = 1;
	if (*offset < 0)
		merge = -1;
	get_player_new_pos(cub, angle, *offset + merge, &new_p);
	if (new_p.x < 0 || new_p.y < 0 || new_p.x > MMAP_S || new_p.y > MMAP_S)
		return (1);
	px = cub->player.px / cub->mmap->block_s;
	py = cub->player.py / cub->mmap->block_s;
	new_p.x /= cub->mmap->block_s;
	new_p.y /= cub->mmap->block_s;
	if (new_p.y >= cub->mmap->nb_line || new_p.y < 0 || new_p.x < 0 || new_p.x >= (int)ft_strlen(cub->mmap->map[(int)new_p.y]) \
		|| !ft_is_in_str("NSEW0", cub->mmap->map[(int)new_p.y][(int)new_p.x]))
	{
		if (py >= 0 && py < cub->mmap->nb_line && 
				new_p.x >= 0 && new_p.x < (int)ft_strlen(cub->mmap->map[py]) && ft_is_in_str("NSWE0", cub->mmap->map[py][(int)new_p.x]))
			cub->player.px = new_p.x;
		if (new_p.y >= 0 && new_p.y < cub->mmap->nb_line && 
				px >= 0 && px < (int)ft_strlen(cub->mmap->map[(int)new_p.y]) && ft_is_in_str("NSWE0", cub->mmap->map[(int)new_p.y][px]))
			cub->player.py = new_p.y;
	//	else
	//		return (check_w_smaller_mov(cub, angle, offset));
		return (1);
	}
	return (0);
}
