/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:43:29 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/22 22:07:31 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "struct.h"
# include "err.h"
# include "render.h"
# include "../minilibx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>

# include <stdio.h> //debug.

# define WINDOW_WIDTH	1024*2
# define WINDOW_HEIGHT	512*2

# define MINIMAP_WIDTH	WINDOW_WIDTH/2
# define MINIMAP_HEIGHT	WINDOW_HEIGHT/2
# if MINIMAP_WIDTH > MINIMAP_HEIGHT
#	undef MINIMAP_WIDTH
#	define MINIMAP_WIDTH MINIMAP_HEIGHT
# endif
# define MINIMAP_W_RGB	0xff0000
# define MINIMAP_RGB	0x00ff00
# define PLAYER_RGB		0x0000ff
# define PLAYER_FOV		120

# define PLAYER_OFFSET	5

# define PI 3.1415926535
# define RADIAN PI/180

void	init_cub(t_cub *cub, char **argv);
void	init_minimap(t_cub *cub);
void	init_player(t_cub *cub);
int		get_player_start_orientation(char c);
t_map	*parse(int map_fd, t_cub *cub);
int		get_map(int map_fd, t_map *map, t_cub *cub);
int		get_wall(int map_fd, t_map *map);
int		check_closed(char *map_str, t_map *map, t_cub *cub);
int		is_line_empty(char *str);
int		close_window(t_cub *cub);
int		handle_input(int keysym, t_cub *cub);
int		get_tab_len(char **tab);

// void	paint_minimap_bg(t_cub *cub);


void	init_map_value(t_cub *cub);
int		no_higher(int nb, int highest, int lowest);
void	set_player_new_pos(t_cub *cub, int angle, float distance);
float	get_player_new_pos(t_cub *cub, int angle, float distance, float *x);
int		rotate_input(int keysym, t_cub *cub);

#endif
