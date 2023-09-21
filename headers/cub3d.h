/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:43:29 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/21 10:39:22 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "struct.h"
# include "err.h"
# include "../minilibx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>

# include <stdio.h> //debug.

# define WINDOW_WIDTH	1024*4
# define WINDOW_HEIGHT	512*4

# define MINIMAP_WIDTH	WINDOW_WIDTH/3
# define MINIMAP_HEIGHT	WINDOW_HEIGHT/3
# define MINIMAP_W_RGB	0xff0000
# define MINIMAP_RGB	0x00ff00
# define PLAYER_RGB		0x0000ff

# define PLAYER_OFFSET	5

void	init_cub(t_cub *cub, char **argv);
void	init_minimap(t_cub *cub);
void	init_player(t_cub *cub);
t_map	*parse(int map_fd, t_cub *cub);
int		get_map(int map_fd, t_map *map, t_cub *cub);
int		get_wall(int map_fd, t_map *map);
int		check_closed(char *map_str, t_map *map, t_cub *cub);
int		is_line_empty(char *str);
int		close_window(t_cub *cub);
int		handle_input(int keysym, t_cub *cub);
int		get_tab_len(char **tab);

void	img_pix_put(t_img *img, int x, int y, int colour);
int		render(t_cub *cub);
void	draw_minimap(t_cub *cub);
void	paint_minimap_bg(t_cub *cub);
int		get_pixel_colour(t_img *img, int x, int y);
int		check_collision(t_cub *cub, int is_x, int *offset);

int		key_event(int key, t_cub *param);

# define ON_DESTROY 17
# define ON_KEYDOWN 2

enum {
	w = 119,
	a = 97,
	s = 115,
	d = 100,
	left = 65361,
	right = 65363,
	down = 65364,
	up = 65362,
	esc = 65307,
	q = 113,
};

#endif
