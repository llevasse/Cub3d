/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 21:56:14 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/26 09:50:02 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_right(t_cub *cub, int x, int y);
static int	check_left(t_cub *cub, int x, int y);

int	check_closed(t_cub *cub, int x, int y)
{	
	if (!check_left(cub, x, y) || !check_right(cub, x, y))
		return (0);
	return (1);
}

static int	check_left(t_cub *cub, int x, int y)
{
	printf("check (%d:%d)\n", x, y);
	if (y < 0 || x < 0)
		return (0);
	if (x > (int)ft_strlen(cub->mmap->map[y]))
		return (0);
	if (cub->mmap->map[y][x] == '1')
		return (1);
	if (!ft_is_in_str("0NSEW", cub->mmap->map[y][x]))
		return (0);
	if (!check_closed(cub, x - 1, y) || !check_closed(cub, x, y - 1))
		return (0);
	return (1);
}

static int	check_right(t_cub *cub, int x, int y)
{
	printf("check (%d:%d)\n", x, y);
	if (y < 0 || x < 0)
		return (0);
	if (x > (int)ft_strlen(cub->mmap->map[y]))
		return (0);
	if (cub->mmap->map[y][x] == '1')
		return (1);
	if (!ft_is_in_str("0NSEW", cub->mmap->map[y][x]))
		return (0);
	if (!check_closed(cub, x + 1, y) || !check_closed(cub, x, y + 1))
		return (0);
	return (1);
}

int	get_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}
