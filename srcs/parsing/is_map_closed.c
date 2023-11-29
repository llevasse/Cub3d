/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 21:56:14 by llevasse          #+#    #+#             */
/*   Updated: 2023/11/29 19:48:49 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	fload(t_cub *cub, int x, int y);

int	check_closed(t_cub *cub, int x, int y)
{
	if (!fload(cub, x, y))
	{
		ft_putstr_fd(OPEN_MAP, 2);
		return (0);
	}
	y = 0;
	while (cub->mmap->map[y])
	{
		x = 0;
		if (ft_is_in_str(cub->mmap->map[y], '0')){
			ft_putstr_fd(ISLAND_MAP, 2);
			return (0);
		}
		while (x < (int)ft_strlen(cub->mmap->map[y]))
		{
			if (cub->mmap->map[y][x] == 'A')
				cub->mmap->map[y][x] = '0';
			x++;
		}
		y++;
	}
	return (1);
}

static int	fload(t_cub *cub, int x, int y)
{
	if (y < 0 || x < 0)
		return (0);
	if (x > (int)ft_strlen(cub->mmap->map[y]))
		return (0);
	if (cub->mmap->map[y][x] == '1' || cub->mmap->map[y][x] == 'A')
		return (1);
	if (!ft_is_in_str("0NSEW", cub->mmap->map[y][x]))
		return (0);
	else if (cub->mmap->map[y][x] == '0')
		cub->mmap->map[y][x] = 'A';
	if (fload(cub, x - 1, y) && fload(cub, x + 1, y) && \
		fload(cub, x, y - 1) && fload(cub, x, y + 1))
		return (1);
	return (0);
}

int	get_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}
