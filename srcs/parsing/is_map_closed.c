/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 21:56:14 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/20 15:31:08 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_line_v_closed(char **tab, int x, int entry_y);
int	is_line_h_closed(char *line);

int	check_closed(char *map_str, t_map *map, t_cub *cub)
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
	cub->mmap->map = split_map; 
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
