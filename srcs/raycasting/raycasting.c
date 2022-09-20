/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:32:48 by rbony             #+#    #+#             */
/*   Updated: 2022/09/20 11:32:36 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

static void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > game->win_width - 1 || y < 0 || y > game->win_height - 1)
		return ;
	dst = game->img.addr + (y * game->img.line_length + x
			* (game->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	set_color(int side)
{
	if (side == 0)
		return (0xFF0000);
	else if (side == 1)
		return (0x00FF00);
	else if (side == 2)
		return (0x0000FF);
	else
		return (0xFFFF00);
}

static void	draw_column(t_game *game, int x, t_raycasting *ray)
{
	int	i;
	int	y;
	int	len;
	int	tmpy;

	len = game->win_height / ray->perp_dist;
	y = game->win_height / 2 - len / 2;
	i = 0;
	while (y + i < y + len)
	{
		tmpy = y + i;
		my_mlx_pixel_put(game, x, tmpy, set_color(ray->side));
		i++;
	}
}

static void	draw_background(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->win_height)
	{
		j = 0;
		while (j < game->win_width)
		{
			if (i < game->win_height / 2)
				my_mlx_pixel_put(game, j, i, 0xC0DFEF);
			else
				my_mlx_pixel_put(game, j, i, 0x333333);
			j++;
		}
		i++;
	}
}

void	raycasting(t_game *game)
{
	int				nbr;
	float			ra;
	t_raycasting	ray;
	t_point			col;

	draw_background(game);
	nbr = 0;
	ra = game->pa + (M_PI / 3) / 2;
	while (nbr < game->win_width)
	{
		ray = dda(game, ra);
		col = create_vect(game->player, ra, ray.perp_dist);
		draw_column(game, nbr, &ray);
		ra -= fixang((M_PI / 3) / game->win_width);
		nbr++;
	}
}