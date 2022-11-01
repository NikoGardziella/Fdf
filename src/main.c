/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngardzie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:40:29 by ngardzie          #+#    #+#             */
/*   Updated: 2022/01/24 11:40:33 by ngardzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom(float *x1, float *y1, t_fdf *map)
{
	if (map->zoom < 0)
		map->zoom = 0;
	if (map->elevation < 0)
		map->elevation = 0;
	map->x = map->x * map->zoom;
	map->y = map->y * map->zoom;
	*x1 = *x1 * map->zoom;
	*y1 = *y1 * map->zoom;
}

int	check_type(int key, t_fdf *map)
{
	if (key == 18)
		map->type = 1;
	if (key == 19)
		map->type = 2;
	if (key == 20)
		map->type = 3;
	if (key == 123)
		map->move_x -= 50;
	if (key == 124)
		map->move_x += 50;
	if (key == 126)
		map->move_y -= 50;
	if (key == 125)
		map->move_y += 50;
	return (0);
}

static int	keydown(int key, t_fdf *map)
{
	check_type (key, map);
	if (key == 53)
		exit (1);
	if (key == 15 && map->elevation >= 0 && map->zoom >= 0)
	{
		map->elevation += 0.5;
		map->zoom += 3;
	}
	if (key == 3 && map->elevation >= 0 && map->zoom >= 0)
	{
		map->elevation -= 0.5;
		map->zoom -= 3;
	}
	if (key == 13)
		map->elevation += 0.2;
	if (key == 12)
		map->elevation -= 0.2;
	if (key == 0)
		map->angle -= 0.2;
	if (key == 1)
		map->angle += 0.2;
	mlx_clear_window (map->mlx_ptr, map->win_ptr);
	map_drawer (map);
	return (0);
}

void	initialize(t_fdf *map)
{
	void	*mlx;
	void	*win;

	mlx = map->mlx_ptr;
	win = map->win_ptr;
	mlx_string_put (mlx, win, 20, 20, 0x0000FF, "How to use");
	mlx_string_put (mlx, win, 20, 40, 0x0000FF, "Use arrow keys \
	to move the map");
	mlx_string_put (mlx, win, 20, 60, 0x0000FF, "Use 1, 2, 3 to \
	change projection");
	mlx_string_put (mlx, win, 20, 80, 0x0000FF, "Use R and F to zoom");
	mlx_string_put (mlx, win, 20, 100, 0x0000FF, "Use A and S to change angle");
	map->move_x = 400;
	map->move_y = 400;
	map->angle = 0.5;
	map->elevation = 10;
}

int	main(int argc, char **argv)
{
	t_fdf	*map;
	int		i;

	map = (t_fdf *)malloc(sizeof(t_fdf));
	if (map == NULL)
		return (ft_fail("error: invalid input"));
	if (argc != 2)
		return (ft_fail("error:invalid argument"));
	read_file(argv[1], map);
	map->mlx_ptr = mlx_init();
	map->win_ptr = mlx_new_window(map->mlx_ptr, 1400, 1400, "FDF");
	initialize(map);
	map_drawer(map);
	mlx_key_hook(map->win_ptr, keydown, map);
	mlx_loop(map->mlx_ptr);
	i = 0;
	while (map->z_matrix[i])
	{
		free(map->z_matrix[i]);
		i++;
	}
	free(map);
	return (0);
}
