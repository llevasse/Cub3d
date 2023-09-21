/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:04:28 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/21 12:19:36 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_input(int keysym, t_cub *cub)
{
	int	offset;

	offset = PLAYER_OFFSET;
	if (keysym == XK_s && !check_collision(cub, 0, &offset))
		return (cub->player.py += offset);
	if (keysym == XK_d && !check_collision(cub, 1, &offset))
		return (cub->player.px += offset);
	offset = -PLAYER_OFFSET;
	if (keysym == XK_w && !check_collision(cub, 0, &offset))
		return (cub->player.py += offset);
	if (keysym == XK_a && !check_collision(cub, 1, &offset))
		return (cub->player.px += offset);
	if (keysym == XK_Escape)
		return (close_window(cub), offset);
	rotate_input(keysym, cub);
	return (0);
}

int	close_window(t_cub *cub)
{
	mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	if (cub->minimap->img.mlx_img)
		mlx_destroy_image(cub->mlx_ptr, cub->minimap->img.mlx_img);
	mlx_destroy_display(cub->mlx_ptr);
	free_garbage(cub->garbage);
	exit(0);
}


/*	rotate_input print dans le terminal l'angle
 d'inclinaison des que les arrows keys sont utilisées */

int	rotate_input(int keysym, t_cub *cub)
{
	int	offset;

	offset = PLAYER_OFFSET;
	if (keysym == XK_Left)
	{
		cub->player.pa -= 0.1;
		if (cub->player.pa < 0)
			cub->player.pa += 2 * PI;
		cub->player.pdx = cos(cub->player.pa) * 5;
		cub->player.pdy = sin(cub->player.pa) * 5;
		printf("%f ; %f\n", cub->player.pdx, cub->player.pdy);
	}
	if (keysym == XK_Right)
	{
		cub->player.pa += 0.1;
		if (cub->player.pa > 2 * PI)
			cub->player.pa -= 2 * PI;
		cub->player.pdx = cos(cub->player.pa) * 5;
		cub->player.pdy = sin(cub->player.pa) * 5;
		printf("%f ; %f\n", cub->player.pdx, cub->player.pdy);
	}
	offset = -PLAYER_OFFSET;
	if (keysym == XK_Up)
	{
		cub->player.px += cub->player.pdx;
		cub->player.py += cub->player.pdy;
		printf("%f ; %f\n", cub->player.pdx, cub->player.pdy);
	}
	if (keysym == XK_Down)
	{
		cub->player.px -= cub->player.pdx;
		cub->player.py -= cub->player.pdy;
		printf("%f ; %f\n", cub->player.pdx, cub->player.pdy);
	}
	return (0);
}
