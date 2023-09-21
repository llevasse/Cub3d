/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:02:47 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/21 12:16:37 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (1);
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		return ((void)ft_putstr_fd(MISS_F, 2), 1);
	init_cub(&cub, argv);
	mlx_loop_hook(cub.mlx_ptr, &render, &cub);
	mlx_hook(cub.win_ptr, KeyPress, KeyPressMask, &handle_input, &cub);
	mlx_hook(cub.win_ptr, 17, 0, &close_window, &cub);
	mlx_loop(cub.mlx_ptr);
	free_garbage(cub.garbage);
}
