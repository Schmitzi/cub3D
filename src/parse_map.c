/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:13:48 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/25 01:09:48 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * Case 1:
 *     111  11
 *   11101111111
 *   10000000001111
 * 1110000000000001
 * 1000011111110001
 * 110111     11111
 *  111
 *   1
 */

static t_error	parse_map(t_map *map, char **raw)
{
	size_t	i;

	i = 0;
	map->raster = ft_calloc((map->height + 1), sizeof(char *));
	if (!map->raster)
	{
		return (E_MAP_ALLOC_FAIL);
	}
	while (i < map->height)
	{
		map->raster[i] = ft_strndup_with_padding((raw[i]) + map->left_bound,
				ft_strlen(raw[i]), map->width, ' ');
		if (!map->raster[i])
		{
			while (i > 0)
				free(map->raster[--i]);
			return (E_MAP_ALLOC_FAIL);
		}
		i++;
	}
	map->raster[i] = NULL;
	return (NO_ERROR);
}

static t_point	get_player_dir(char c)
{
	if (c == 'N')
		return ((t_point){0, -1});
	if (c == 'S')
		return ((t_point){0, 1});
	if (c == 'E')
		return ((t_point){1, 0});
	if (c == 'W')
		return ((t_point){-1, 0});
	return ((t_point){0, 0});
}

static void	set_player_pos(t_config *config)
{
	t_point	pos;
	size_t	x;
	size_t	y;

	y = 0;
	while (config->map.raster[y])
	{
		x = 0;
		while (config->map.raster[y][x])
		{
			if (gnl_strchr("NSEW", config->map.raster[y][x]) != NULL)
			{
				pos.x = x + 0.5;
				pos.y = y + 0.5;
				config->player.pos = pos;
				config->player.dir = get_player_dir(config->map.raster[y][x]);
				config->map.raster[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

t_error	parse_map_file(t_config *config, t_raw_map *raw_map, t_map *map)
{
	int		i;
	t_error	err;

	err = validate_map_structure(config, raw_map);
	i = 0;
	while (!err && raw_map->raw[i] && !is_map_line(raw_map->raw[i]))
		err = parse_config_param(raw_map, raw_map->raw[i++]);
	if (!err)
	{
		get_colours(config);
		get_map_dimensions(raw_map->raw + i, map);
		err = parse_map(map, raw_map->raw + i);
	}
	if (!err)
	{
		err = is_valid_map(map);
		set_player_pos(config);
	}
	return (err);
}
