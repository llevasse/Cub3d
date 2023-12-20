/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:04:28 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/20 15:55:45 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_door(t_cub *cub);

int	handle_input(int keysym, t_cub *cub)
{
	float	offset;

	offset = 0.2 * cub->mmap->block_s;
	if (keysym == XK_w || keysym == XK_Up)
		check_collision(cub, 0, offset);
	if (keysym == XK_d)
		check_collision(cub, 90, offset);
	offset *= -1;
	if (keysym == XK_s || keysym == XK_Down)
		check_collision(cub, 0, offset);
	if (keysym == XK_a)
		check_collision(cub, 90, offset);
	if (keysym == XK_e)
		check_door(cub);
	if (keysym == XK_Escape)
		return (close_window(cub), 0);
	if (keysym == XK_Left)
		cub->player.pa -= PLAYER_R_OFFSET;
	if (keysym == XK_Right)
		cub->player.pa += PLAYER_R_OFFSET;
	return (0);
}

void	check_door(t_cub *cub)
{
	t_cast cast;
	cast = get_cast_data(cub, cub->player.pa);
	if (cast.line.door.cross_door || cast.line.door.hit_door)
	{
		if (cub->mmap->map[cast.line.door.y][cast.line.door.x] == 'C')
			cub->mmap->map[cast.line.door.y][cast.line.door.x] = 'O';
		if (cub->mmap->map[cast.line.door.y][cast.line.door.x] == 'O')
			cub->mmap->map[cast.line.door.y][cast.line.door.x] = 'C';
	}
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
