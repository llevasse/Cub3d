/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:29:27 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/20 13:52:30 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cub(t_game *cub, char **argv)
{
	cub->garbage = 0x0;
	cub->minimap = malloc(sizeof(struct s_minimap));
	ft_add_garbage(&cub->garbage, cub->minimap);
	cub->map = parse(open(argv[1], O_RDONLY), cub);
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
	cub->minimap->img.mlx_img = mlx_new_image(cub->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	cub->minimap->img.addr = mlx_get_data_addr(cub->minimap->img.mlx_img, &cub->minimap->img.bpp, &cub->minimap->img.line_len, &cub->minimap->img.endian);
}
