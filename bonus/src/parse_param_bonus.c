/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_param_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:08:45 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/24 23:57:10 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

// validate that there's actually 1-3 numbers, then comma,
// then another 1-3 numbers,
// then another comma & then another three extra numbers
// followed only by whitespace or nothing
static t_error	parse_color_param(t_config *config, char *line,
		t_direction type)
{
	int			i;
	uint32_t	*color;

	line = line + 2;
	line = skip_ws(line);
	if (!is_valid_color_param(line, 0))
		return (E_INVALID_COLOR_PARAM);
	if (type == C)
		color = config->raw_map.ceiling;
	else
		color = config->raw_map.floor;
	i = 0;
	while (i < 3)
	{
		color[i] = ft_atoi(line);
		if (color[i] > 255)
			return (E_COLOR_OUT_OF_BOUNDS);
		line = skip_ws(line + strint_length(line));
		if (*line && *line == ',')
			line++;
		i++;
	}
	return (NO_ERROR);
}

static t_error	parse_texture_path(t_raw_map *map, char *line, t_direction type)
{
	size_t	length;

	line = line + 3;
	line = skip_ws(line);
	trim_whitespace(line);
	if (!*line)
		return (E_NO_PATH_IN_TEXTURE_PARAM);
	length = ft_strlen(line);
	if (length < 4 || ft_strncmp(line + length - 4, ".xpm", 4))
		return (E_INVALID_TEXTURE_EXT);
	map->texture_paths[type] = line;
	return (NO_ERROR);
}

// get a pointer, see if it points at a valid float
// i.e. a digit, followed by arbitrary number of digits,
// an optional dot, and optionally more digits.
// shouldn't be too long, just limit it to some sane number
// like 64, including the dot. "." is also a valid float, representing 0.0f
// static bool	good_float(char *line)
// {
// 	size_t	i;
// 	size_t	dot;

// 	if (!line || !*line)
// 		return (false);
// 	i = 0;
// 	dot = 0;
// 	printf("good float oogling %s\n", line);
// 	while (line[i] && line[i] != ' ' && i < 64)
// 	{
// 		if (line[i] == '.')
// 			dot++;
// 		else if (!is_digit(line[i]))
// 			return (false);
// 		i++;
// 	}
// 	if (line[i] != ' ' && !is_digit(line[i]))
// 		return (false);
// 	return (dot <= 1);
// }

// first, skip over any whitespace
// then figure out which identifier it is,
// before storing whatever comes after it in
t_error	parse_config_param(t_raw_map *raw_map, char *line)
{
	char		*tmp;
	t_direction	type;
	t_config	*config;

	if (is_whitespace_line(line))
		return (NO_ERROR);
	config = *get_config(NULL);
	tmp = skip_ws(line);
	type = get_param_type(tmp);
	if (type == F || type == C)
		return (parse_color_param(config, tmp, type));
	if (type == S)
		return (parse_sprite(&config->map, tmp));
	return (parse_texture_path(raw_map, tmp, type));
}

void	count_player_spawns(char **raw)
{
	t_config	*config;
	char		*line;
	int			i;
	int			li;

	config = *get_config(NULL);
	li = 0;
	while (raw[li] && is_map_line(raw[li]))
	{
		line = raw[li];
		i = 0;
		while (line[i])
		{
			if (is_one_of(line[i], "NESW"))
				config->raw_map.player_count++;
			i++;
		}
		li++;
	}
}

bool	is_valid_color_param(char *line, int i)
{
	while (line[i] && is_digit(line[i]))
		i++;
	if (i > 3 || i == 0 || !line[i])
		return (false);
	line = skip_ws(line + i);
	if (*line != ',')
		return (false);
	line = skip_ws(++line);
	i = 0;
	while (line[i] && is_digit(line[i]))
		i++;
	if (i > 3 || i == 0 || !line[i])
		return (false);
	line = skip_ws(line + i);
	if (*line != ',')
		return (false);
	line = skip_ws(++line);
	i = 0;
	while (line[i] && is_digit(line[i]))
		i++;
	if (i > 3 || i == 0)
		return (false);
	line = line + i;
	return (is_whitespace_line(line));
}
