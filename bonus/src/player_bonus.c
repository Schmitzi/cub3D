/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 03:49:24 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/24 23:57:10 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

t_player	**get_player(t_player *the_goods)
{
	static t_player	*player = NULL;

	if (the_goods)
		player = the_goods;
	return (&player);
}

void	init_player(t_player *player)
{
	ft_bzero(player, sizeof(t_player));
	player->dir.x = -1.0f;
	player->dir.y = 0.0f;
	player->mov_speed = DEFAULT_MOVE_SPEED;
	player->rot_speed = DEFAULT_ROT_SPEED;
	player->mouse_scaling_factor = DEFAULT_MOUSE_SCALING_FACTOR;
	player->acceleration = DEFAULT_ACCELERATION;
	player->deceleration = DEFAULT_DECELERATION;
	player->fov = DEFAULT_FOV;
	player->pos.x = 0.0f;
	player->pos.y = 0.0f;
	player->plane.x = 0.0f;
	player->plane.y = 0.66f;
}

// set the player's plane depending on which way he's facing in the map, and
// on the FOV value (player.fov, or DEFAULT_FOV)
void	set_player_plane(t_player *player)
{
	double	angle;

	player->focal_length = tan(deg_to_rad(player->fov / 2));
	angle = atan2(player->dir.y, player->dir.x) + M_PI_2;
	player->plane.x = cos(angle) * player->focal_length;
	player->plane.y = sin(angle) * player->focal_length;
}
