/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:52:44 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/29 16:40:08 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "cub3d.h"

typedef struct s_garbage
{
	void				*addr;
	struct s_garbage	*next;
}				t_garbage;

typedef struct s_img
{
	void				*mlx_img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
	int					width;
	int					height;
}				t_img;

typedef struct s_map
{
	struct s_img		north_img;
	struct s_img		south_img;
	struct s_img		east_img;
	struct s_img		west_img;
	struct s_img		door_img;
	int					f_rgb;
	int					c_rgb;
	float				player_rotation;
	struct s_garbage	*garbage;
}				t_map;

typedef struct s_minimap
{
	char				**map;
	int					dof;
	int					nb_line;
	int					map_width;
	int					block_s;
	int					*mapx;
	int					maps;
}				t_minimap;

typedef struct s_point
{
	float				x;
	float				y;
}				t_point;

typedef struct s_door
{
	float				r_x;
	float				r_y;
	float				dist;
	int					x;
	int					y;
	int					hit_door;
	int					cross_door;
}				t_door;

typedef struct s_line
{
	t_point				p_a;
	t_point				p_b;
	float				dx;
	float				dy;
	float				x_step;
	float				y_step;
	float				steps;
	float				dist;
	float				wall_percent;
	t_img				*wall;
	int					w_type;
	int					x;
	int					y;
	int					height;
	int					start;
	int					stop;
	t_door				door;
}				t_line;

typedef struct s_player
{
	float			px;
	float			py;
	float			pdx;
	float			pdy;
	float			pa;
	struct s_point	p;
}				t_player;

typedef struct s_cub
{
	void				*mlx_ptr;
	void				*win_ptr;
	struct s_map		*map;
	struct s_img		img;
	struct s_minimap	*mmap;
	struct s_garbage	*garbage;
	float				field_step;
	float				avg_block_s;
	float				avg_v_block_s;
	float				avg_h_block_s;
	t_door				*door;
	t_player			player;
}				t_cub;

typedef struct s_cast
{
	t_line	line;
	t_line	h;
	t_line	v;
	float	y_ratio;
	float	dist;
}				t_cast;

t_garbage	*ft_new_garbage(void *address);
void		ft_add_garbage(t_garbage **lst, void *addr);
void		malloc_failed(t_garbage *garbage);
void		free_garbage(t_garbage	*garbage);
int			garbage_size(t_garbage *lst);
void		free_one_addr(t_garbage **lst, void *addr);
#endif
