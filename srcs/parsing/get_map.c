/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <llevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 12:01:04 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/19 12:11:19 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map(int map_file_fd)
{
	char	*str;
	char	*tmp;

	str = "";
	tmp = get_next_line(map_fd);
	while (tmp)
	{
		while (tmp && is_line_empty(tmp))
			tmp = get_next_line(map_fd);
		if (!tmp)
			break ;
		str = ft_strjoin(str, tmp);
	}
}
