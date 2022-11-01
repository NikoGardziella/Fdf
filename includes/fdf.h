/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngardzie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:26:10 by ngardzie          #+#    #+#             */
/*   Updated: 2022/01/26 10:27:27 by ngardzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/get_next_line.h"
# include <math.h>
# include "../minilibx/mlx.h"
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_fdf
{
	int		height;
	int		width;
	float	x;
	float	y;
	int		**z_matrix;
	void	*win_ptr;
	void	*mlx_ptr;
	int		zoom;
	int		color;
	int		move_x;
	int		move_y;
	double	angle;
	float	elevation;
	int		type;
}			t_fdf;

/*
* main.c
*/

int			check_type(int key, t_fdf *map);
void		initialize(t_fdf *map);
void		zoom(float *x1, float *y1, t_fdf *map);

/*
* reader.c
*/

void		fill_map(int *z_line, char *line);
void		map_size(char *file, t_fdf *map);
void		read_file(char *file, t_fdf *map);

/*
* drawer.c
*/

void		color(int z, t_fdf *map);
void		draw_iso(float *x, float *y, int z, t_fdf *map);
void		rasterisation(float x1, float y1, t_fdf *map);
void		draw(float x1, float y1, t_fdf *map);
void		map_drawer(t_fdf *map);

#endif
