/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:11:00 by xgossing          #+#    #+#             */
/*   Updated: 2024/10/02 20:19:12 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static bool	is_point_in_circle(float xa, float ya, float xc, float yc)
{
	static const double	buffer_distance_squared = WALL_BUFFER_DISTANCE
		* WALL_BUFFER_DISTANCE;

	return (((xa - xc) * (xa - xc) + (ya - yc) * (ya
				- yc)) < buffer_distance_squared);
}

static void	collide_orthogonal(t_point_int tile, t_point *new, double buffer)
{
	t_map	*map;
	double	dist_left;
	double	dist_right;
	double	dist_top;
	double	dist_bottom;

	map = *get_map(NULL);
	dist_left = new->x - tile.x;
	dist_right = (tile.x + 1) - new->x;
	dist_top = new->y - tile.y;
	dist_bottom = (tile.y + 1) - new->y;
	if (dist_left < buffer && map->raster[tile.y][tile.x - 1] != '0')
		new->x = tile.x + buffer;
	if (dist_right < buffer && map->raster[tile.y][tile.x + 1] != '0')
		new->x = tile.x + 1 - buffer;
	if (dist_top < buffer && map->raster[tile.y - 1][tile.x] != '0')
		new->y = tile.y + buffer;
	if (dist_bottom < buffer && map->raster[tile.y + 1][tile.x] != '0')
		new->y = tile.y + 1 - buffer;
}

// assumes that the radius is small enough to only ever hit one corner at a time
void	collide_diagonal(t_point_int tile, t_point *new, double buffer)
{
	t_point	normal;
	t_map	*map;

	map = *get_map(NULL);
	if (is_point_in_circle(new->x, new->y, tile.x, tile.y) && map->raster[tile.y
			- 1][tile.x - 1] != '0')
		normal = (t_point){new->x - tile.x, new->y - tile.y};
	else if (is_point_in_circle(new->x, new->y, tile.x + 1, tile.y)
		&& map->raster[tile.y - 1][tile.x + 1] != '0')
		normal = (t_point){new->x - ++tile.x, new->y - tile.y};
	else if (is_point_in_circle(new->x, new->y, tile.x, tile.y + 1)
		&& map->raster[tile.y + 1][tile.x - 1] != '0')
		normal = (t_point){new->x - tile.x, new->y - ++tile.y};
	else if (is_point_in_circle(new->x, new->y, tile.x + 1, tile.y + 1)
		&& map->raster[tile.y + 1][tile.x + 1] != '0')
		normal = (t_point){new->x - ++tile.x, new->y - ++tile.y};
	else
		return ;
	normalize_vector(&normal);
	new->x = tile.x + normal.x * buffer;
	new->y = tile.y + normal.y * buffer;
}

void	handle_player_collision(t_player *p, double distance, double delta_time)
{
	t_point_int	tile;
	t_point		new;
	t_point		step;
	size_t		steps;
	size_t		i;

	steps = (size_t)(distance / MAX_STEP_SIZE);
	step.x = (p->velocity.x * delta_time * DEFAULT_PLAYER_STEP_SIZE) / steps;
	step.y = (p->velocity.y * delta_time * DEFAULT_PLAYER_STEP_SIZE) / steps;
	i = 0;
	while (i < steps)
	{
		new = (t_point){p->pos.x + step.x, p->pos.y + step.y};
		tile = (t_point_int){(int)new.x, (int)new.y};
		collide_orthogonal(tile, &new, WALL_BUFFER_DISTANCE);
		collide_diagonal(tile, &new, WALL_BUFFER_DISTANCE);
		p->pos.x = new.x;
		p->pos.y = new.y;
		i++;
	}
}
