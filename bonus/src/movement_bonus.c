/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:21:39 by xgossing          #+#    #+#             */
/*   Updated: 2024/10/02 20:17:21 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	normalize_vector(t_point *v)
{
	double	magnitude;

	magnitude = sqrt(v->x * v->x + v->y * v->y);
	if (magnitude > 0)
	{
		v->x /= magnitude;
		v->y /= magnitude;
	}
}

void	decelerate_player(t_player *player, double delta_time)
{
	double	deceleration;

	deceleration = 1 - (player->deceleration * delta_time);
	player->velocity = (t_point){player->velocity.x * deceleration,
		player->velocity.y * deceleration};
}

void	wrap_player_position(t_player *p, t_config *config)
{
	if (p->pos.x < 0)
		p->pos.x = config->map.width + p->pos.x;
	if (p->pos.x > config->map.width)
		p->pos.x = p->pos.x - config->map.width;
	if (p->pos.y < 0)
		p->pos.y = config->map.height + p->pos.y;
	if (p->pos.y > config->map.height)
		p->pos.y = p->pos.y - config->map.height;
}

static void	calculate_combined_velocity(t_player *p, double acceleration)
{
	double	multiplier;

	multiplier = 1.0f;
	if (p->keys[K_S])
		multiplier = -1.0f;
	if (p->keys[K_SHIFT])
		multiplier *= 2.0f;
	if (p->keys[K_W] ^ p->keys[K_S])
	{
		if (p->keys[K_D] ^ p->keys[K_A])
			multiplier *= DIAGONAL_MOVE_SPEED;
		p->velocity.x += p->dir.x * multiplier * acceleration;
		p->velocity.y += p->dir.y * multiplier * acceleration;
	}
	multiplier = 1.0f;
	if (p->keys[K_A])
		multiplier = -1.0f;
	if (p->keys[K_D] ^ p->keys[K_A])
	{
		if (p->keys[K_W] ^ p->keys[K_S])
			multiplier *= DIAGONAL_MOVE_SPEED;
		p->velocity.x += (-p->dir.y) * multiplier * acceleration;
		p->velocity.y += p->dir.x * multiplier * acceleration;
	}
}

// first decelerate p using drag coefficient
// deceleration should happen pretty soon after key release
// if the player is at max speed, it should take a bit longer
// but never longer than 1.5 seconds

int	move_player(t_config *config, double delta_time)
{
	t_player	*p;
	double		distance;

	p = &config->player;
	calculate_combined_velocity(p, p->acceleration * delta_time);
	distance = sqrt(p->velocity.x * p->velocity.x + p->velocity.y
			* p->velocity.y);
	handle_player_collision(p, distance, delta_time);
	return (0);
}
