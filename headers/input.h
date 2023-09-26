/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:22:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/26 11:57:37 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//srcs/input/input.c:
int	handle_input(int keysym, t_cub *cub);
int	close_window(t_cub *cub);
int	rotate_input(int keysym, t_cub *cub);

//srcs/input/set_player_pos.c:
float		no_higher(float nb, float highest, float lowest);
void		set_player_new_pos(t_cub *cub, int angle);
void		get_player_new_pos(t_cub *cub, int angle, t_point *p);
