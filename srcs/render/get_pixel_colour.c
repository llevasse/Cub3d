/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_colour.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:45:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/26 23:20:24 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel_colour(t_img *img, int x, int y)
{
	char	*pixel;
	int		i;
	int		r;
	int		g;
	int		b;

	r = 1;
	g = 1;
	b = 1;
	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	if (img->endian != 0)
	{
		ft_printf("cc");
		r *= ((*pixel << i) & 0xFF) + 1;
		r *= ((*pixel << (i + 8)) & 0xFF) + 1;
		g *= ((*pixel << (i + 16)) & 0xFF) + 1;
		g *= ((*pixel << (i + 24)) & 0xFF) + 1;
		b *= ((*pixel << (i + 32)) & 0xFF) + 1;
		b *= ((*pixel << (i + 40)) & 0xFF) + 1; //reword this part later
	}
	else
	{
		b *= ((*(pixel++)) & 0xFF) + 1;
		g *= ((*(pixel++)) & 0xFF) + 1;
		r *= ((*(pixel++)) & 0xFF) + 1; //should work fine
	}
	return (((r - 1) * 256 * 256) + ((g - 1) * 256) + (b - 1));
}
