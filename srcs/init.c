/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:29:27 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/20 15:52:09 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cub(t_game *cub, char **argv)
{
	cub->garbage = 0x0;
	cub->minimap = malloc(sizeof(struct s_minimap));
	ft_add_garbage(&cub->garbage, cub->minimap);
	cub->map = parse(open(argv[1], O_RDONLY), cub);
	init_minimap(cub);
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
	{
		free_garbage(cub->garbage);
		return ((void)ft_putstr_fd(MLX_ERR, 2));
	}
	ft_add_garbage(&cub->garbage, cub->mlx_ptr);
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!cub->win_ptr)
		ft_add_garbage(&cub->garbage, NULL);
	cub->minimap->img.mlx_img = mlx_new_image(cub->mlx_ptr, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	cub->minimap->img.addr = mlx_get_data_addr(cub->minimap->img.mlx_img, &cub->minimap->img.bpp, &cub->minimap->img.line_len, &cub->minimap->img.endian);
}

void	init_minimap(t_game *cub)
{
	int	i;

	cub->minimap->nb_line = get_tab_len(cub->minimap->map);
	i = 0;
	cub->minimap->map_width = 0;
	while (i < cub->minimap->nb_line)
	{
		if ((int)ft_strlen(cub->minimap->map[i++]) > cub->minimap->map_width)
			cub->minimap->map_width = ft_strlen(cub->minimap->map[i - 1]);
	}
	cub->minimap->block_w = MINIMAP_WIDTH/cub->minimap->map_width;
	cub->minimap->block_h = MINIMAP_HEIGHT/cub->minimap->nb_line;
}
