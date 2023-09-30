/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 23:48:52 by llevasse          #+#    #+#             */
/*   Updated: 2023/10/01 00:08:23 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_rgb_value(char *s)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(ft_strsep(&s, ", \t"));
	g = ft_atoi(ft_strsep(&s, ", \t"));
	b = ft_atoi(ft_strsep(&s, ", \t"));
	return ((r * 256 * 256) + (g * 256) + b);
}

static int	do_open(char *s, int *fd, int face)
{
	while (*s && ft_isspace(*s))
		s++;
	*fd = open(ft_strsep(&s, "\n\r \t"), O_RDONLY);
	if (*fd == -1 && face == 0)
		return ((void)ft_putstr_fd(N_WALL_OPEN_ERR, 2), 0);
	if (*fd == -1 && face == 1)
		return ((void)ft_putstr_fd(S_WALL_OPEN_ERR, 2), 0);
	if (*fd == -1 && face == 2)
		return ((void)ft_putstr_fd(W_WALL_OPEN_ERR, 2), 0);
	if (*fd == -1 && face == 3)
		return ((void)ft_putstr_fd(E_WALL_OPEN_ERR, 2), 0);
	return (1);
}

static char	*get_str_line(int map_fd, t_map *map)
{
	char	*str;

	str = get_next_line(map_fd);
	ft_add_garbage(&map->garbage, str);
	while (str && is_line_empty(str))
	{
		str = get_next_line(map_fd);
		ft_add_garbage(&map->garbage, str);
	}
	if (!str)
		return (0);
	while (*str && ft_isspace(*str))
		str++;
	if (*str)
		return (str);
	return (NULL);
}

int	get_wall(int map_fd, t_map *map)
{
	char	*str;
	char	*id;

	str = get_str_line(map_fd, map);
	if (!str)
		return (0);
	id = ft_strsep(&str, " \t");
	if (!ft_strcmp("NO", id) && map->north_fd == -1)
		return (do_open(str, &map->north_fd, 0));
	if (!ft_strcmp("SO", id) && map->south_fd == -1)
		return (do_open(str, &map->south_fd, 1));
	if (!ft_strcmp("WE", id) && map->west_fd == -1)
		return (do_open(str, &map->west_fd, 2));
	if (!ft_strcmp("EA", id) && map->east_fd == -1)
		return (do_open(str, &map->east_fd, 3));
	if (!ft_strcmp("F", id) && map->f_rgb == -1)
		return ((void)(map->f_rgb = get_rgb_value(str)), 1);
	if (!ft_strcmp("C", id) && map->c_rgb == -1)
		return ((void)(map->c_rgb = get_rgb_value(str)), 1);
	return ((void)ft_putstr_fd(INVALID_CUB, 2), 0);
}
