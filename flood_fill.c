/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:44:12 by mowardan          #+#    #+#             */
/*   Updated: 2025/02/23 14:50:51 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**duplicate_map(char **rd_map, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(rd_map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[height] = NULL;
	return (copy);
}

void	flood_fill(char **rd_map, int x, int y)
{
	if (rd_map[y][x] == '1' || rd_map[y][x] == 'X')
		return ;
	rd_map[y][x] = 'X';
	flood_fill(rd_map, x - 1, y);
	flood_fill(rd_map, x + 1, y);
	flood_fill(rd_map, x, y - 1);
	flood_fill(rd_map, x, y + 1);
}

static int	find_and_flood_fill(char **map_copy, int *x, int *y)
{
	*y = 0;
	while (map_copy[*y])
	{
		*x = 0;
		while (map_copy[*y][*x])
		{
			if (map_copy[*y][*x] == 'P')
			{
				flood_fill(map_copy, *x, *y);
				return (1);
			}
			(*x)++;
		}
		(*y)++;
	}
	return (0);
}

int	check_valid_path(char **rd_map, int height)
{
	char	**map_copy;

	int (x), y;
	map_copy = duplicate_map(rd_map, height);
	if (!map_copy)
		return (ft_putstr("Error\nFailed to duplicate map.\n"), 0);
	if (!find_and_flood_fill(map_copy, &x, &y))
	{
		free_map(map_copy);
		return (ft_putstr("Error\nStarting position 'P' not found.\n"), 0);
	}
	y = 0;
	while (map_copy[y])
	{
		x = 0;
		while (map_copy[y][x])
		{
			if (map_copy[y][x] == 'C' || map_copy[y][x] == 'E')
				return (ft_putstr("Error\nInvalidpath"), free_map(map_copy), 0);
			x++;
		}
		y++;
	}
	free_map(map_copy);
	return (1);
}
