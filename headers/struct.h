/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:52:44 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/20 15:31:49 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "cub3d.h"

typedef struct s_map
{
	int		north_fd;
	int		south_fd;
	int		east_fd;
	int		west_fd;
	int		f_rgb;		//floor rgb value
	int		c_rgb;		//ceiling rgb value
	double	player_rotation;
}				t_map;

typedef struct s_player
{
	float	px;
	float	py;

}				t_player;

typedef struct s_image
{
	void	*img_ptr;
	int		width;
	int		height;
}				t_image;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		img;
	t_map		map;
	t_player	player;
}				t_game;

#endif
