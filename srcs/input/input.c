/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdutel <tdutel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 23:04:28 by llevasse          #+#    #+#             */
/*   Updated: 2023/09/22 12:36:55 by llevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_input(int keysym, t_cub *cub)
{
	float	offset;

	offset = 0.1 * cub->minimap->block_w;
	if (keysym == XK_w && !check_collision(cub, 0, &offset))
		set_player_new_pos(cub, 0, offset);
	if (keysym == XK_d && !check_collision(cub, 90, &offset))
		set_player_new_pos(cub, 90, offset);
	offset = -PLAYER_OFFSET;
	if (keysym == XK_s && !check_collision(cub, 0, &offset))
		set_player_new_pos(cub, 0, offset);
	if (keysym == XK_a && !check_collision(cub, 90, &offset))
		set_player_new_pos(cub, 90, offset);
	if (keysym == XK_Escape)
		return (close_window(cub), offset);
	rotate_input(keysym, cub);
	// draw_line(*cub, cub->player.px + cub->player.pdx * 5, cub->player.py + cub->player.pdy * 5);
	return (0);
}

int	close_window(t_cub *cub)
{
	mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	if (cub->minimap->img.mlx_img)
		mlx_destroy_image(cub->mlx_ptr, cub->minimap->img.mlx_img);
	mlx_destroy_display(cub->mlx_ptr);
	free_garbage(cub->garbage);
	exit(0);
}


/*	rotate_input print dans le terminal l'angle
 d'inclinaison des que les arrows keys sont utilisées */

int	rotate_input(int keysym, t_cub *cub)
{
	if (keysym == XK_Left)
		cub->player.pa--;
	if (keysym == XK_Right)
		cub->player.pa++;
	if (keysym == XK_Up)
	{
		cub->player.px += cub->player.pdx;
		cub->player.py += cub->player.pdy;
	}
	if (keysym == XK_Down)
	{
		cub->player.px -= cub->player.pdx;
		cub->player.py -= cub->player.pdy;
	}
	return (0);
}

// Fonction pour tracer une ligne avec la minilibX
void	draw_line(t_cub cub, int x2, int y2)
{
	int			dx;
	int			dy;
	int			steps;
	t_player	nb;

	dx = x2 - cub.player.px;
	dy = y2 - cub.player.py;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	nb.pdx = (float) dx / steps;
	nb.pdy = (float) dy / steps;
	nb.px = cub.player.px + 10;
	nb.py = cub.player.py + 10;
	nb.pa = 0;
	while(nb.pa <= steps + 100)
	{
		img_pix_put(&cub.minimap->img, (int)nb.px, (int)nb.py, 0x222222);
//		mlx_pixel_put(cub.mlx_ptr, cub.win_ptr, (int)nb.px, (int)nb.py, 0x222222);
		nb.px += nb.pdx;
		nb.py += nb.pdy;
		nb.pa += 1;
	}
}

void	drawRays3D(t_cub cub)
{
	t_math	var;

	var.ra = cub.player.pa;
	var.r = 0;
	while (var.r < 1)
	{
		var.dof = 0;
		var.aTan = -1 / tan(var.ra);
		if (var.ra > PI)
		{
			printf("ry = %f\n", var.ry);
			var.ry = (((int)cub.player.py >> 6) << 6) - 0.0001;
			printf("ry = %f\n", var.ry);
			var.rx = (cub.player.py - var.ry) * var.aTan + cub.player.px;
			var.yo = -cub.minimap->maps;
			var.xo = -var.yo * var.aTan;
		}
		if (var.ra < PI)
		{
			var.ry = (((int)cub.player.py >> 6) << 6) + cub.minimap->maps;
			var.rx = (cub.player.py - var.ry) * var.aTan + cub.player.px;
			var.yo = cub.minimap->maps;
			var.xo = -var.yo * var.aTan;
		}
		if (var.ra == 0 || var.ra == PI)
		{
			var.rx = cub.player.px;
			var.ry = cub.player.py;
			var.dof = cub.minimap->mapy;
		}
		printf("raPI\n");
		while (var.dof < cub.minimap->mapy)
		{
			var.mx = (int)(var.rx) >> 6;
			var.my = (int)(var.ry) >> 6;
			printf("my = %d\n", cub.minimap->mapx[var.dof]);
			var.mp = var.my * cub.minimap->mapx[var.dof] + var.mx;
			if ((var.mp < cub.minimap->maps) && (cub.minimap->map[var.dof][var.mp % cub.minimap->mapy] == '1'))
				var.dof = cub.minimap->mapy;
			else
			{
				var.rx += var.xo;
				var.ry += var.yo;
				var.dof += 1;
			}
		}
		draw_line(cub, var.rx, var.ry);
		var.r++;
	}
}
