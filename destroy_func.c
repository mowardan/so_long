/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:37:38 by mowardan          #+#    #+#             */
/*   Updated: 2025/02/22 21:35:00 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_input(int key, t_henix *henix)
{
	if (key == XK_Escape)
	{
		destroy_henix(henix);
		exit(0);
	}
	if (key == XK_Up || key == XK_w)
	{
		henix_moves(henix, 0, -1);
	}
	if (key == XK_Down || key == XK_s)
	{
		henix_moves(henix, 0, 1);
	}
	if (key == XK_Left || key == XK_a)
	{
		henix_moves(henix, -1, 0);
	}
	if (key == XK_Right || key == XK_d)
	{
		henix_moves(henix, 1, 0);
	}
	return (0);
}

void	free_henix(t_henix *henix)
{
	int	i;

	if (henix->map)
	{
		i = 0;
		while (henix->map[i])
		{
			free(henix->map[i]);
			i++;
		}
		free(henix->map);
		henix->map = NULL;
	}
}

void	destroy_henix(t_henix *henix)
{
	if (!henix)
		return ;
	free_henix(henix);
	if (henix->mlx)
	{
		if (henix->wall)
			mlx_destroy_image(henix->mlx, henix->wall);
		if (henix->floor)
			mlx_destroy_image(henix->mlx, henix->floor);
		if (henix->player)
			mlx_destroy_image(henix->mlx, henix->player);
		if (henix->collectible)
			mlx_destroy_image(henix->mlx, henix->collectible);
		if (henix->exit)
			mlx_destroy_image(henix->mlx, henix->exit);
		if (henix->win)
			mlx_destroy_window(henix->mlx, henix->win);
		mlx_destroy_display(henix->mlx);
		free(henix->mlx);
		henix->mlx = NULL;
	}
}

int	close_win(t_henix *henix)
{
	if (henix->mlx)
	{
		destroy_henix(henix);
		exit(0);
	}
	return (0);
}

int	check_valide_char(t_henix *henix, int height)
{
	int (i), j;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (henix->map[i][j])
		{
			if (henix->map[i][j] != 'P' && henix->map[i][j] != 'E'
				&& henix->map[i][j] != 'C' && henix->map[i][j] != '1'
				&& henix->map[i][j] != '0' && henix->map[i][j] != '\n')
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
