/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:00:33 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/25 00:38:17 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// asserts that a map of sufficient size exists at raw's current position
t_error	assert_map_portion_exists(char **raw)
{
	size_t	i;

	if (!raw)
		return (E_NO_MAP);
	i = 0;
	while (*raw && is_map_line(*raw))
	{
		i++;
		raw++;
	}
	if (i == 0)
		return (E_NO_MAP);
	if (i < 3)
		return (E_MAP_TOO_SMALL);
	return (NO_ERROR);
}

static bool	floor_is_surrounded(char **raster, size_t row, size_t column)
{
	if (raster[row][column - 1] == ' ')
		return (false);
	if (raster[row - 1][column] == ' ')
		return (false);
	if (raster[row][column] == ' ')
		return (false);
	if (raster[row + 1][column] == ' ')
		return (false);
	if (raster[row][column + 1] == ' ')
		return (false);
	return (true);
}

static t_error	check_surrounding_tiles(t_map *map, size_t row, size_t column)
{
	if (map->raster[row][column] != '1' && map->raster[row][column] != ' ')
	{
		if (row == 0 || column == 0 || row == map->height - 1
			|| column == map->width - 1)
		{
			return (E_FLOOR_TOUCHES_EDGE);
		}
		else if (!floor_is_surrounded(map->raster, row, column))
		{
			return (E_FLOOR_TOUCHES_VOID);
		}
	}
	return (NO_ERROR);
}

// ensure only 1s are adjacent to any space
// ensure only 1s are adjacent to the matrix's outer boundaries
// inverse flood fill?
// loop over every single character
// if the character is not 1, ensure it is
// not in map->raster[0], or line[0]
// also ensure it is not in map->raster[npos] or line[npos]
// then check the surrounding 8 cells for any spaces
// if the non-1 character is not in the outer perimeter
// and otherwise isn't adjacent to a space character,
// the map is valid & shouldn't have any floors touching the void
t_error	is_valid_map(t_map *map)
{
	size_t	row;
	size_t	column;
	t_error	err;

	row = 0;
	while (map->raster[row])
	{
		column = 0;
		while (map->raster[row][column])
		{
			err = check_surrounding_tiles(map, row, column);
			if (err != NO_ERROR)
				return (err);
			column++;
		}
		row++;
	}
	return (NO_ERROR);
}

void	get_colours(t_config *config)
{
	uint32_t	ceiling;
	uint32_t	floor;
	uint64_t	two_pixels_ceiling;
	uint64_t	two_pixels_floor;

	ceiling = get_rgb(config->raw_map.ceiling[0], config->raw_map.ceiling[1],
			config->raw_map.ceiling[2]);
	floor = get_rgb(config->raw_map.floor[0], config->raw_map.floor[1],
			config->raw_map.floor[2]);
	two_pixels_ceiling = ((uint64_t)ceiling << 32) | ceiling;
	two_pixels_floor = ((uint64_t)floor << 32) | floor;
	config->map.ceiling = two_pixels_ceiling;
	config->map.floor = two_pixels_floor;
}
