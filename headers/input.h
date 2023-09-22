/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:22:53 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/22 22:24:51 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//srcs/input/input.c:
int	handle_input(int keysym, t_cub *cub);
int	close_window(t_cub *cub);
int	rotate_input(int keysym, t_cub *cub);

//srcs/input/set_player_pos.c:
int		no_higher(int nb, int highest, int lowest);
void	set_player_new_pos(t_cub *cub, int angle, float distance);
float	get_player_new_pos(t_cub *cub, int angle, float distance, float *x);
