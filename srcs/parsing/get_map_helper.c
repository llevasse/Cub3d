/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 16:18:35 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/24 16:25:27 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_in_str("NSEW01CO\n\t \r", str[i]))
			return ((ft_putstr_fd(INVALID_MAP_LINE, 2)), 0);
		i++;
	}
	return (1);
}

int	search_door(t_cub *cub, t_map *map, char *s)
{
	ft_strsep(&s, " \t");
	if (!do_open(s, &map->door_img, 4, cub))
		return (0);
	map->door_img.addr = mlx_get_data_addr(map->door_img.mlx_img,
			&map->door_img.bpp, &map->door_img.line_len,
			&map->door_img.endian);
	return (1);
}

int	check_player_in_string(t_point *p, int y, int x, char *str)
{
	if (ft_is_in_str("NSEW", str[x]))
	{
		p->x = x;
		p->y = y;
		return (1);
	}
	return (0);
}

int	search_player_presence(t_map *map, t_cub *cub, char *s)
{
	t_point	p;
	int		y;
	int		x;
	int		nb;
	char	**split;

	split = ft_split(s, '\n');
	ft_add_garbage(&map->garbage, split);
	y = 0;
	nb = 0;
	while (y < get_tab_len(split))
	{
		ft_add_garbage(&map->garbage, split[y]);
		x = 0;
		while (split[y][x])
			nb += check_player_in_string(&p, y, x++, split[y]);
		y++;
	}
	if (nb > 1)
		return ((ft_putstr_fd(TMP, 2)), 0);
	if (nb == 0)
		return ((ft_putstr_fd(NO_PLAYER, 2)), 0);
	cub->mmap->map = split;
	return (check_closed(cub, p.x, p.y));
}
