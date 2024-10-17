/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:21:22 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/25 00:38:17 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_intersection_data(int window_height, t_ray *ray)
{
	static const int32_t	half_win_height = WINDOW_H / 2;
	int32_t					half_line_height;

	if (ray->side == 0)
		ray->wall_dist = (ray->grid_pos.x - ray->pos.x + ((1
						- ray->step_dir.x) >> 1)) / ray->dir.x;
	else
		ray->wall_dist = (ray->grid_pos.y - ray->pos.y + ((1
						- ray->step_dir.y) >> 1)) / ray->dir.y;
	ray->wall_dist += WALL_DISTANCE_EPSILON;
	ray->line_height = (int)(window_height / ray->wall_dist);
	half_line_height = ray->line_height >> 1;
	ray->draw_start = -half_line_height + half_win_height;
	ray->draw_end = half_line_height + half_win_height;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= window_height)
		ray->draw_end = window_height - 1;
}
