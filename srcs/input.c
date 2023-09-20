/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:04:28 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/21 00:04:46 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_input(int keysym, t_cub *cub)
{
	ft_printf("\n\n\n\n\n\n\n\n\n\n");
	if ((keysym == XK_W || keysym == XK_w) && !check_collision(cub->minimap, cub->player.px, cub->player.py - 5))
		return (cub->player.py -= 5);
	if ((keysym == XK_S || keysym == XK_s) && !check_collision(cub->minimap, cub->player.px, cub->player.py + 5))
		return (cub->player.py += 5);
	if ((keysym == XK_D || keysym == XK_d) && !check_collision(cub->minimap, cub->player.px + 5, cub->player.py))
		return (cub->player.px += 5);
	if ((keysym == XK_A || keysym == XK_a) && !check_collision(cub->minimap, cub->player.px - 5, cub->player.py))
		return (cub->player.px -= 5);
	if (keysym == XK_Escape)
		return (close_window(cub), 0);
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
