/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:52:44 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/19 15:04:40 by llevasse         ###   ########.fr       */
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

typedef struct s_garbage
{
	void				*addr;
	struct s_garbage	*next;
}	t_garbage;

t_garbage	*ft_new_garbage(void *address);
void		ft_add_garbage(t_garbage **lst, void *addr);
void		malloc_failed(t_garbage *garbage);
void		free_garbage(t_garbage	*garbage);

#endif
