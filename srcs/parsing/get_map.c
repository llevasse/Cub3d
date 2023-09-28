/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:01:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/26 09:56:52 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	search_player_presence(t_map *map, t_cub *cub, char *s);

int	get_map(int map_fd, t_map *map, t_cub *cub)
{
	char	*str;
	char	*tmp;

	str = "";
	tmp = get_next_line(map_fd);
	while (tmp)
	{
		ft_add_garbage(&map->garbage, tmp);
		while (tmp && is_line_empty(tmp))
		{
			tmp = get_next_line(map_fd);
			if (tmp)
				ft_add_garbage(&map->garbage, tmp);
		}
		if (!tmp)
			break ;
		str = ft_strjoin(str, tmp);
		ft_add_garbage(&map->garbage, str);
		tmp = get_next_line(map_fd);
	}
	if (!search_player_presence(map, cub, str))
		return (0);
	return (1);
}

static int	search_player_presence(t_map *map, t_cub *cub, char *s)
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
		{
			if (ft_is_in_str("NSEW", split[y][x++]))
			{
				p.x = x - 1;
				p.y = y;
				nb++;
			}
		}
		y++;
	}
	if (nb > 1)
		return ((ft_putstr_fd(TMP, 2)), 0);
	if (nb == 0)
		return ((ft_putstr_fd(NO_PLAYER, 2)), 0);
	cub->mmap->map = split;
	return (check_closed(cub, p.x, p.y));
}
