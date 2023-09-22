/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:37:45 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/22 23:57:33 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_cub *cub)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (i < cub->minimap->nb_line)
	{
		j = 0;
		len = ft_strlen(cub->minimap->map[i]);
		while (j < len)
		{
			if (ft_is_in_str("NSEW", cub->minimap->map[i][j++]))
			{
				cub->player.pa = get_player_start_orientation(cub->minimap->map[i][j - 1]);
				cub->player.px = ((j - 1) * cub->minimap->block_h);
				cub->player.py = (i * cub->minimap->block_h);
			}
		}
		i++;
	}
	cub->player.px += cub->minimap->block_h / 2;
	cub->player.py += cub->minimap->block_h / 2;
}

int	get_player_start_orientation(char c)
{
	if (c == 'E')
		return (0);
	if (c == 'S')
		return (90);
	if (c == 'W')
		return (180);
	if (c == 'N')
		return (270);
	return (0);
}
