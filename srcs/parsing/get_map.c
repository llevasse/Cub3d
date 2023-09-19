/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:01:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/19 21:57:27 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	search_player_presence(char *map);

int	get_map(int map_fd, t_map *map)
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
	if (!search_player_presence(str) || !check_closed(str, map))
		return (0);
	return (1);
}

static int	search_player_presence(char *map)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (map[i])
	{
		if (ft_is_in_str("NSEW", map[i++]))
			nb++;
	}
	if (nb > 1)
		return ((ft_putstr_fd(TMP, 2)), 0);
	if (nb == 0)
		return ((ft_putstr_fd(NO_PLAYER, 2)), 0);
	return (1);
}
