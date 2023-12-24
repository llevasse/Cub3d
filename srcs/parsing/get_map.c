/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:01:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/24 23:03:15 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*pass_space(char *s)
{
	char	*str;

	str = s;
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

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
		if (is_texture_line(tmp))
		{
			if (!get_wall(tmp, map, cub))
				return (0);
		}
		else
		{
			str = ft_strjoin(str, tmp);
			ft_add_garbage(&map->garbage, str);
		}
		tmp = get_next_line(map_fd);
	}
	if (!search_player_presence(map, cub, str) || !valid_line(str, map))
		return (0);
	return (1);
}
