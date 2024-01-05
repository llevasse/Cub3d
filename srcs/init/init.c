/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:29:27 by llevasse          #+#    #+#             */
/*   Updated: 2024/01/05 22:42:43 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cub(t_cub *cub, char **argv)
{
	cub->garbage = 0x0;
	cub->door = NULL;
	cub->win_ptr = NULL;
	cub->map = NULL;
	cub->img.mlx_img = NULL;
	cub->north_img.mlx_img = NULL;
	cub->south_img.mlx_img = NULL;
	cub->east_img.mlx_img = NULL;
	cub->west_img.mlx_img = NULL;
	cub->door_img.mlx_img = NULL;
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		return (ft_putstr_fd(MLX_ERR, 2));
	cub->mmap = malloc(sizeof(struct s_minimap));
	ft_add_garbage(&cub->garbage, cub->mmap, cub);
	cub->map = parse(open(argv[1], O_RDONLY), cub);
	if (!cub->map)
		close_window(cub, 1);
	init_minimap(cub);
	init_player(cub);
	ft_add_garbage(&cub->garbage, cub->mlx_ptr, cub);
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WINDOW_W, WINDOW_H, "cub3D");
	if (!cub->win_ptr)
		close_window(cub, 1);
	init_images(cub);
	cub->field_step = ((float)(PLAYER_FOV - 1) / WINDOW_W);
}

void	init_images(t_cub *cub)
{
	cub->img.mlx_img = mlx_new_image(cub->mlx_ptr, WINDOW_W, WINDOW_H);
	cub->img.width = WINDOW_W;
	cub->img.height = WINDOW_H;
	cub->img.addr = mlx_get_data_addr(cub->img.mlx_img,
			&cub->img.bpp, &cub->img.line_len, &cub->img.endian);
}

void	init_minimap(t_cub *cub)
{
	int	i;

	cub->mmap->nb_line = get_tab_len(cub->mmap->map);
	init_map_value(cub);
	i = 0;
	cub->mmap->map_width = 0;
	while (i < cub->mmap->nb_line)
	{
		if (cub->mmap->mapx[i++] > cub->mmap->map_width)
			cub->mmap->map_width = cub->mmap->mapx[i - 1];
	}
	cub->mmap->dof = cub->mmap->map_width;
	if (cub->mmap->map_width < cub->mmap->nb_line)
		cub->mmap->dof = cub->mmap->nb_line;
	cub->mmap->block_s = cub->north_img.width;
}

void	init_map_value(t_cub *cub)
{
	int	i;

	i = 0;
	cub->mmap->mapx = malloc(sizeof(int) * (cub->mmap->nb_line));
	ft_add_garbage(&cub->garbage, cub->mmap->mapx, cub);
	cub->mmap->maps = 0;
	while (i < cub->mmap->nb_line)
	{
		cub->mmap->mapx[i] = ft_strlen(cub->mmap->map[i]) - 1;
		cub->mmap->maps += cub->mmap->mapx[i++];
	}
}
