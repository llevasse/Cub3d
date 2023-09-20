/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_colour.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:45:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/20 23:12:56 by llevasse         ###   ########.fr       */
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
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	if (img->endian != 0)
	{
		r *= ((*pixel << (img->bpp - 8 - (img->bpp - 8))) & 0xFF) + 1;
		r *= ((*pixel << (img->bpp - 8 - img->bpp) & 0xFF)) + 1;
		g *= ((*pixel << (img->bpp - 8 - (img->bpp + 8))) & 0xFF) + 1;
		g *= ((*pixel << (img->bpp - 8 - (img->bpp + 16))) & 0xFF) + 1;
		b *= ((*pixel << (img->bpp - 8 - (img->bpp + 24))) & 0xFF) + 1;
		b *= ((*pixel << (img->bpp - 8 - (img->bpp + 32))) & 0xFF) + 1;
	}
	else
	{
		b *= ((*pixel << (img->bpp - 8 - (img->bpp - 8))) & 0xFF) + 1;
		b *= ((*pixel << (img->bpp - 8 - img->bpp) & 0xFF)) + 1;
		g *= ((*pixel << (img->bpp - 8 - (img->bpp + 8))) & 0xFF) + 1;
		g *= ((*pixel << (img->bpp - 8 - (img->bpp + 16))) & 0xFF) + 1;
		r *= ((*pixel << (img->bpp - 8 - (img->bpp + 24))) & 0xFF) + 1;
		r *= ((*pixel << (img->bpp - 8 - (img->bpp + 32))) & 0xFF) + 1;
	}
	r--;
	g--;
	b--;
	ft_printf("0 : %i\n", img->bpp - 8 - (img->bpp - 8));
	ft_printf("1 : %i\n", img->bpp - 8 - (img->bpp));
	ft_printf("2 : %i\n", img->bpp - 8 - (img->bpp + 8));
	ft_printf("3 : %i\n", img->bpp - 8 - (img->bpp + 16));
	ft_printf("4 : %i\n", img->bpp - 8 - (img->bpp + 24));
	ft_printf("5 : %i\n", img->bpp - 8 - (img->bpp + 32));
	return (((r - 1) * 256 * 256) + ((g - 1) * 256) + (b - 1));
}
