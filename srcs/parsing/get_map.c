/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:01:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/19 21:54:29 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_closed(char *map_str, t_map *map);
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

int	is_line_v_closed(char **tab, int x, int entry_y)
{
	int	y;
	int	closed;

	closed = 0;
	y = entry_y;
	if (tab[y][x] != '0')
		return (1);
	while (y >= 0 && !closed)
	{
		if ((int)ft_strlen(tab[y]) >= x && tab[y][x] == '1')
			closed++;
		y--;
	}
	y = entry_y;
	while (y < get_tab_len(tab))
	{
		if ((int)ft_strlen(tab[y]) >= x && tab[y][x] == '1' && closed)
			return (closed);
		y++;
	}
	return (0);
}

int	check_closed(char *map_str, t_map *map)
{
	char	**split_map;
	int		i;
	int		j;
	int		len;

	i = 0;
	split_map = ft_split(map_str, '\n');
	ft_add_garbage(&map->garbage, split_map);
	while (i < get_tab_len(split_map))
	{
		j = 0;
		len = ft_strlen(split_map[i]);
		ft_add_garbage(&map->garbage, split_map[i]);
		while (j < len)
		{
			if (!is_line_v_closed(split_map, j++, i))
				return ((void)ft_putstr_fd(OPEN_MAP, 2), 0);
		}
		if (!is_line_h_closed(split_map[i++]))
			return ((void)ft_putstr_fd(OPEN_MAP, 2), 0);
	}
	return (1);
}
