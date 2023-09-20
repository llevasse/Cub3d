/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:43:29 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/20 12:52:31 by llevasse         ###   ########.fr       */
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

# define WINDOW_WIDTH	1024
# define WINDOW_HEIGHT	512

# define MINIMAP_W_RGB	0xff
# define MINIMAP_RGB	0x00ff00

void	init_cub(t_game *cub, char **argv);
t_map	*parse(int map_fd, t_game *cub);
int		get_map(int map_fd, t_map *map);
int		get_wall(int map_fd, t_map *map);
int		check_closed(char *map_str, t_map *map);
int		is_line_empty(char *str);
int		close_window(t_game *cub);
int		handle_input(int keysym, t_game *cub);

void	img_pix_put(t_img *img, int x, int y, int colour);
int		render(t_game *cub);
void	paint_minimap_bg(t_game *cub);

#endif
