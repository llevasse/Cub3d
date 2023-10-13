/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:52:44 by llevasse          #+#    #+#             */
/*   Updated: 2023/10/13 22:48:15 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "cub3d.h"

typedef struct s_map
{
	int					north_fd;
	int					south_fd;
	int					east_fd;
	int					west_fd;
	int					f_rgb;		//floor rgb value
	int					c_rgb;		//ceiling rgb value
	double				player_rotation;
	struct s_garbage	*garbage;
	}				t_map;

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
}				t_img;

typedef struct s_minimap
{
	char				**map;
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
	int					steps;
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
