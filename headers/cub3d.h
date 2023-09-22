/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:43:29 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/22 22:25:07 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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

t_map	*parse(int map_fd, t_cub *cub);
int		get_map(int map_fd, t_map *map, t_cub *cub);
int		get_wall(int map_fd, t_map *map);
int		check_closed(char *map_str, t_map *map, t_cub *cub);
int		is_line_empty(char *str);
int		get_tab_len(char **tab);

// void	paint_minimap_bg(t_cub *cub);

#endif
