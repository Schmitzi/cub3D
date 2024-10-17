/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+: :+:
 */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:49:00 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/09/23 18:24:44 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static t_door	*get_door(t_point pos, t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->door_count)
	{
		if (map->door[i].pos.x == pos.x && map->door[i].pos.y == pos.y)
			return (map->door + i);
		i++;
	}
	return (NULL);
}

// I want the furthest-away door that is not obscured by something
// i.e. as long as door[i] == 0,
// start at the closest block, if it is 0 (floor or open door) move up
// f without holding shift prioritises opening doors
// f with holding shift prioritises closing the furthest-away, non-obstructed,
// open door
// if the furthest-away door is closed, and shift is not held,
// open the furthest-away door

// if shift is not held, then get nearest closed door, open it.
// if no closed door is found,
// close the furthest-away open door if one is found, otherwise do nothing

// if shift is held, then get furthest away, non-obstructed open door, close it.
// if no open door is found, open the nearest closed door. otherwise do nothing.

// t_door	*get_matching_door(t_tile *looking_at, t_map *map, bool shift)
// {
// 	size_t	i;
// 	t_door	*door;
// 	t_door	*furthest_closed_door;
// 	t_door	*furthest_open_door;

// 	i = 0;
// 	furthest_closed_door = NULL;
// 	furthest_open_door = NULL;
// 	if (shift)
// 	{
// 		while (i < PLAYER_INTERACTION_DISTANCE && looking_at[i].visible)
// 		{
// 			door = get_door(looking_at[i].pos, map);
// 			if (door)
// 			{
// 				if (door->is_open == false)
// 					furthest_closed_door = door;
// 				else
// 					furthest_open_door = door;
// 			}
// 			i++;
// 		}
// 		if (!furthest_closed_door)
// 		{
// 			if (furthest_open_door)
// 				return (furthest_open_door);
// 			else
// 				return (NULL);
// 		}
// 	}
// 	while (i < PLAYER_INTERACTION_DISTANCE && looking_at[i].visible)
// 	{
// 		door = get_door(looking_at[i].pos, map);
// 		if (door)
// 		{
// 			if (door->is_open == false)
// 				return (door);
// 			furthest_open_door = door;
// 		}
// 		i++;
// 	}
// 	if (furthest_open_door)
// 		return (furthest_open_door);
// 	return (NULL);
// }

void	toggle_door(t_player *player, t_map *map, size_t i)
{
	t_door	*door;

	while (i < PLAYER_INTERACTION_DISTANCE)
	{
		door = get_door(player->looking_at[i].pos, map);
		if (door && !door->is_open)
		{
			map->raster[(int)door->pos.y][(int)door->pos.x] = '0';
			door->is_open = !door->is_open;
			return ;
		}
		else if (door && door->is_open && i != 0)
		{
			map->raster[(int)door->pos.y][(int)door->pos.x] = 'D';
			door->is_open = !door->is_open;
			return ;
		}
		i++;
	}
}

bool	get_door_status(t_door *door, t_ray *ray, t_map *map)
{
	int	i;

	i = 0;
	while (door[i].is_open)
	{
		if (ray->grid_pos.x == map->door[i].pos.x
			&& ray->grid_pos.y == map->door[i].pos.y)
			return (map->door[i].is_open);
		i++;
	}
	return (false);
}

int	count_doors(t_map *map)
{
	int		count;
	t_point	pos;

	count = 0;
	pos.y = 0;
	while (pos.y < map->height)
	{
		pos.x = 0;
		while (pos.x < map->width)
		{
			if (map->raster[(int)pos.y][(int)pos.x] == 'D')
				count++;
			pos.x++;
		}
		pos.y++;
	}
	return (count);
}

t_error	set_doors(t_map *map)
{
	int		i;
	t_point	pos;

	map->door_count = count_doors(map);
	if (map->door_count == 0)
		return (NO_ERROR);
	map->texture_count++;
	pos.y = -1;
	map->door = (t_door *)ft_calloc(map->door_count, sizeof(t_door));
	if (map->door == NULL)
		return (E_MAP_ALLOC_FAIL);
	i = 0;
	while (++pos.y < map->height)
	{
		pos.x = -1;
		while (++pos.x < map->width)
		{
			if (map->raster[(int)pos.y][(int)pos.x] == 'D')
			{
				map->door[i].pos = pos;
				map->door[i++].is_open = false;
			}
		}
	}
	return (NO_ERROR);
}
