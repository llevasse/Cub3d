/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:50:20 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/19 12:08:04 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_map_null(t_map *map);

t_map	*parse(int map_fd)
{
	int		element_got;
	t_map	*map;

	element_got = 0;
	if (map_fd == -1)
		return ((void)ft_putstr_fd(CUB_OPEN_ERR, 2), NULL);
	map = malloc(sizeof(struct s_map));
	if (!map)
		return ((void)ft_putstr_fd(MEM_ERR, 2), NULL);
	set_map_null(map);
	while (element_got < 6 && get_wall(map_fd, map) == 1)
		element_got++;
	if (!get_map(map_fd))
		return (NULL);
	return (map);
}

int	is_line_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	set_map_null(t_map *map)
{
	map->north_fd = -1;
	map->south_fd = -1;
	map->east_fd = -1;
	map->west_fd = -1;
	map->f_rgb = -1;
	map->c_rgb = -1;
	map->player_rotation = -1;
}
