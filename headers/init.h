/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:13:25 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/25 13:54:50 by tdutel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//srcs/init/init_player.c:
void	init_player(t_cub *cub);
float		get_player_start_orientation(char c);

//srcs/init/init.c:
void	init_cub(t_cub *cub, char **argv);
void	init_minimap(t_cub *cub);
void	init_images(t_cub *cub);
void	init_map_value(t_cub *cub);
