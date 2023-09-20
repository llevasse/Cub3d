/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:04:28 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/21 01:23:40 by llevasse         ###   ########.fr       */
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
