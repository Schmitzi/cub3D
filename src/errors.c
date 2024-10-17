/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:09:58 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/25 01:04:42 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static const t_error_message	g_error_messages[] = {
{NO_ERROR, "No issues encountered"},
{E_INCORRECT_ARGC, "Invalid number of arguments, expected 1.\n"},
{E_MLX_INIT_FAIL, "Failed to initialize minilibx"},
{E_MLX_WINDOW_INIT_FAIL, "Failed to initialize window"},
{E_MLX_IMAGE_INIT_FAIL, "Failed to initialize image"},
{E_FRAMEBUF_INIT_FAIL, "Failed to initialize frame buffer"},
{E_CACHE_INIT_FAIL, "Failed to initialize frame buffer base index cache"},
{E_IMAGE_CACHE_INIT_FAIL, "Failed to initialize image base index cache"},
{E_DEBUG_INIT_FAIL, "Failed to initialize debug buffers"},
{E_INVALID_MAP_EXT, "Invalid file extension (expected: \".cub\")"},
{E_MAP_OPEN_FAIL, "Failed to open map file"},
{E_MAP_READ_FAIL, "Failed to read map file"},
{E_MAP_ALLOC_FAIL, "Failed to allocate memory for map raster"},
{E_MAP_CONV_FAIL, "Failed to convert map to raster"},
{E_INVALID_MAP_STRUCTURE, "Map file has invalid structure"},
{E_INVALID_PARAM, "Invalid map parameter encountered"},
{E_INVALID_MAP_CONFIG, "Incorrect number of config params encountered"},
{E_INVALID_TEX_PARAM, "Texture parameter is invalid"},
{E_NO_PATH_IN_TEXTURE_PARAM, "Texture path missing in map file"},
{E_INVALID_TEXTURE_EXT, "Texture file has invalid file extension"},
{E_INVALID_COLOR_PARAM, "Color parameter is invalid"},
{E_COLOR_OUT_OF_BOUNDS, "Color parameter is out of bounds (expected 0-255)"},
{E_NO_MAP, "No map portion found"},
{E_MAP_TOO_SMALL, "Map is too small"},
{E_SOMETHING_AFTER_MAP, "Data encountered after map portion"},
{E_NO_PLAYER_SPAWN, "No player spawn found"},
{E_TOO_MANY_PLAYER_SPAWN, "Encountered multiple player spawns"},
{E_FLOOR_TOUCHES_EDGE, "Floor tile in contact with map edge encountered"},
{E_FLOOR_TOUCHES_VOID, "Floor tile missing boundaries encountered"},
{E_IMAGE_OPEN_FAIL, "Image file failed to open"},
{E_IMAGE_FORMAT_FAIL, "Image file is corrupted"},
};

void	print_error(t_error error)
{
	size_t	big;

	big = sizeof(g_error_messages) / sizeof(t_error_message);
	if (error == NO_ERROR)
		printf("No error: Why am I printing this?\n");
	else if (error >= big)
		printf("Unknown error!\n");
	else
		printf("Error\n%s\n", g_error_messages[error].message);
}
