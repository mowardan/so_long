/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 09:59:46 by mowardan          #+#    #+#             */
/*   Updated: 2025/02/26 15:05:06 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

int	initialize_game(t_henix *henix, char *map_file, int *height, int *width)
{
	henix->map = read_map(map_file);
	if (!henix->map)
		return (ft_putstr("Error\nCouldn't read the map.\n"), 1);
	henix->collected = 0;
	*height = 0;
	while (henix->map[*height])
		(*height)++;
	if (!check_characters(henix) || !check_rectangular(henix->map)
		|| !check_walls(henix->map, *height, width)
		|| !check_valid_path(henix->map, *height) || check_valide_char(henix,
			*height))
	{
		free_map(henix->map);
		return (1);
	}
	return (0);
}

int	check_ber(char *str, char *ber)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '.')
		{
			while (str[i + j] && str[i + j] == ber[j])
				j++;
			if (ber[j] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_henix	henix;

	int (height), width;
	henix.moves = 0;
	if (ac != 2 || check_ber(av[1], ".ber") == 0)
		return (ft_putstr("Error\nUsage: <map_file.ber>\n"), 1);
	if (initialize_game(&henix, av[1], &height, &width))
		return (1);
	henix.mlx = mlx_init();
	if (henix.mlx == NULL)
		return (1);
	henix.win = mlx_new_window(henix.mlx, (width * 64), (height * 64),
			"so_long");
	load_images(&henix);
	map_display(&henix);
	mlx_key_hook(henix.win, handle_input, &henix);
	mlx_hook(henix.win, 17, 1, close_win, &henix);
	mlx_loop(henix.mlx);
	return (0);
}
