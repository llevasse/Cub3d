/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:13:25 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/22 22:14:40 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//srcs/init/init_player.c:
void	init_player(t_cub *cub);
int		get_player_start_orientation(char c);

//srcs/init/init.c:
void	init_cub(t_cub *cub, char **argv);
void	init_minimap(t_cub *cub);
void	init_map_value(t_cub *cub);
