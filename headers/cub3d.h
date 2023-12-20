/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:43:29 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/20 14:45:31 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WINDOW_W	960 //1920
# define WINDOW_H	600 //1200

# define MMAP_W_RGB		0x000000
# define MMAP_RGB		0xffffff
# define MMAP_RANGE		8
# define MMAP_BLOCK_S	8 //16

# define DOOR_RGB		0x888888

# define PLAYER_RGB		0x0000ff
# define PLAYER_FOV		80

# define PLAYER_R_OFFSET	3

# define PI 3.1415926535
# define RADIAN 0.017453292519444445

# include "../libft/libft.h"
# include "struct.h"
# include "err.h"
# include "render.h"
# include "init.h"
# include "input.h"
# include "parse.h"
# include "../minilibx/mlx.h"

# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
#endif
