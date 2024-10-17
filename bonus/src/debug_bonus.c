/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 20:25:06 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/24 23:57:10 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

// 2 second buffer
t_error	init_debug(t_debug *debug)
{
	static const int	tick_buffer_seconds = 2;

	ft_bzero(debug, sizeof(t_debug));
	debug->size = DEFAULT_ENGINE_FPS * tick_buffer_seconds;
	if (debug->size > WINDOW_W - GRAPH_PADDING * 2)
		debug->size = WINDOW_W - GRAPH_PADDING * 2;
	debug->frame_times = ft_calloc(sizeof(double), debug->size);
	debug->tick_times = ft_calloc(sizeof(double), debug->size);
	if (!debug->frame_times || !debug->tick_times)
		return (E_DEBUG_INIT_FAIL);
	return (NO_ERROR);
}

void	destroy_debug_info(void)
{
	t_debug	*debug;

	debug = &(*get_config(NULL))->debug;
	if (debug->frame_times)
		free(debug->frame_times);
	if (debug->tick_times)
		free(debug->tick_times);
	ft_bzero(debug, sizeof(t_debug));
}
