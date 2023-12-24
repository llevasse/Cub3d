/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 23:48:52 by llevasse          #+#    #+#             */
/*   Updated: 2023/12/24 23:03:28 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_rgb_value(char *s, int *value, char *err)
{
	int		r;
	int		g;
	int		b;
	char	*tmp;

	tmp = ft_strsep(&s, ", \t");
	if (tmp[0] == '\n')
		return ((void)ft_putstr_fd(err, 2), 0);
	r = no_higher(ft_atoi(tmp), 255, 0);
	tmp = ft_strsep(&s, ", \t");
	if (tmp[0] == '\n')
		return ((void)ft_putstr_fd(err, 2), 0);
	g = no_higher(ft_atoi(tmp), 255, 0);
	tmp = ft_strsep(&s, ", \t");
	if (tmp[0] == '\n')
		return ((void)ft_putstr_fd(err, 2), 0);
	b = no_higher(ft_atoi(tmp), 255, 0);
	*value = (r * 256 * 256) + (g * 256) + b;
	return (1);
}

int	do_open(char *s, t_img *img, int face, t_cub *cub)
{
	int	w;
	int	h;

	while (*s && ft_isspace(*s))
		s++;
	img->mlx_img = mlx_xpm_file_to_image(cub->mlx_ptr,
			ft_strsep(&s, "\n\r\t "), &w, &h);
	if (img->mlx_img == NULL && face == 0)
		return ((void)ft_putstr_fd(N_WALL_OPEN_ERR, 2), 0);
	if (img->mlx_img == NULL && face == 1)
		return ((void)ft_putstr_fd(S_WALL_OPEN_ERR, 2), 0);
	if (img->mlx_img == NULL && face == 2)
		return ((void)ft_putstr_fd(W_WALL_OPEN_ERR, 2), 0);
	if (img->mlx_img == NULL && face == 3)
		return ((void)ft_putstr_fd(E_WALL_OPEN_ERR, 2), 0);
	if (img->mlx_img == NULL && face == 4)
		return ((void)ft_putstr_fd(DOOR_OPEN_ERR, 2), 0);
	img->width = w;
	img->height = h;
	return (1);
}

int	get_wall(char *str, t_map *map, t_cub *cub)
{
	char	*id;


	str = pass_space(str);
	id = ft_strsep(&str, " \t");
	if (!ft_strcmp("NO", id) && map->north_img.mlx_img == 0)
		return (do_open(str, &map->north_img, 0, cub));
	if (!ft_strcmp("SO", id) && map->south_img.mlx_img == 0)
		return (do_open(str, &map->south_img, 1, cub));
	if (!ft_strcmp("WE", id) && map->west_img.mlx_img == 0)
		return (do_open(str, &map->west_img, 2, cub));
	if (!ft_strcmp("EA", id) && map->east_img.mlx_img == 0)
		return (do_open(str, &map->east_img, 3, cub));
	if (!ft_strcmp("F", id) && map->f_rgb == -1)
		return (get_rgb_value(str, &map->f_rgb, F_ERR));
	if (!ft_strcmp("C", id) && map->c_rgb == -1)
		return (get_rgb_value(str, &map->c_rgb, C_ERR));
	if (!ft_strcmp("DOOR", id) && map->door_img.mlx_img == 0)
		return (do_open(str, &map->door_img, 4, cub));
	return ((void)ft_putstr_fd(INVALID_CUB, 2), 0);
}
