/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:22:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/29 17:02:48 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//srcs/input/input.c:
int			handle_input(int keysym, t_cub *cub);
int			close_window(t_cub *cub);
int			rotate_input(int keysym, t_cub *cub);

//srcs/input/set_player_pos.c:
float		no_higher(float nb, float highest, float lowest);
void		check_collision(t_cub *cub, int angle, float h_offset, float v_offset);
t_point		get_player_new_pos(t_cub *cub, int angle, float h_dist, float v_dist);
