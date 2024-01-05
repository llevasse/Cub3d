/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:01:04 by llevasse          #+#    #+#             */
/*   Updated: 2024/01/05 22:11:16 by llevasse         ###   ########.fr       */
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

char	*skip_empty_line(int fd, t_map *map, char *str, t_cub *cub)
{
	while (str && is_line_empty(str))
	{
		str = get_next_line(fd);
		if (str)
			ft_add_garbage(&map->garbage, str, cub);
	}
	return (str);
}

int	valid_resolution(t_map *map)
{
	if (map->north_img.width != map->south_img.width)
		return ((void)ft_putstr_fd(UNEQUAL_RESOLUTION, 2), 0);
	if (map->north_img.width != map->east_img.width)
		return ((void)ft_putstr_fd(UNEQUAL_RESOLUTION, 2), 0);
	if (map->west_img.width != map->south_img.width)
		return ((void)ft_putstr_fd(UNEQUAL_RESOLUTION, 2), 0);
	if (map->door_img.mlx_img && map->north_img.width != map->door_img.width)
		return ((void)ft_putstr_fd(UNEQUAL_RESOLUTION, 2), 0);
	return (1);
}

int	get_map(int map_fd, t_map *map, t_cub *cub)
{
	char	*str;
	char	*tmp;

	str = "";
	tmp = get_next_line(map_fd);
	while (tmp)
	{
		ft_add_garbage(&map->garbage, tmp, cub);
		tmp = skip_empty_line(map_fd, map, tmp, cub);
		if (!tmp)
			break ;
		if (!is_texture_line(tmp))
		{
			str = ft_strjoin(str, tmp);
			ft_add_garbage(&map->garbage, str, cub);
		}
		else if (!get_wall(tmp, map, cub))
			return (0);
		tmp = get_next_line(map_fd);
	}
	if (!search_player_presence(map, cub, str) || !valid_line(str, map)
		|| !valid_resolution(map))
		return (0);
	return (1);
}
