/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:02:47 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/19 22:37:43 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*cub;

	if (argc != 2)
		return (1);
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		return ((void)ft_putstr_fd(MISS_F, 2), 1);
	cub = init_cub(argv);
	mlx_destroy_display(cub->mlx_ptr);
	free_garbage(cub->garbage);
}
