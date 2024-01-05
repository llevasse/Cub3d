/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:50:20 by llevasse          #+#    #+#             */
/*   Updated: 2024/01/05 22:49:14 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parse(int map_fd, t_cub *cub)
{
	cub->f_rgb = -1;
	cub->c_rgb = -1;
	cub->player_rotation = -1;
	if (map_fd == -1)
		return ((void)ft_putstr_fd(CUB_OPEN_ERR, 2), 0);
	if (!get_map(map_fd, cub)){
		close(map_fd);
		return (0);
	}
	close(map_fd);
	get_side_data_addrs(cub);
	return (1);
}

void	get_side_data_addrs(t_cub *cub)
{
	cub->north_img.addr = mlx_get_data_addr(cub->north_img.mlx_img,
			&cub->north_img.bpp, &cub->north_img.line_len,
			&cub->north_img.endian);
	cub->south_img.addr = mlx_get_data_addr(cub->south_img.mlx_img,
			&cub->south_img.bpp, &cub->south_img.line_len,
			&cub->south_img.endian);
	cub->west_img.addr = mlx_get_data_addr(cub->west_img.mlx_img,
			&cub->west_img.bpp, &cub->west_img.line_len,
			&cub->west_img.endian);
	cub->east_img.addr = mlx_get_data_addr(cub->east_img.mlx_img,
			&cub->east_img.bpp, &cub->east_img.line_len,
			&cub->east_img.endian);
	if (cub->door_img.mlx_img)
		cub->door_img.addr = mlx_get_data_addr(cub->door_img.mlx_img,
				&cub->door_img.bpp, &cub->door_img.line_len,
				&cub->door_img.endian);
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
