/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:50:20 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/18 23:21:46 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_map_null(t_map *map);
static int	get_wall(int map_fd, t_map *map);
static int	is_line_empty(char *str);

t_map	*parse(int map_fd)
{
	int		element_got;
	t_map	*map;

	element_got = 0;
	map = malloc(sizeof(struct s_map));
	if (!map)
		return (NULL);
	set_map_null(map);
	while (element_got < 6 && get_wall(map_fd, map) == 1)
		element_got++;
	return (map);
}

static int	get_rgb_value(char *s)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(ft_strsep(&s, ","));
	g = ft_atoi(ft_strsep(&s, ","));
	b = ft_atoi(ft_strsep(&s, ","));
	return ((r * 256 * 256) + (g * 256) + b);
}

static int	get_wall(int map_fd, t_map *map)
{
	char	*str;

	str = get_next_line(map_fd);
	while (str && is_line_empty(str))
		str = get_next_line(map_fd);
	if (!str)
		return (0);
	if (!ft_strncmp("NO ", str, 3) && map->north_fd == -1)
		return ((void)(map->north_fd = open(str + 3, O_RDONLY)), 1);
	if (!ft_strncmp("SO ", str, 3) && map->south_fd == -1)
		return ((void)(map->south_fd = open(str + 3, O_RDONLY)), 1);
	if (!ft_strncmp("WE ", str, 3) && map->west_fd == -1)
		return ((void)(map->west_fd = open(str + 3, O_RDONLY)), 1);
	if (!ft_strncmp("EA ", str, 3) && map->east_fd == -1)
		return ((void)(map->east_fd = open(str + 3, O_RDONLY)), 1);
	if (!ft_strncmp("F ", str, 2) && map->f_rgb == -1)
		return ((void)(map->f_rgb = get_rgb_value(str + 3)), 1);
	if (!ft_strncmp("C ", str, 2) && map->c_rgb == -1)
		return ((void)(map->c_rgb = get_rgb_value(str + 3)), 1);
	return (0);
}

static int	is_line_empty(char *str)
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
