/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 23:42:30 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/19 21:30:19 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

# include "cub3d.h"

# define MEM_ERR "Error\nError while allocating memory.\n"
# define N_WALL_OPEN_ERR "Error\nError in opening north wall texture file.\n"
# define S_WALL_OPEN_ERR "Error\nError in opening south wall texture file.\n"
# define E_WALL_OPEN_ERR "Error\nError in opening east wall texture file.\n"
# define W_WALL_OPEN_ERR "Error\nError in opening west wall texture file.\n"
# define CUB_OPEN_ERR "Error\nError in opening cub file.\n"
# define MISS_F "Error\n.cub file is missing.\n"
# define INVALID_CUB "Error\n.cub file is invalid.\n"
# define TMP "Error\nToo many player in the map file.\n"
# define NO_PLAYER "Error\nThere is no player in the map file.\n"

#endif
