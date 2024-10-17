/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 22:49:25 by xgossing          #+#    #+#             */
/*   Updated: 2024/10/02 18:40:04 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	fast_draw_background(t_config *config, size_t *cache, char *img_data)
{
	uint64_t	color;
	size_t		len;
	size_t		i;

	len = config->cache_size >> 1;
	i = 0;
	color = config->map.ceiling;
	while (i < len)
	{
		fast_write_2pxl(img_data, cache[i], color);
		fast_write_2pxl(img_data, cache[i + 1], color);
		fast_write_2pxl(img_data, cache[i + 2], color);
		fast_write_2pxl(img_data, cache[i + 3], color);
		i += 4;
	}
	len = config->cache_size;
	color = config->map.floor;
	while (i < len)
	{
		fast_write_2pxl(img_data, cache[i], color);
		fast_write_2pxl(img_data, cache[i + 1], color);
		fast_write_2pxl(img_data, cache[i + 2], color);
		fast_write_2pxl(img_data, cache[i + 3], color);
		i += 4;
	}
}

void	init_renderer(t_renderer *render)
{
	render->render_fps = DEFAULT_RENDER_FPS;
	render->last_frame = get_precise_time();
	render->frame_time = 1.0f / render->render_fps;
}

static void	put_coordinates_to_window(t_config *config, t_mlx *mlx, int h)
{
	char	*str;

	mlx_string_put(mlx->xvar, mlx->window, 10, h + 50, 0x0000FF66,
		"Player coordinates:");
	str = ft_itoa((int)config->player.pos.x);
	if (!str)
		return ;
	mlx_string_put(mlx->xvar, mlx->window, 10, h + 70, 0x0000FF66, str);
	free(str);
	str = ft_itoa((int)config->player.pos.y);
	if (!str)
		return ;
	mlx_string_put(mlx->xvar, mlx->window, 10, h + 90, 0x0000FF66, str);
	free(str);
}

void	put_debug_info_to_window(t_config *config, t_mlx *mlx)
{
	char	*str;
	int		num;
	int		h;

	h = config->win.half_height - 10;
	num = round(config->debug.tick_times[config->debug.tt_index] * 10000000.0f);
	str = ft_itoa(num);
	if (!str)
		return ;
	mlx_string_put(mlx->xvar, mlx->window, 10, h + 10, 0x0000FF66, str);
	free(str);
	num = round(config->debug.frame_times[config->debug.ft_index]
			* 10000000.0f);
	str = ft_itoa(num);
	if (!str)
		return ;
	mlx_string_put(mlx->xvar, mlx->window, 10, h + 30, 0x0000FF66, str);
	free(str);
	put_coordinates_to_window(config, mlx, h);
}

double	render_frame(t_config *config, double current_time)
{
	static double	previous_time = 0;

	if (config->player.keys[DEBUG_SHOW_GRAPH])
		log_frame_time(config, current_time - previous_time);
	previous_time = current_time;
	render_scene(config, &config->player);
	draw_minimap(config);
	if (config->player.keys[DEBUG_SHOW_GRAPH])
		draw_graph();
	config->render.frame_count++;
	return (current_time);
}
