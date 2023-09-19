/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:29:27 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/20 00:17:09 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*init_cub(char **argv)
{
	t_game	*cub;

	cub = malloc(sizeof(struct s_game));
	if (!cub)
		return ((void)ft_putstr_fd(MEM_ERR, 2), NULL);
	cub->garbage = 0x0;
	ft_add_garbage(&cub->garbage, cub);
	cub->map = parse(open(argv[1], O_RDONLY), cub);
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
	{
		free_garbage(cub->garbage);
		return ((void)ft_putstr_fd(MLX_ERR, 2), NULL);
	}
	ft_add_garbage(&cub->garbage, cub->mlx_ptr);
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!cub->win_ptr)
		ft_add_garbage(&cub->garbage, NULL);
	mlx_hook(cub->win_ptr, KeyPress, KeyPressMask, &handle_input, cub);
	mlx_hook(cub->win_ptr, 17, 0, &close_window, cub);
	mlx_loop(cub->mlx_ptr);
	return (cub);
}
