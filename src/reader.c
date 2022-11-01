/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngardzie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:53:24 by ngardzie          #+#    #+#             */
/*   Updated: 2022/03/04 10:53:26 by ngardzie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fill_map(int *z_line, char *line)
{
	char	**split;
	int		i;

	split = ft_strsplit(line, ' ');
	i = 0;
	while (split[i])
	{
		z_line[i] = ft_atoi(split[i]);
		free(split[i]);
		if (z_line[i] > 100)
			z_line[i] = 100;
		else if (z_line[i] < -100)
			z_line[i] = -100;
		i++;
	}
	free(split);
}

void	map_size(char *file, t_fdf *map)
{
	int		fd;
	char	*line;
	int		x;
	int		y;

	y = 0;
	fd = 0;
	x = -1;
	fd = open(file, O_RDONLY, 0);
	if (!fd)
		ft_fail("error: invalid input");
	while (get_next_line(fd, &line) == 1)
	{
		if (x == -1)
		{
			x = (int)ft_word_count(line, ' ');
			map->width = x;
		}
		x = (int)ft_word_count(line, ' ');
		if (x != map->width || x < 1)
			ft_fail("error: invalid input");
		y++;
		free(line);
	}
	map->height = y;
}

void	read_file(char *file, t_fdf *map)
{
	char	*line;
	int		i;
	int		fd;

	fd = open(file, O_DIRECTORY);
	if (fd >= 0)
		ft_fail("error: directory is not valid input");
	map_size(file, map);
	map->z_matrix = (int **)malloc(sizeof(int *) * (map->height + 1));
	i = 0;
	while (i <= map->height)
	{
		map->z_matrix[i] = (int *)malloc(sizeof(int) * (map->width + 1));
		i++;
	}
	i = 0;
	fd = open(file, O_RDONLY, 0);
	while (get_next_line(fd, &line) == 1)
	{
		fill_map(map->z_matrix[i], line);
		free(line);
		i++;
	}
	map->zoom = 700 / (map->height + map->width);
	close(fd);
}
