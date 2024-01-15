/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:25:17 by llevasse          #+#    #+#             */
/*   Updated: 2024/01/15 23:52:33 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cast	get_cast_data(t_cub *cub, float ca, int check_door)
{
	t_cast	cast;

	cast.h = get_horr(cub, ca);
	cast.v = get_vert(cub, ca);
	if (cast.h->line.dist < cast.v->line.dist)
		cast.line = cast.h->line;
	else
		cast.line = cast.v->line;
	if (cast.h->line.door.dist > cast.v->line.door.dist && !cast.v->line.dist)
		cast.line.door = cast.h->line.door;
	else if (cast.h->line.door.dist < cast.v->line.door.dist && !cast.h->line.dist)
		cast.line.door = cast.v->line.door;
	if (!check_door)
	{
		cast.line.door.cross_door = 0;
		cast.line.door.hit_door = 0;
	}
	cast.dist = cast.line.dist;
	return (cast);
}

int	get_texture_colour(t_line line, int height)
{
	int	y;
	int	x;

	y = (int)((((height * line.wall->height) / line.height)
				% line.wall->height) * line.wall->line_len);
	x = line.wall_percent * (line.wall->bpp / 8);
	return (*(int *)(line.wall->addr + y + x));
}

void	free_cast(t_cast cast)
{
	free(cast.h);
	cast.h = NULL;
	free(cast.v);
	cast.h = NULL;
}

t_door	*cast(t_cub *cub, t_cast c, int x)
{
	int		current;
	t_door	*door;

	current = 0;
	while (current < c.line.start)
		img_pix_put(&cub->img, x, current++, cub->c_rgb);
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
		img_pix_put(&cub->img, x, current++, cub->f_rgb);
	if (!c.line.door.cross_door && !c.line.door.hit_door)
		return (free_cast(c), NULL);
	door = malloc(sizeof(t_door));
	ft_add_garbage(&cub->garbage, door, cub);
	*door = c.line.door;
	return (free_cast(c), door);
}

int	is_pos_valid(t_cub cub, int x, int y)
{
	return (y < cub.mmap->nb_line && y >= 0
		&& x >= 0 && x < (int)ft_strlen(cub.mmap->map[y]));
}
