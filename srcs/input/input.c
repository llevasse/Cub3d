/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:04:28 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/10 15:03:33 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_input(int keysym, t_cub *cub)
{
	float	offset;
	float	mini_offset;

	mini_offset = 0.1 * cub->mmap->block_s;
	offset = 0.1 * cub->map->north_img.width;
	if (keysym == XK_w || keysym == XK_Up)
		check_collision(cub, 0, mini_offset, offset);
	if (keysym == XK_d)
		check_collision(cub, 90, mini_offset, offset);
	mini_offset *= -1;
	offset *= -1;
	if (keysym == XK_s || keysym == XK_Down)
		check_collision(cub, 0, mini_offset, offset);
	if (keysym == XK_a)
		check_collision(cub, 90, mini_offset, offset);
	if (keysym == XK_Escape)
		return (close_window(cub), 0);
	rotate_input(keysym, cub);
	return (0);
}

int	close_window(t_cub *cub)
{
	mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	close_walls(cub, cub->map);
	if (cub->img.mlx_img)
		mlx_destroy_image(cub->mlx_ptr, cub->img.mlx_img);
	mlx_destroy_display(cub->mlx_ptr);
	free_garbage(cub->garbage);
	exit(0);
}

/*	rotate_input print dans le terminal l'angle
 d'inclinaison des que les arrows keys sont utilisées */

int	rotate_input(int keysym, t_cub *cub)
{
	if (keysym == XK_Left)
		cub->mini_player.pa -= PLAYER_R_OFFSET;
	if (keysym == XK_Right)
		cub->mini_player.pa += PLAYER_R_OFFSET;
	return (0);
}
