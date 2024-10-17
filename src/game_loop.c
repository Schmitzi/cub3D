/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:26:42 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/25 01:43:40 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	show_tick(t_config *config, size_t i)
{
	if (i == 0)
	{
		mlx_put_image_to_window(config->mlx.xvar, config->mlx.window,
			config->frame.mlx_img, 0, 0);
		if (config->player.keys[DEBUG_SHOW_GRAPH])
			put_debug_info_to_window(config, &config->mlx);
	}
}

static size_t	tick_tick(t_config *config, double current_time, size_t i)
{
	static double	next_tick_time = 0;

	if (next_tick_time == 0)
		next_tick_time = get_precise_time();
	if (current_time >= next_tick_time)
	{
		config->engine.last_tick = do_engine_tick(config, current_time);
		next_tick_time += config->engine.tick_duration;
		show_tick(config, i);
		if (++i == 2)
			fast_draw_background(config, config->base_index_cache,
				config->frame.data);
	}
	return (i);
}

static size_t	render_tick(t_config *config, double current_time, size_t i)
{
	static double		next_frame_time = 0;
	static const size_t	ticks_per_frame = DEFAULT_ENGINE_FPS
		/ DEFAULT_RENDER_FPS;

	if (next_frame_time == 0)
		next_frame_time = get_precise_time();
	if (i >= ticks_per_frame && current_time >= next_frame_time)
	{
		config->render.last_frame = render_frame(config, current_time);
		next_frame_time += config->render.frame_time;
		return (0);
	}
	return (i);
}

// what if I return early when not enough ticks have happened
// before a frame starts rendering?
int	loop_hook(t_config *config)
{
	static size_t	i = 0;
	double			current_time;

	current_time = get_precise_time();
	i = tick_tick(config, current_time, i);
	i = render_tick(config, current_time, i);
	return (0);
}
