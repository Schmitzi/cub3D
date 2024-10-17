/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:03:38 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/25 18:00:58 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static int	key_down(int keycode, t_player *player)
{
	t_map	*map;

	if (keycode == K_ESC)
		exit_game();
	if (keycode == K_G)
		player->keys[DEBUG_SHOW_GRAPH] = !player->keys[DEBUG_SHOW_GRAPH];
	if (keycode == K_M)
		player->keys[COOL_WALLS_ACTIVE] = !player->keys[COOL_WALLS_ACTIVE];
	if (keycode == K_F)
	{
		map = *get_map(NULL);
		toggle_door(player, map, 0);
	}
	player->keys[keycode] = true;
	return (0);
}

static int	key_up(int keycode, t_player *player)
{
	player->keys[keycode] = false;
	return (0);
}

static int	mouse_move(int x, int y, t_mouse *mouse)
{
	mouse->pos.x = x;
	mouse->pos.y = y;
	return (0);
}

static int	mouse_ignore(int button, int x, int y, t_mouse *mouse)
{
	(void)button;
	(void)x;
	(void)y;
	(void)mouse;
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
	mlx_hook(mlx->window, 6, 1L << 6, &mouse_move, &config->mouse);
	mlx_hook(mlx->window, 4, 1L << 2, &mouse_ignore, &config->mouse);
	mlx_hook(mlx->window, 5, 1L << 3, &mouse_ignore, &config->mouse);
	mlx_loop_hook(mlx->xvar, loop_hook, config);
}
