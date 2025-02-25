/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working_on_images.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:39:59 by mowardan          #+#    #+#             */
/*   Updated: 2025/02/15 15:12:54 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_images(t_henix *henix)
{
	int (w), h;
	henix->wall = mlx_xpm_file_to_image(henix->mlx, "textures/walls.xpm", &w,
			&h);
	henix->floor = mlx_xpm_file_to_image(henix->mlx, "textures/white-_2_.xpm",
			&w, &h);
	henix->player = mlx_xpm_file_to_image(henix->mlx, "textures/henix.xpm", &w,
			&h);
	henix->collectible = mlx_xpm_file_to_image(henix->mlx,
			"textures/02-_1_.xpm", &w, &h);
	henix->exit = mlx_xpm_file_to_image(henix->mlx, "textures/myexit-_1_.xpm",
			&w, &h);
}

void	map_display(t_henix *henix)
{
	int (x), y;
	y = 0;
	while (henix->map[y])
	{
		x = 0;
		while (henix->map[y][x])
		{
			mlx_put_image_to_window(henix->mlx, henix->win, henix->floor, x
				* 64, y * 64);
			if (henix->map[y][x] == '1')
				mlx_put_image_to_window(henix->mlx, henix->win, henix->wall, x
					* 64, y * 64);
			else if (henix->map[y][x] == 'P')
				mlx_put_image_to_window(henix->mlx, henix->win, henix->player, x
					* 64, y * 64);
			else if (henix->map[y][x] == 'C')
				mlx_put_image_to_window(henix->mlx, henix->win,
					henix->collectible, x * 64, y * 64);
			else if (henix->map[y][x] == 'E')
				mlx_put_image_to_window(henix->mlx, henix->win, henix->exit, x
					* 64, y * 64);
			x++;
		}
		y++;
	}
}

static void	find_player_pos(t_henix *henix, int *x, int *y)
{
	*y = 0;
	while (henix->map[*y])
	{
		*x = 0;
		while (henix->map[*y][*x])
		{
			if (henix->map[*y][*x] == 'P')
				return ;
			(*x)++;
		}
		(*y)++;
	}
}

static char	handle_exit_pos(char tmp)
{
	if (tmp == 'E')
		return ('E');
	else
		return ('0');
}

void	henix_moves(t_henix *henix, int dx, int dy)
{
	static char	pos = '0';
	char		tmp;

	int (x), y;
	find_player_pos(henix, &x, &y);
	if (henix->map[y + dy][x + dx] == '1')
		return ;
	if (henix->map[y + dy][x + dx] == 'E'
		&& henix->collected == henix->total_collectibles)
	{
		ft_putstr("henix win");
		destroy_henix(henix);
		exit(0);
	}
	if (henix->map[y + dy][x + dx] == 'C')
	{
		henix->map[y + dy][x + dx] = '0';
		henix->collected++;
	}
	tmp = henix->map[y + dy][x + dx];
	henix->map[y][x] = pos;
	pos = handle_exit_pos(tmp);
	henix->map[y + dy][x + dx] = 'P';
	ft_putnbrnl(henix->moves++);
	map_display(henix);
}
