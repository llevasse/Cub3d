/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llevasse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:05:00 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/22 22:07:53 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

//srcs/render/render.c:
int		render(t_cub *cub);
void	img_pix_put(t_img *img, int x, int y, int colour);

//srcs/render/line.c:
void	draw_line(t_cub cub, int x2, int y2);
void	drawRays3D(t_cub cub);

//srcs/render/minimap.c:
void	draw_square(t_minimap *map, int x, int y, int colour);
void	draw_player(t_minimap *map, int x, int y, int colour);
void	draw_minimap(t_cub *cub);

//srcs/render/get_pixel_colour.c:
int		get_pixel_colour(t_img *img, int x, int y);

//srcs/render/collision.c:
int		check_w_smaller_mov(t_cub *cub, int angle, float *offset);
int		check_collision(t_cub *cub, int angle, float *offset);

//srcs/render/draw_fov.c:
void	draw_fov(t_cub *cub);
#endif
