/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngardzie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 09:54:47 by ngardzie          #+#    #+#             */
/*   Updated: 2022/03/21 09:54:49 by ngardzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	color(int z, t_fdf *map)
{
	if (z < -5)
		map->color = 0x7499FE;
	else if (z < 0 && z > -5)
		map->color = 0xBDCEFE;
	else if (z == 0)
		map->color = 0xFFF2F2;
	else if (z <= 3 && z > 0)
		map->color = 0x990101;
	else if (z <= 6 && z > 3)
		map->color = 0xC80000;
	else if (z <= 9 && z > 6)
		map->color = 0xDF0000;
	else if (z > 9)
		map->color = 0xFF0000;
}

void	draw_iso(float *x, float *y, int z, t_fdf *map)
{
	*x = (*x - *y) * cos(map->angle);
	*y = (*x + *y) * sin(map->angle) - z * map->elevation;
}

void	rasterisation(float x1, float y1, t_fdf *map)
{
	float	x_draw;
	float	y_draw;
	int		max;
	float	x;
	float	y;

	x = map->x;
	y = map->y;
	x_draw = x1 - x;
	y_draw = y1 - y;
	max = ft_higher_float(ft_absolute(x_draw), ft_absolute(y_draw));
	x_draw = x_draw / max;
	y_draw = y_draw / max;
	while ((int)(x - x1) != 0 || (int)(y - y1) != 0)
	{
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, x, y, map->color);
		x = x + x_draw;
		y = y + y_draw;
	}
}

void	draw(float x1, float y1, t_fdf *map)
{
	int	z;
	int	z1;

	z = map->z_matrix[(int)map->y][(int)map->x];
	z1 = map->z_matrix[(int)y1][(int)x1];
	zoom(&x1, &y1, map);
	if (map->type >= 2)
	{
		if (map->type == 3)
			map->angle = 0;
		draw_iso(&map->x, &map->y, z, map);
		draw_iso(&x1, &y1, z1, map);
	}
	map->x = map->x + map->move_x;
	map->y = map->y + map->move_y;
	x1 = x1 + map->move_x;
	y1 = y1 + map->move_y;
	color(z, map);
	rasterisation(x1, y1, map);
}

void	map_drawer(t_fdf *map)
{
	int	x;
	int	y;

	y = 0;
	map->y = y;
	while (y < map->height)
	{
		x = 0;
		map->x = x;
		while (x < map->width)
		{
			if (x < map->width - 1)
				draw(x + 1, y, map);
			map->y = y;
			map->x = x;
			if (y < map->height - 1)
				draw(x, y + 1, map);
			x++;
			map->x = x;
			map->y = y;
		}
		y++;
		map->y = y;
	}
}
