/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 00:40:14 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/18 13:38:57 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render(t_cub *cub)
{
	float	x;
	float	ca;
	float	gained_angle;
	float	temp_x;

	ca = no_higher(cub->player.pa - (PLAYER_FOV / 2), 360, 0);
	x = 0;
	gained_angle = 0;
	while (gained_angle < PLAYER_FOV)
	{
		temp_x = x + cub->column_width;
		while (x < temp_x && x < WINDOW_W)
			cast(cub, get_cast_data(cub, ca), x++);
		gained_angle += cub->field_step;
		ca = no_higher(ca + cub->field_step, 360, 0);
	}
	draw_minimap(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img.mlx_img, 0, 0);
	return (0);
}

void	img_pix_put(t_img *img, int x, int y, int colour)
{
	char	*pixel;
	int		i;

	if (x < 0 || x > WINDOW_W || y < 0 || y > WINDOW_H)
		return ;
	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel = (colour >> i) & 0xFF;
		else
			*pixel = (colour >> (img->bpp - 8 - i)) & 0xff;
		pixel++;
		i -= 8;
	}
}
