/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:25:17 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/23 19:59:42 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cast	get_cast_data(t_cub *cub, float ca)
{
	t_cast	cast;

	cast.h = get_horr(*cub, ca);
	cast.v = get_vert(*cub, ca);
	if (cast.h.dist < cast.v.dist)
		cast.line = cast.h;
	else
		cast.line = cast.v;
	if (cast.h.door.dist > cast.v.door.dist && !cast.v.dist)
	   cast.line.door = cast.h.door;
	else if (cast.h.door.dist < cast.v.door.dist && !cast.h.dist)
	   cast.line.door = cast.v.door;
	cast.dist = cast.line.dist;
	return (cast);
}

int	get_texture_colour(t_line line, int height)
{
	int	y;
	int	x;

	if (line.door.hit_door)
		return (DOOR_RGB);
	y = (int)((((height * line.wall->height) / line.height)
				% line.wall->height) * line.wall->line_len);
	x = line.wall_percent * (line.wall->bpp / 8);
	return (*(int *)(line.wall->addr + y + x));
}

t_door	*cast(t_cub *cub, t_cast c, int x)
{
	int		current;
	t_door	*door;

	current = 0;
	while (current < c.line.start)
		img_pix_put(&cub->img, x, current++, cub->map->c_rgb);
	current = 0;
	if (c.line.start < 0)
		current += -c.line.start;
	while (c.line.start + current < c.line.stop
		&& c.line.start + current < WINDOW_H)
	{
		img_pix_put(&cub->img, x, c.line.start + current,
			get_texture_colour(c.line, current));
		current++;
	}
	current = c.line.stop;
	while (current < WINDOW_H)
		img_pix_put(&cub->img, x, current++, cub->map->f_rgb);
	if (!c.line.door.cross_door && !c.line.door.hit_door)
		return (NULL);
	door = malloc(sizeof(t_door));
	ft_add_garbage(&cub->garbage, door);
	*door = c.line.door;
	return (door);
}
