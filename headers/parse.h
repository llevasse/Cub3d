/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:13:25 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/23 22:15:28 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//srcs/parsing/get_map.c
int		get_map(int map_fd, t_map *map, t_cub *cub);
int		search_player_presence(t_map *map, t_cub *cub, char *s);

//srcs/parsing/get_wall.c
int		get_wall(int map_fd, t_map *map, t_cub *cub, int *max);

//srcs/parsing/is_map_closed.c
int		check_closed(t_cub *cub, int x, int y);
int		fload(t_cub *cub, int x, int y);
int		get_tab_len(char **tab);

//srcs/parsing/parce.c
t_map	*parse(int map_fd, t_cub *cub);
void	close_walls(t_cub *cub, t_map *map);
int		is_line_empty(char *str);
void	set_map_null(t_map *map);
void	get_side_data_addrs(t_map *map, int max);
