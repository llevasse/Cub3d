/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:52:44 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/21 11:42:23 by tdutel           ###   ########.fr       */
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
	int					block_w;
	int					block_h;
	struct s_img		img;
}				t_minimap;

typedef struct s_player
{
	float	px;
	float	py;
	float	pdx;	//player delta x
	float	pdy;	//player delta y
	float	pa;		//player angle
}				t_player;


typedef struct s_cub
{
	void				*mlx_ptr;
	void				*win_ptr;
	struct s_map		*map;
	struct s_minimap	*minimap;
	struct s_garbage	*garbage;
	t_player			player;
}				t_cub;

t_garbage	*ft_new_garbage(void *address);
void		ft_add_garbage(t_garbage **lst, void *addr);
void		malloc_failed(t_garbage *garbage);
void		free_garbage(t_garbage	*garbage);

#endif
