/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:52:44 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/20 00:43:53 by llevasse         ###   ########.fr       */
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
}						t_img;

typedef struct s_game
{
	void				*mlx_ptr;
	void				*win_ptr;
	struct s_img		img;
	struct s_map		*map;
	struct s_garbage	*garbage;
}				t_game;

t_garbage	*ft_new_garbage(void *address);
void		ft_add_garbage(t_garbage **lst, void *addr);
void		malloc_failed(t_garbage *garbage);
void		free_garbage(t_garbage	*garbage);

#endif
