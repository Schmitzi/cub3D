/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:28:20 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/24 23:57:10 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	init_engine(t_engine *engine)
{
	ft_bzero(engine, sizeof(t_engine));
	engine->tick_rate = DEFAULT_ENGINE_FPS;
	engine->last_tick = get_precise_time();
	engine->tick_duration = 1.0f / engine->tick_rate;
}

// calculate the difference between the current and previous mouse position
// and rotate the player's view accordingly
// abstract into rotate_player() function
// FIXME: for some reason, before the first mouse move some weird stuff happens
// with the player's view. it faces the wrong direction, sometimes it snaps
// back as soon as the mouse is touched. sometimes the direction is correct.
// it boggles the mind.
// rotate keys technically need delta_time
static void	process_mouse_move(t_mouse *mouse, t_player *player,
		double delta_time)
{
	t_point	delta;
	t_point	dir;
	double	s;
	double	angle;

	s = player->mouse_scaling_factor;
	if (player->keys[K_RIGHT] ^ player->keys[K_LEFT])
	{
		if (player->keys[K_RIGHT])
			mouse->pos.x += DEFAULT_ROT_SPEED * delta_time;
		else
			mouse->pos.x -= DEFAULT_ROT_SPEED * delta_time;
	}
	delta.x = mouse->pos.x - mouse->center.x;
	delta.y = mouse->pos.y - mouse->center.y;
	angle = delta.x * s;
	dir.x = player->dir.x * cos(angle) - player->dir.y * sin(angle);
	dir.y = player->dir.x * sin(angle) + player->dir.y * cos(angle);
	normalize_vector(&dir);
	angle = atan2(dir.y, dir.x) + M_PI_2;
	player->plane.x = cos(angle) * player->focal_length;
	player->plane.y = sin(angle) * player->focal_length;
	player->dir = dir;
}

static void	do_other_input_stuff(t_config *config)
{
	if (config->player.keys[K_COMMA] && config->player.fov >= 0.2f)
	{
		config->player.fov -= 0.1;
		set_player_plane(&config->player);
	}
	if (config->player.keys[K_DOT] && config->player.fov <= 177.9f)
	{
		config->player.fov += 0.1;
		set_player_plane(&config->player);
	}
}

double	do_engine_tick(t_config *config, double current_time)
{
	double			delta_time;
	static double	previous_time = 0.0f;

	if (config->player.keys[DEBUG_SHOW_GRAPH])
		log_tick_time(config, current_time - previous_time);
	if (previous_time == 0.0f)
	{
		delta_time = 0.0f;
		previous_time = current_time;
	}
	else
	{
		delta_time = (current_time - previous_time)
			/ config->engine.tick_duration;
		previous_time = current_time;
	}
	decelerate_player(&config->player, delta_time);
	process_mouse_move(&config->mouse, &config->player, delta_time);
	move_player(config, delta_time);
	do_other_input_stuff(config);
	mlx_mouse_move(config->mlx.xvar, config->mlx.window, config->mouse.center.x,
		config->mouse.center.y);
	++config->engine.tick_count;
	return (current_time);
}
