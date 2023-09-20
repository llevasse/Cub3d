/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:37:55 by tdutel            #+#    #+#             */
/*   Updated: 2023/09/20 16:40:14 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_init.h.h"




void	drawMap2D(t_game cub)
{
	int	x;
	int	y;
	int	xo;
	int	yo;
	int	map[]=
{
 1,1,1,1,1,1,1,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,1,0,1,
 1,0,0,0,0,0,0,1,
 1,1,1,1,1,1,1,1,
};

	y = 0;
	x = 0;
	while (y < MAPY)
	{
		while (x < MAPX)
		{
			if (map[y * MAPX + x] == 1)
			{
				cub.img.img_ptr = mlx_xpm_file_to_image(cub.mlx_ptr, WALL, &cub.img.width, &cub.img.height);
				mlx_put_image_to_window(cub.mlx_ptr, cub.win_ptr, cub.img.img_ptr, cub.img.width * x + 1, cub.img.height * y + 1);
			}
			else
			{
				// ft_printf("ok?");
				cub.img.img_ptr = mlx_xpm_file_to_image(cub.mlx_ptr, FLOOR, &cub.img.width, &cub.img.height);
				mlx_put_image_to_window(cub.mlx_ptr, cub.win_ptr, cub.img.img_ptr, cub.img.width * x + 1, cub.img.height * y + 1);
			}
			xo = x * MAPS;
			yo = y * MAPS;

			x++;
		}
		x = 0;
		y++;
	}
}

int	main(void)
{
	t_game	cub;
	void	*tmp;

	cub.mlx_ptr = mlx_init();

	cub.win_ptr = mlx_new_window(cub.mlx_ptr, 2048, 1024, "cub3D");
	cub.player.px = 5;
	cub.player.py = 5;
	cub.img.img_ptr = mlx_xpm_file_to_image(cub.mlx_ptr, DOT, &cub.img.width, &cub.img.height);
	tmp = cub.img.img_ptr;
	mlx_put_image_to_window(cub.mlx_ptr, cub.win_ptr, cub.img.img_ptr, cub.img.width * cub.player.px, cub.img.height * cub.player.py);
	drawMap2D(cub);
	cub.img.img_ptr = tmp;
	mlx_hook(cub.win_ptr, ON_DESTROY, 0, exit_prog, &cub);
	mlx_key_hook(cub.win_ptr, key_event, &cub);
	mlx_loop(cub.mlx_ptr);
	return (0);
}

int	key_event(int key, t_game *cub)
{
	ft_printf("%d\n", key);
	if (key == esc)
		exit_prog(cub);
	if (key == a || key == d || key == w || key == s)
		redisplay(key, cub);
	return (0);
}

int	exit_prog(t_game *cub)
{
	mlx_destroy_image(cub->mlx_ptr, cub->img.img_ptr);
	mlx_destroy_display(cub->mlx_ptr);
	free(cub->mlx_ptr);
	free(cub->win_ptr);
	// mlx_destroy_display(cub->mlx_ptr);
	exit (0);
	return (0);
}

void	redisplay(int key, t_game *cub)
{
	if (key == a)
		cub->player.px -= 0.5;
	if (key == d)
		cub->player.px += 0.5;
	if (key == w)
		cub->player.py -= 0.5;
	if (key == s)
		cub->player.py += 0.5;
	drawMap2D(*cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img.img_ptr, cub->img.width * cub->player.px, cub->img.height * cub->player.py);
}
