/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 21:56:14 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/26 16:36:46 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_right(t_cub *cub, int x, int y);
static int	check_left(t_cub *cub, int x, int y);
static int	check_up(t_cub *cub, int x, int y);
static int	check_down(t_cub *cub, int x, int y);

int	check_closed(t_cub *cub, int x, int y)
{	
	printf("player : %d:%d\n", x, y);
	if (!check_left(cub, x, y) || !check_right(cub, x, y) ||\
		!check_up(cub, x, y) || !check_down(cub, x, y))
	{
		ft_putstr_fd(OPEN_MAP, 2);
		return (0);
	}
	y = 0;
	while (y < cub->mmap->nb_line)
	{
		x = 0;
		while (x < (int)ft_strlen(cub->mmap->map[y]))
		{
			if (cub->mmap->map[y][x] == 'A')
				cub->mmap->map[y][x] = '0';
			x++;
		}
	}
	return (1);
}

static int	check_left(t_cub *cub, int x, int y)
{
	if (y < 0 || x < 0)
		return (0);
	if (x > (int)ft_strlen(cub->mmap->map[y]))
		return (0);
	if (cub->mmap->map[y][x] == '1' || cub->mmap->map[y][x] == 'A')
		return (1);
	if (!ft_is_in_str("0NSEW", cub->mmap->map[y][x]))
		return ((void)printf("(left)open at %d:%d\n", x, y), 0);
	else if (cub->mmap->map[y][x] == '0')
		cub->mmap->map[y][x] = 'A';
	if (check_left(cub, x - 1, y) && check_left(cub, x, y - 1) && \
		check_left(cub, x, y + 1))
		return (1);
	return (0);
}

static int	check_right(t_cub *cub, int x, int y)
{
	if (y < 0 || x < 0)
		return (0);
	if (x > (int)ft_strlen(cub->mmap->map[y]))
		return (0);
	if (cub->mmap->map[y][x] == '1' || cub->mmap->map[y][x] == 'A')
		return (1);
	if (!ft_is_in_str("0NSEW", cub->mmap->map[y][x]))
		return ((void)printf("(right)open at %d:%d\n", x, y), 0);
	else if (cub->mmap->map[y][x] == '0')
		cub->mmap->map[y][x] = 'A';
	if (!check_right(cub, x + 1, y) || !check_right(cub, x, y - 1) || \
		!check_right(cub, x, y + 1))
		return (0);
	return (1);
}

static int	check_up(t_cub *cub, int x, int y)
{
	if (y < 0 || x < 0)
		return (0);
	if (x > (int)ft_strlen(cub->mmap->map[y]))
		return (0);
	if (cub->mmap->map[y][x] == '1' || cub->mmap->map[y][x] == 'A')
		return (1);
	if (!ft_is_in_str("0NSEW", cub->mmap->map[y][x]))
		return ((void)printf("(up)open at %d:%d\n", x, y), 0);
	else if (cub->mmap->map[y][x] == '0')
		cub->mmap->map[y][x] = 'A';
	if (!check_up(cub, x, y - 1) || !check_up(cub, x - 1, y) || \
		!check_up(cub, x + 1, y))
		return (0);
	return (1);
}

static int	check_down(t_cub *cub, int x, int y)
{
	if (y < 0 || x < 0)
		return (0);
	if (x > (int)ft_strlen(cub->mmap->map[y]))
		return (0);
	if (cub->mmap->map[y][x] == '1' || cub->mmap->map[y][x] == 'A')
		return (1);
	if (!ft_is_in_str("0NSEW", cub->mmap->map[y][x]))
		return ((void)printf("(down)open at %d:%d\n", x, y), 0);
	else if (cub->mmap->map[y][x] == '0')
		cub->mmap->map[y][x] = 'A';
	if (!check_down(cub, x, y + 1) || !check_down(cub, x - 1, y) || \
		!check_down(cub, x + 1, y))
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
