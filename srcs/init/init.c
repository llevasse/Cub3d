/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:29:27 by llevasse          #+#    #+#             */
/*   Updated: 2023/10/17 10:17:07 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cub(t_cub *cub, char **argv)
{
	cub->garbage = 0x0;
	cub->mmap = malloc(sizeof(struct s_minimap));
	ft_add_garbage(&cub->garbage, cub->mmap);
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		return ((void)(free_garbage(cub->garbage), ft_putstr_fd(MLX_ERR, 2)));
	cub->map = parse(open(argv[1], O_RDONLY), cub);
	if (!cub->map)
		return ;
	init_minimap(cub);
	init_player(cub);
	ft_add_garbage(&cub->garbage, cub->mlx_ptr);
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WINDOW_W, WINDOW_H, "cub3D");
	if (!cub->win_ptr)
		ft_add_garbage(&cub->garbage, NULL);
	init_images(cub);
}

void	init_images(t_cub *cub)
{
	cub->img.mlx_img = mlx_new_image(cub->mlx_ptr, WINDOW_W, WINDOW_H);
	cub->img.addr = mlx_get_data_addr(cub->img.mlx_img,
			&cub->img.bpp, &cub->img.line_len, &cub->img.endian);
}

int	round_to_pow_2(int n){
	n--;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	return (n + 1);
}

void	init_minimap(t_cub *cub)
{
	int	i;
	int	divider;

	cub->mmap->nb_line = get_tab_len(cub->mmap->map);
	cub->mmap->mapy = cub->mmap->nb_line;
	init_map_value(cub);
	i = 0;
	cub->mmap->map_width = 0;
	while (i < cub->mmap->nb_line)
	{
		if ((int)ft_strlen(cub->mmap->map[i++]) > cub->mmap->map_width)
			cub->mmap->map_width = ft_strlen(cub->mmap->map[i - 1]);
	}
	divider = cub->mmap->map_width;
	if (WINDOW_W < WINDOW_H)
		divider = cub->mmap->nb_line;
	cub->mmap->block_s = round_to_pow_2(MMAP_S / divider) / 2;
}

void	init_map_value(t_cub *cub)
{
	int	i;

	i = 0;
	cub->mmap->mapx = malloc(sizeof(int) * (cub->mmap->mapy));
	ft_add_garbage(&cub->garbage, cub->mmap->mapx);
	cub->mmap->maps = 0;
	while (i < cub->mmap->mapy)
	{
		cub->mmap->mapx[i] = ft_strlen(cub->mmap->map[i]) - 1;
		cub->mmap->maps += cub->mmap->mapx[i];
		i++;
	}
}
