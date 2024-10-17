/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:03:38 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/25 01:17:02 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	key_down(int keycode, t_player *player)
{
	if (keycode == K_ESC)
		exit_game();
	if (keycode == K_G)
		player->keys[DEBUG_SHOW_GRAPH] = !player->keys[DEBUG_SHOW_GRAPH];
	player->keys[keycode] = true;
	return (0);
}

static int	key_up(int keycode, t_player *player)
{
	player->keys[keycode] = false;
	return (0);
}

void	init_hooks(t_mlx *mlx)
{
	t_player	*player;
	t_config	*config;

	player = *get_player(NULL);
	config = *get_config(NULL);
	mlx_hook(mlx->window, 3, 1L << 1, &key_up, player);
	mlx_hook(mlx->window, 2, 1L << 0, &key_down, player);
	mlx_hook(mlx->window, 17, 1L << 17, &exit_game, player);
	mlx_loop_hook(mlx->xvar, loop_hook, config);
}
