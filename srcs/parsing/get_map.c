/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:01:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/24 16:16:33 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_line(char *str);
static int	search_door(t_cub *cub, t_map *map, char *s);

char *pass_space(char *s)
{
	char *str;

	str = s;
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

int	get_map(int map_fd, t_map *map, t_cub *cub, int elements)
{
	char	*str;
	char	*tmp;
	int		i;

	str = "";
	tmp = get_next_line(map_fd);
	i = 0;
	while (tmp)
	{
		ft_add_garbage(&map->garbage, tmp);
		while (tmp && is_line_empty(tmp))
		{
			tmp = get_next_line(map_fd);
			if (tmp)
				ft_add_garbage(&map->garbage, tmp);
		}
		if (!tmp)
			break ;
		if (i == 0 && elements == 6 && map->door_img.mlx_img == 0
			&& !ft_strncmp("DOOR", pass_space(tmp), 4))
		{
			if (!search_door(cub, map, tmp))
				return (0);
		}
		else
		{
			str = ft_strjoin(str, tmp);
			ft_add_garbage(&map->garbage, str);
		}
		tmp = get_next_line(map_fd);
		i++;
	}
	if (!search_player_presence(map, cub, str) || !valid_line(str))
		return (0);
	return (1);
}

int	valid_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_in_str("NSEW01CO\n\t \r", str[i]))
			return ((ft_putstr_fd(INVALID_MAP_LINE, 2)), 0);
		i++;
	}
	return (1);
}

static int	search_door(t_cub *cub, t_map *map, char *s)
{
	ft_strsep(&s, " \t");
	if (!do_open(s, &map->door_img, 4, cub))
		return (0);
	map->door_img.addr = mlx_get_data_addr(map->door_img.mlx_img,
		&map->door_img.bpp, &map->door_img.line_len,
		&map->door_img.endian);
	return (1);
}

int	check_player_in_string(t_point *p, int y, int x, char *str)
{
	if (ft_is_in_str("NSEW", str[x]))
	{
		p->x = x;
		p->y = y;
		return (1);
	}
	return (0);
}

int	search_player_presence(t_map *map, t_cub *cub, char *s)
{
	t_point	p;
	int		y;
	int		x;
	int		nb;
	char	**split;

	split = ft_split(s, '\n');
	ft_add_garbage(&map->garbage, split);
	y = 0;
	nb = 0;
	while (y < get_tab_len(split))
	{
		ft_add_garbage(&map->garbage, split[y]);
		x = 0;
		while (split[y][x])
			nb += check_player_in_string(&p, y, x++, split[y]);
		y++;
	}
	if (nb > 1)
		return ((ft_putstr_fd(TMP, 2)), 0);
	if (nb == 0)
		return ((ft_putstr_fd(NO_PLAYER, 2)), 0);
	cub->mmap->map = split;
	return (check_closed(cub, p.x, p.y));
}
