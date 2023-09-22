/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:37:45 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/22 11:45:19 by llevasse         ###   ########.fr       */
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
				cub->player.px = ((j - 1) * cub->minimap->block_w);
				j = cub->minimap->map[i][j - 1];
				cub->player.py = (i * cub->minimap->block_h);
				cub->player.pa = get_player_start_orientation(j);
				return ;
			}
		}
		i++;
	}
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
