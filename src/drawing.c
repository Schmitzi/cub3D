/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:15:28 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/25 01:13:52 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	write_rect(t_config *config, t_point start, t_point end, int color)
{
	int	i;
	int	j;

	i = start.x;
	while (i < end.x)
	{
		j = start.y;
		while (j < end.y)
		{
			slow_write_pxl(config, i, j, color);
			j++;
		}
		i++;
	}
}

void	fast_write_rect(t_image *frame, t_point start, t_point end,
		uint64_t color)
{
	int	i;
	int	j;
	int	base_index;
	int	ylen;

	i = start.x;
	while (i < end.x)
	{
		j = start.y;
		while (j < end.y)
		{
			ylen = j * frame->line_len;
			base_index = (i * 4) + ylen;
			fast_write_2pxl(frame->data, base_index / 8, color);
			j++;
		}
		i += 2;
	}
}

// draw the player's field of view
// abstract into draw_triangle(point, angle) or smth?
void	draw_player_fov(t_player *player)
{
	t_vec3	corners;
	double	angle1;
	double	angle2;

	corners.a.x = player->pos.x;
	corners.a.y = player->pos.y;
	angle1 = atan2(player->dir.y, player->dir.x) - deg_to_rad(player->fov / 2);
	angle2 = atan2(player->dir.y, player->dir.x) + deg_to_rad(player->fov / 2);
	corners.b.x = player->pos.x + cos(angle1) * 80;
	corners.b.y = player->pos.y + sin(angle1) * 80;
	corners.c.x = player->pos.x + cos(angle2) * 80;
	corners.c.y = player->pos.y + sin(angle2) * 80;
	plot_line((t_vector){corners.a, corners.b}, get_rgb(255, 255, 255));
	plot_line((t_vector){corners.a, corners.c}, get_rgb(255, 255, 255));
	plot_line((t_vector){corners.b, corners.c}, get_rgb(255, 255, 255));
}
