/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 00:28:00 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/20 00:57:05 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	paint_minimap_bg(t_game *cub)
{
	int	x;
	int	y;

	y = 0;
	if (!cub->win_ptr)
		return ;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
			img_pix_put(&cub->img, x++, y, MINIMAP_RGB);
		y++;
	}
}
