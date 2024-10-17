/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:26:42 by xgossing          #+#    #+#             */
/*   Updated: 2024/10/11 16:16:50 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	draw_greenscreen_image(t_image *img, t_image *buffer,
		size_t **buffer_vcache)
{
	int						x;
	int						y;
	t_image_buffer_caches	c;
	uint32_t				color;

	if (!img)
		return ;
	c.frame_data = buffer->data;
	c.image_data = (uint32_t *)img->data;
	c.ivc = img->vcache;
	x = 0;
	while (x < img->width && x < buffer->width)
	{
		y = 0;
		c.image_vcache = c.ivc[x];
		c.frame_vcache = buffer_vcache[x];
		while (y < img->height && y < buffer->height)
		{
			color = c.image_data[c.image_vcache[y]];
			if (color != 0x00FF00)
				fast_write_pxl(c.frame_data, c.frame_vcache[y], color);
			y++;
		}
		x++;
	}
}

static void	show_tick(t_config *config, size_t i)
{
	double	now;
	t_image	*img;

	if (i == 0)
	{
		now = get_precise_time();
		if (config->map.sprite_count)
		{
			img = get_animation_img(config->map.sprites,
					config->map.sprite_count - 1, now,
					config->player.keys[K_B]);
			draw_greenscreen_image(img, &config->frame,
				config->vertical_index_cache);
		}
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
