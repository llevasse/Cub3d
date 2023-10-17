/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:50:20 by llevasse          #+#    #+#             */
/*   Updated: 2023/10/17 10:37:02 by llevasse         ###   ########.fr       */
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
		return (close_walls(cub, map), free_garbage(map->garbage),
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

void	close_walls(t_cub *cub, t_map *map)
{
	if (map->north_img.mlx_img)
		mlx_destroy_image(cub->mlx_ptr, map->north_img.mlx_img);
	if (map->south_img.mlx_img)
		mlx_destroy_image(cub->mlx_ptr, map->south_img.mlx_img);
	if (map->east_img.mlx_img)
		mlx_destroy_image(cub->mlx_ptr, map->east_img.mlx_img);
	if (map->west_img.mlx_img)
		mlx_destroy_image(cub->mlx_ptr, map->west_img.mlx_img);
}

static void	set_map_null(t_map *map)
{
	map->north_img.mlx_img = NULL;
	map->south_img.mlx_img = NULL;
	map->east_img.mlx_img = NULL;
	map->west_img.mlx_img = NULL;
	map->f_rgb = -1;
	map->c_rgb = -1;
	map->player_rotation = -1;
}
