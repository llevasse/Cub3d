/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:01:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/19 16:51:10 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_closed(char *map_str, t_map *map);

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
	ft_printf("map :\n%s\n", str);
	ft_printf("Is the map closed : %d\n", check_closed(str, map));
	return (1);
}

int	get_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

int	is_line_h_closed(char *line)
{
	int	i;
	int	len;

	len = ft_strlen(line);
	i = 0;
	while (len > 0 && line[len] != '1')
	{
		if (line[len--] == '0')
			return (0);
	}
	while (i < len && line[i] != '1')
	{
		if (line[i++] == '0')
			return (0);
	}
	return (1);
}

int	check_closed(char *map_str, t_map *map)
{
	char	**split_map;
	int		i;

	i = 0;
	split_map = ft_split(map_str, '\n');
	ft_add_garbage(&map->garbage, split_map);
	while (i < get_tab_len(split_map))
	{
		ft_add_garbage(&map->garbage, split_map[i]);
		if (!is_line_h_closed(split_map[i++]))
			return (0);
	}
	return (1);
}
