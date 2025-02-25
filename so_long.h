/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 10:01:19 by mowardan          #+#    #+#             */
/*   Updated: 2025/02/23 09:14:57 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "/usr/include/minilibx-linux/mlx.h"
# include "get_next_line.h"
# include <X11/keysym.h>
# include <fcntl.h>

typedef struct s_henix
{
	void	*mlx;
	void	*win;
	void	*wall;
	void	*floor;
	void	*player;
	void	*collectible;
	void	*exit;
	char	**map;
	int		total_collectibles;
	int		collected;
	int		moves;
}			t_henix;

char		**read_map(char *av);
int			check_characters(t_henix *henix);
int			count_lines(char *av);
int			check_rectangular(char **rd_map);
int			check_walls(char **rd_map, int height, int *width);
int			check_valid_path(char **rd_map, int height);
void		flood_fill(char **rd_map, int x, int y);
char		**duplicate_map(char **rd_map, int height);
void		load_images(t_henix *henix);
void		map_display(t_henix *henix);
int			handle_input(int key, t_henix *henix);
void		henix_moves(t_henix *henix, int dx, int dy);
void		destroy_henix(t_henix *henix);
void		free_map(char **map);
void		free_henix(t_henix *henix);
void		ft_putstr(char *s);
void		ft_putnbr(int nbr);
void		ft_putnbrnl(int nbr);
int			initialize_game(t_henix *henix, char *map_file, int *height,
				int *width);
int			close_win(t_henix *henix);
int			check_valide_char(t_henix *henix, int height);
int			check_ber(char *str, char *ber);

#endif
