/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:50:20 by llevasse          #+#    #+#             */
/*   Updated: 2023/10/17 10:07:05 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_map_null(t_map *map);

t_map	*parse(int map_fd, t_cub *cub)
{
	int		element_got;
	t_map	*map;

	element_got = 0;
	if (map_fd == -1)
		return ((void)ft_putstr_fd(CUB_OPEN_ERR, 2), NULL);
	map = malloc(sizeof(struct s_map));
	ft_add_garbage(&cub->garbage, map);
	set_map_null(map);
	map->garbage = cub->garbage;
	while (element_got < 6 && get_wall(map_fd, map, cub) == 1)
		element_got++;
	if (element_got != 6 || !get_map(map_fd, map, cub))
		return (close_walls(map), free_garbage(map->garbage),
			close(map_fd), NULL);
	close(map_fd);
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

void	close_walls(t_map *map)
{
	if (map->north_fd != -1)
		close(map->north_fd);
	if (map->south_fd != -1)
		close(map->south_fd);
	if (map->east_fd != -1)
		close(map->east_fd);
	if (map->west_fd != -1)
		close(map->west_fd);
}

static void	set_map_null(t_map *map)
{
	map->north_fd = -1;
	map->south_fd = -1;
	map->east_fd = -1;
	map->west_fd = -1;
	map->north_img = NULL;
	map->south_img = NULL;
	map->east_img = NULL;
	map->west_img = NULL;
	map->f_rgb = -1;
	map->c_rgb = -1;
	map->player_rotation = -1;
}
