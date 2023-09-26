/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 21:56:14 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/26 03:07:05 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_line_v_closed(char **tab, int x, int entry_y);
int	is_line_h_closed(char *line);

int	check_closed(t_cub *cub, int x, int y)
{	
	if (y < 0 || x < 0)
		return (0);
	if (x > (int)ft_strlen(cub->mmap->map[y]))
		return (0);
	if (cub->mmap->map[y][x] == '1')
		return (1);
	if (!ft_is_in_str("0NSEW", cub->mmap->map[y][x]))
		return (0);
	if (!check_closed(cub, x - 1, y) || !check_closed(cub, x + 1, y))
		return (0);
	if (!check_closed(cub, x, y - 1) || !check_closed(cub, x, y + 1))
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

int	is_line_h_closed(char *line)
{
	int	i;
	int	len;

	len = ft_strlen(line);
	i = 0;
	while (len > 0 && line[len] != '1')
	{
		if (line[len--] == '0')
			return (0);
	}
	while (i < len && line[i] != '1')
	{
		if (line[i++] == '0')
			return (0);
	}
	return (1);
}

int	is_line_v_closed(char **tab, int x, int entry_y)
{
	int	y;
	int	closed;

	closed = 0;
	y = entry_y;
	if (tab[y][x] != '0')
		return (1);
	while (y >= 0 && !closed)
	{
		if ((int)ft_strlen(tab[y]) >= x && tab[y][x] == '1')
			closed++;
		y--;
	}
	y = entry_y;
	while (y < get_tab_len(tab))
	{
		if ((int)ft_strlen(tab[y]) >= x && tab[y][x] == '1' && closed)
			return (closed);
		y++;
	}
	return (0);
}
