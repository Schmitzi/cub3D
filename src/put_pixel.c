/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:17:02 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/25 00:38:17 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// int	*pixels;
// pixels = (int *)mlx->img_data;
// pixels[x * player->win.height + y] = color;
// make sure this doesn't write outside of the window viewport
void	slow_write_pxl(t_config *config, int x, int y, int color)
{
	wrap_overflow(&x, config->win.width);
	wrap_overflow(&y, config->win.height);
	config->frame.data[(x * 4 + 3) + (y
			* config->frame.line_len)] = color >> 24;
	config->frame.data[(x * 4 + 2) + (y
			* config->frame.line_len)] = color >> 16;
	config->frame.data[(x * 4 + 1) + (y * config->frame.line_len)] = color >> 8;
	config->frame.data[(x * 4 + 0) + (y * config->frame.line_len)] = color;
}

inline void	fast_write_pxl(char *data, size_t base_index, uint32_t color)
{
	((uint32_t *)data)[base_index] = color;
}

inline void	fast_write_2pxl(char *data, size_t base_index, uint64_t color)
{
	((uint64_t *)data)[base_index] = color;
}
