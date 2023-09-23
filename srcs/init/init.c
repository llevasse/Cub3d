/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:29:27 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/22 12:19:42 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cub(t_cub *cub, char **argv)
{
	cub->garbage = 0x0;
	cub->minimap = malloc(sizeof(struct s_minimap));
	ft_add_garbage(&cub->garbage, cub->minimap);
	cub->map = parse(open(argv[1], O_RDONLY), cub);
	if (!cub->map)
		return ;
	init_minimap(cub);
	init_player(cub);
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		return ((void)(free_garbage(cub->garbage), ft_putstr_fd(MLX_ERR, 2)));
	ft_add_garbage(&cub->garbage, cub->mlx_ptr);
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!cub->win_ptr)
		ft_add_garbage(&cub->garbage, NULL);
	cub->minimap->img.mlx_img = mlx_new_image(cub->mlx_ptr, MMAP_WIDTH, MMAP_HEIGHT);
	cub->minimap->img.addr = mlx_get_data_addr(cub->minimap->img.mlx_img, &cub->minimap->img.bpp, &cub->minimap->img.line_len, &cub->minimap->img.endian);
}

void	init_minimap(t_cub *cub)
{
	int	i;
	int	divider;

	cub->minimap->nb_line = get_tab_len(cub->minimap->map);
	cub->minimap->mapy = cub->minimap->nb_line;
	init_map_value(cub);
	i = 0;
	cub->minimap->map_width = 0;
	while (i < cub->minimap->nb_line)
	{
		if ((int)ft_strlen(cub->minimap->map[i++]) > cub->minimap->map_width)
			cub->minimap->map_width = ft_strlen(cub->minimap->map[i - 1]);
	}
	divider = cub->minimap->map_width;
	if (MMAP_WIDTH < MMAP_HEIGHT)
		divider = cub->minimap->nb_line;
	cub->minimap->block_w = MMAP_WIDTH/divider;
	cub->minimap->block_h = MMAP_HEIGHT/divider;
}

void	init_map_value(t_cub *cub)
{
	int	i;

	i = 0;
	cub->minimap->mapx = malloc(sizeof(int) * (cub->minimap->mapy));
	ft_add_garbage(&cub->garbage, cub->minimap->mapx);
	cub->minimap->maps = 0;
	while (i < cub->minimap->mapy)
	{
		cub->minimap->mapx[i] = ft_strlen(cub->minimap->map[i]) - 1;
		cub->minimap->maps += cub->minimap->mapx[i];
		i++;
	}
}
