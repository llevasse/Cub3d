/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 23:48:52 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/18 23:55:27 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	do_open(char *s, int *fd)
{
	*fd = open(s, O_RDONLY);
	if (*fd == -1)
		return ((void)ft_putstr_fd(WALL_OPEN_ERR, 2), 0);
	return (1);
}

int	get_wall(int map_fd, t_map *map)
{
	char	*str;

	str = get_next_line(map_fd);
	while (str && is_line_empty(str))
		str = get_next_line(map_fd);
	if (!str)
		return (0);
	if (!ft_strncmp("NO ", str, 3) && map->north_fd == -1)
		return (do_open(str + 3, &map->north_fd));
	if (!ft_strncmp("SO ", str, 3) && map->south_fd == -1)
		return (do_open(str + 3, &map->south_fd));
	if (!ft_strncmp("WE ", str, 3) && map->west_fd == -1)
		return (do_open(str + 3, &map->west_fd));
	if (!ft_strncmp("EA ", str, 3) && map->east_fd == -1)
		return (do_open(str + 3, &map->east_fd));
	if (!ft_strncmp("F ", str, 2) && map->f_rgb == -1)
		return ((void)(map->f_rgb = get_rgb_value(str + 3)), 1);
	if (!ft_strncmp("C ", str, 2) && map->c_rgb == -1)
		return ((void)(map->c_rgb = get_rgb_value(str + 3)), 1);
	return (0);
}
