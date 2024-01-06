/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:50:20 by llevasse          #+#    #+#             */
/*   Updated: 2024/01/06 17:42:40 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse(int map_fd, t_cub *cub)
{
	cub->north_img.mlx_img = NULL;
	cub->south_img.mlx_img = NULL;
	cub->east_img.mlx_img = NULL;
	cub->west_img.mlx_img = NULL;
	cub->door_img.mlx_img = NULL;
	cub->f_rgb = -1;
	cub->c_rgb = -1;
	cub->player_rotation = -1;
	if (map_fd == -1)
		return ((void)ft_putstr_fd(CUB_OPEN_ERR, 2), 0);
	if (!get_map(map_fd, cub))
	{
		close(map_fd);
		return (0);
	}
	close(map_fd);
	return (1);
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

void	close_walls(t_cub *cub)
{
	if (cub->north_img.mlx_img)
		mlx_destroy_image(cub->mlx_ptr, cub->north_img.mlx_img);
	if (cub->south_img.mlx_img)
		mlx_destroy_image(cub->mlx_ptr, cub->south_img.mlx_img);
	if (cub->east_img.mlx_img)
		mlx_destroy_image(cub->mlx_ptr, cub->east_img.mlx_img);
	if (cub->west_img.mlx_img)
		mlx_destroy_image(cub->mlx_ptr, cub->west_img.mlx_img);
	if (cub->door_img.mlx_img)
		mlx_destroy_image(cub->mlx_ptr, cub->door_img.mlx_img);
}
