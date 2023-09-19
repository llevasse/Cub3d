/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 23:48:52 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/19 12:03:36 by llevasse         ###   ########.fr       */
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
	*fd = open(s, O_RDONLY);
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

int	get_wall(int map_fd, t_map *map)
{
	char	*str;

	str = get_next_line(map_fd);
	while (str && is_line_empty(str))
		str = get_next_line(map_fd);
	if (!str)
		return (0);
	if (!ft_strncmp("NO ", str, 3) && map->north_fd == -1)
		return (do_open(str + 3, &map->north_fd, 0));
	if (!ft_strncmp("SO ", str, 3) && map->south_fd == -1)
		return (do_open(str + 3, &map->south_fd, 1));
	if (!ft_strncmp("WE ", str, 3) && map->west_fd == -1)
		return (do_open(str + 3, &map->west_fd, 2));
	if (!ft_strncmp("EA ", str, 3) && map->east_fd == -1)
		return (do_open(str + 3, &map->east_fd, 3));
	if (!ft_strncmp("F ", str, 2) && map->f_rgb == -1)
		return ((void)(map->f_rgb = get_rgb_value(str + 2)), 1);
	if (!ft_strncmp("C ", str, 2) && map->c_rgb == -1)
		return ((void)(map->c_rgb = get_rgb_value(str + 2)), 1);
	return ((void)ft_putstr_fd(INVALID_CUB, 2), 0);
}
