/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 00:40:14 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/28 00:15:09 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render(t_cub *cub)
{
	paint_bg(cub);
	draw_minimap(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img.mlx_img, 0, 0);
//	exit(0);
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

void	paint_bg(t_cub *cub)
{
	int	x;
	int	y;
	y = 0;
	if (!cub->win_ptr)
		return ;
	while (y < WINDOW_H / 2)
	{
		x = 0;
		while (x < WINDOW_W)
			img_pix_put(&cub->img, x++, y, cub->map->c_rgb);
		y++;
	}
	while (y < WINDOW_H)
	{
		x = 0;
		while (x < WINDOW_W)
			img_pix_put(&cub->img, x++, y, cub->map->f_rgb);
		y++;
	}
}
