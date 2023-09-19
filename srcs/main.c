/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:02:47 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/19 22:10:42 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	cub;
	t_map	*map;

	if (argc != 2)
		return (1);
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		return ((void)ft_putstr_fd(MISS_F, 2), 1);
	map = parse(open(argv[1], O_RDONLY));
	if (!map)
		return (1);
	cub.mlx_ptr = mlx_init();
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, 1024, 512, "cub3D");
	while (1)
		;
	mlx_destroy_display(cub.mlx_ptr);
	free(cub.mlx_ptr);
	free_garbage(map->garbage);
}
