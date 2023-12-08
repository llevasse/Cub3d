/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_colour.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:45:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/08 12:16:42 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel_colour(t_img *img, int x, int y)
{
	char	*pixel;
	int		r;
	int		g;
	int		b;

	r = 1;
	g = 1;
	b = 1;
	if (!img)
		return ((((r - 1) * 256 * 256) + ((g - 1) * 256) + (b - 1)));
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));		//bpp ?
	if (img->endian != 0)
	{
		r *= ((*(pixel++)) & 0xFF) + 1;
		g *= ((*(pixel++)) & 0xFF) + 1;
		b *= ((*(pixel++)) & 0xFF) + 1;
	}
	else
	{
		b *= ((*(pixel++)) & 0xFF) + 1;
		g *= ((*(pixel++)) & 0xFF) + 1;
		r *= ((*(pixel++)) & 0xFF) + 1;
	}
	return (((r - 1) * 256 * 256) + ((g - 1) * 256) + (b - 1));
}
