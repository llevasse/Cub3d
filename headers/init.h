/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:39:12 by tdutel            #+#    #+#             */
/*   Updated: 2023/09/20 16:40:55 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "cub3d.h"


#define PLAYER "assets/player.xpm"
#define DOT "assets/dot.xpm"
#define WALL "assets/wall.xpm"
#define FLOOR "assets/floor.xpm"

//-----------------------------MAP----------------------------------------------
#define MAPX  8      //map width
#define MAPY  8      //map height
#define MAPS 64      //map cube size

void	redisplay(int key, t_game *cub);
int	exit_prog(t_game *cub);
int	key_event(int key, t_game *cub);


#endif
