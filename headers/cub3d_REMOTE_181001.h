/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:43:29 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/20 11:41:20 by tdutel           ###   ########.fr       */
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

t_map	*parse(int map_fd);
int		get_wall(int map_fd, t_map *map);
int		is_line_empty(char *str);

int		key_event(int key, t_game *param);

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
