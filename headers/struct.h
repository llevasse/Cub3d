/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:52:44 by llevasse          #+#    #+#             */
/*   Updated: 2023/11/14 14:05:33 by tdutel           ###   ########.fr       */
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
	struct s_img		*wall;
	struct s_img		*old_wall;
	int					f_rgb;		//floor rgb value
	int					c_rgb;		//ceiling rgb value
	float				player_rotation;
	struct s_garbage	*garbage;
	}				t_map;

typedef struct s_minimap
{
	char				**map;
	int					dof;		//depth of field
	int					nb_line;
	int					map_width;
	int					block_s;
	int					*mapx;
	int					mapy;
	int					maps;
}				t_minimap;

typedef struct s_point
{
	float				x;
	float				y;
}				t_point;

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
}				t_line;

typedef struct s_player
{
	float			px;
	float			py;
	float			pdx;	//player delta x
	float			pdy;	//player delta y
	float			pa;		//player angle
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
	t_player			player;
}				t_cub;

typedef struct s_fov
{
	t_point				player;
	t_point				leftest;
	t_point				rightest;
	t_point				p;
	t_point				p2;
	t_line				fl;				//false_line
	float				field_dist;		//distance between leftest point and rightest point
	float				field_step;		//field_dist / WINDOW_WIDTH
	float				column_width;
	float				beg_angle;
	float				cur_angle;
	float				end_angle;
	float				ray_step;
	float				player_dist;
}				t_fov;

typedef struct s_cast
{
	t_line	line;
	t_img	*wall;
	int		height;
	int		high;
	int		low;
	int		x;
	int		y;
	float	y_ratio;
	float	dist;
}				t_cast;

t_garbage	*ft_new_garbage(void *address);
void		ft_add_garbage(t_garbage **lst, void *addr);
void		malloc_failed(t_garbage *garbage);
void		free_garbage(t_garbage	*garbage);



//-----math-----------------------------

typedef struct s_math
{
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	aTan;
}				t_math;

#endif
