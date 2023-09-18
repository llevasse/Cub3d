/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:52:44 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/18 22:02:15 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "cub3d"

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

#endif
