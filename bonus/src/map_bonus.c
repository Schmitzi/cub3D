/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:37:36 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/24 23:57:10 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

t_map	**get_map(t_map *the_goods)
{
	static t_map	*map = NULL;

	if (the_goods)
		map = the_goods;
	return (&map);
}

void	init_map(t_map *map)
{
	ft_bzero(map, sizeof(t_map));
	map->ceiling = (uint64_t)get_rgb(30, 0, 0) << 32 | (uint64_t)get_rgb(30, 0,
			0);
	map->floor = (uint64_t)get_rgb(0, 0, 30) << 32 | (uint64_t)get_rgb(0, 0,
			30);
	map->texture_count = 4;
}

void	destroy_map(void)
{
	t_map	*map;
	size_t	i;

	map = *get_map(NULL);
	free_matrix(map->raster);
	if (map->door_count && map->door)
		free(map->door);
	i = 0;
	while (i < map->texture_count)
	{
		if (map->tex[i].mlx_img || map->tex[i].vcache)
			destroy_image(map->tex + i);
		i++;
	}
	ft_bzero(map, sizeof(t_map));
}
