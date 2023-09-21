/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:15:33 by tdutel            #+#    #+#             */
/*   Updated: 2023/09/20 16:36:30 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	main(int argc, char **argv)
// {
// 	t_map	*map;
// 	void	*ptr;

// 	ptr = mlx_init();
// 	if (argc != 2)
// 		return (1);
// 	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
// 		return ((void)ft_putstr_fd(MISS_F, 2), 1);
// 	map = parse(open(argv[1], O_RDONLY));
// 	if (!map)
// 		return (1);
// 	return (0);
// }

#define PLAYER "assets/player.xpm"
#define DOT "assets/dot.xpm"
#define WALL "assets/wall.xpm"
#define FLOOR "assets/floor.xpm"

//-----------------------------MAP----------------------------------------------
#define MAPX  8      //map width
#define MAPY  8      //map height
#define MAPS 64      //map cube size

void	drawMap2D(t_cub cub)
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

void	redisplay(int key, t_cub *cub);
int		exit_prog(t_cub *cub);

int	main(void)
{
	t_cub	cub;
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

int	key_event(int key, t_cub *cub)
{
	ft_printf("%d\n", key);
	if (key == esc)
		exit_prog(cub);
	if (key == a || key == d || key == w || key == s)
		redisplay(key, cub);
	return (0);
}

int	exit_prog(t_cub *cub)
{
	mlx_destroy_image(cub->mlx_ptr, cub->img.img_ptr);
	mlx_destroy_display(cub->mlx_ptr);
	free(cub->mlx_ptr);
	free(cub->win_ptr);
	// mlx_destroy_display(cub->mlx_ptr);
	exit (0);
	return (0);
}

void	redisplay(int key, t_cub *cub)
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
