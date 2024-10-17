/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 04:38:29 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/25 00:38:17 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	is_whitespace_line(char *line)
{
	if (!line)
		return (true);
	while (*line)
	{
		if (!is_whitespace(*line))
			return (false);
		line++;
	}
	return (true);
}

bool	is_map_line(char *line)
{
	unsigned int	player_count;

	player_count = 0;
	if (is_whitespace_line(line))
		return (false);
	while (*line)
	{
		if (!is_one_of(*line, VALID_MAP_CHARS))
			return (false);
		if (is_one_of(*line, "NESW"))
			player_count++;
		line++;
	}
	return (player_count <= 1);
}

bool	is_config_param_line(char *line)
{
	return (!is_whitespace_line(line) && !is_map_line(line));
}
