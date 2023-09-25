/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:04:28 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/26 00:37:00 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_input(int keysym, t_cub *cub)
{
	float	offset;

	offset = 0.1 * cub->mmap->block_w;
	if ((keysym == XK_w || keysym == XK_Up) && !check_collision(cub, 0, &offset))
		set_player_new_pos(cub, 0, offset);
	if (keysym == XK_d && !check_collision(cub, 90, &offset))
		set_player_new_pos(cub, 90, offset);
	offset *= -1;
	if ((keysym == XK_s || keysym == XK_Down) && !check_collision(cub, 0, &offset))
		set_player_new_pos(cub, 0, offset);
	if (keysym == XK_a && !check_collision(cub, 90, &offset))
		set_player_new_pos(cub, 90, offset);
	if (keysym == XK_Escape)
		return (close_window(cub), offset);
	rotate_input(keysym, cub);
	return (0);
}

int	close_window(t_cub *cub)
{
	mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	if (cub->img.mlx_img)
		mlx_destroy_image(cub->mlx_ptr, cub->img.mlx_img);
	mlx_destroy_display(cub->mlx_ptr);
	close_walls(cub->map);
	free_garbage(cub->garbage);
	exit(0);
}


/*	rotate_input print dans le terminal l'angle
 d'inclinaison des que les arrows keys sont utilisées */

int	rotate_input(int keysym, t_cub *cub)
{
	if (keysym == XK_Left)
		cub->player.pa--;
	if (keysym == XK_Right)
		cub->player.pa++;
	return (0);
}
