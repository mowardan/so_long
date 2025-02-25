/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:00:58 by mowardan          #+#    #+#             */
/*   Updated: 2025/02/23 14:51:48 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_lines(char *av)
{
	int		line_count;
	char	*line;
	int		fd;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (0);
	line_count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (line_count);
}

char	**read_map(char *av)
{
	char	*a;
	char	**rd_map;

	int (line_count), fd, i;
	i = 0;
	line_count = count_lines(av);
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (NULL);
	rd_map = malloc(sizeof(char *) * (line_count + 1));
	if (!rd_map)
		return (NULL);
	a = get_next_line(fd);
	while (a)
	{
		rd_map[i] = ft_strdup(a);
		free(a);
		if (!rd_map[i])
			return (free_map(rd_map), NULL);
		a = get_next_line(fd);
		i++;
	}
	rd_map[i] = NULL;
	close(fd);
	return (rd_map);
}

int	check_characters(t_henix *henix)
{
	int (p), e, c, i, j;
	p = 0;
	c = 0;
	e = 0;
	i = 0;
	while (henix->map[i])
	{
		j = 0;
		while (henix->map[i][j])
		{
			if (henix->map[i][j] == 'P')
				p++;
			if (henix->map[i][j] == 'E')
				e++;
			if (henix->map[i][j] == 'C')
				c++;
			j++;
		}
		i++;
	}
	henix->total_collectibles = c;
	if (p != 1 || e != 1 || c < 1)
		return (ft_putstr("Error\nInvalid map\n"), 0);
	return (1);
}

int	check_rectangular(char **rd_map)
{
	int	width;
	int	i;

	i = 1;
	width = ft_strlen2(rd_map[0]);
	while (rd_map[i])
	{
		if (ft_strlen2(rd_map[i]) != width)
		{
			ft_putstr("Error\nmap must be rectangular.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_walls(char **rd_map, int height, int *width)
{
	int	i;

	*width = 0;
	while (rd_map[0][*width] && rd_map[0][*width] != '\n')
		(*width)++;
	i = 0;
	while (i < *width)
	{
		if (rd_map[0][i] != '1' || rd_map[height - 1][i] != '1')
			return (ft_putstr("Error\nInvalid map: must be closed by walls.\n"),
				0);
		i++;
	}
	i = 0;
	while (i < height)
	{
		if (rd_map[i][0] != '1' || rd_map[i][*width - 1] != '1')
			return (ft_putstr("Error\nInvalid map: must be closed by walls.\n"),
				0);
		i++;
	}
	return (1);
}
