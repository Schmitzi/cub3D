/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:24:04 by schmitzi          #+#    #+#             */
/*   Updated: 2024/09/24 23:57:10 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	set_color(t_minimap *mini, t_config *config, t_image *buffer,
		size_t index)
{
	t_player	*player;
	uint32_t	color;

	player = &config->player;
	mini->map.x = (player->pos.x - (double)(mini->width >> 1) / TILE_SIZE)
		+ (mini->pos.x / TILE_SIZE);
	mini->map.y = (player->pos.y - (double)(mini->height >> 1) / TILE_SIZE)
		+ (mini->pos.y / TILE_SIZE);
	if (mini->map.x >= 0 && mini->map.x < (int)config->map.width
		&& mini->map.y >= 0 && mini->map.y < (int)config->map.height)
	{
		mini->tile = config->map.raster[(int)mini->map.y][(int)mini->map.x];
		if ((int)player->pos.x == (int)mini->map.x
			&& (int)player->pos.y == (int)mini->map.y)
			color = 0xFF0000;
		else if (mini->tile == '0')
			color = config->map.floor;
		else if (mini->tile == '1')
			color = 0xFFFFFF;
		else if (mini->tile == 'D')
			color = 0x0000FF;
		else
			return ;
		fast_write_pxl(buffer->data, index >> 2, color);
	}
}

void	draw_minimap(t_config *config)
{
	t_minimap	mini;
	size_t		ylen;
	int			padded_height;
	int			padded_width;
	int			bpp_div8;

	mini.pos.y = MINIMAP_PADDING;
	mini.height = DEFAULT_MINIMAP_HEIGHT;
	mini.width = DEFAULT_MINIMAP_WIDTH;
	padded_height = mini.height + MINIMAP_PADDING;
	padded_width = mini.width + MINIMAP_PADDING;
	bpp_div8 = config->frame.bpp >> 3;
	while (mini.pos.y < padded_height)
	{
		mini.pos.x = MINIMAP_PADDING;
		ylen = mini.pos.y * config->frame.line_len;
		while (mini.pos.x < padded_width)
		{
			set_color(&mini, config, &config->frame, (int)(mini.pos.x * bpp_div8
					+ ylen));
			mini.pos.x++;
		}
		mini.pos.y++;
	}
}
