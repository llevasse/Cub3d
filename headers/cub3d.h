/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:43:29 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/08 19:13:32 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WINDOW_W	320*9
# define WINDOW_H	200*9

# define MMAP_S		WINDOW_W/3
# if WINDOW_W/3 > WINDOW_H/3
#	undef MMAP_S
#	define MMAP_S WINDOW_H/3
# endif

# define MMAP_W_RGB	0x000000
# define MMAP_RGB	0xffffff
# define PLAYER_RGB		0x0000ff
# define PLAYER_FOV		80

# define PLAYER_OFFSET		5
# define PLAYER_R_OFFSET	1

# define PI 3.1415926535
# define RADIAN PI/180

# define FIELD_R_STEP ((float)(PLAYER_FOV - 1) / WINDOW_W) / 16
# define COLUMN_WIDTH (WINDOW_W / PLAYER_FOV) * FIELD_R_STEP

# define NO 1
# define SO 2
# define WE 3
# define EA 4

# include "../libft/libft.h"
# include "struct.h"
# include "err.h"
# include "render.h"
# include "init.h"
# include "input.h"
# include "../minilibx/mlx.h"

# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>

# include <stdio.h> //debug.

t_map	*parse(int map_fd, t_cub *cub);
int		get_map(int map_fd, t_map *map, t_cub *cub);
void	close_walls(t_cub *cub, t_map *map);
int		get_wall(int map_fd, t_map *map, t_cub *cub);
int		check_closed(t_cub *cub, int x, int y);
int		is_line_empty(char *str);
int		get_tab_len(char **tab);

#endif
