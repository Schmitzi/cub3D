/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:05:21 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/24 23:57:10 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

char	*skip_ws(char *str)
{
	if (!str)
		return (NULL);
	while (*str && is_whitespace(*str))
		str++;
	return (str);
}

// I hate writing side effects but they're just so convenient
// Snips off trailing whitespace
void	trim_whitespace(char *str)
{
	char	*end;

	if (!str || !*str)
		return ;
	end = str + ft_strlen(str) - 1;
	while (end > str && is_whitespace(*end))
	{
		*end = '\0';
		end--;
	}
}

t_direction	get_param_type(char *line)
{
	if (ft_strncmp("F ", line, 2) == 0)
		return (F);
	if (ft_strncmp("C ", line, 2) == 0)
		return (C);
	if (ft_strncmp("S ", line, 2) == 0)
		return (S);
	if (ft_strncmp("DO ", line, 3) == 0)
		return (DO);
	if (ft_strncmp("NO ", line, 3) == 0)
		return (NO);
	if (ft_strncmp("EA ", line, 3) == 0)
		return (EA);
	if (ft_strncmp("SO ", line, 3) == 0)
		return (SO);
	if (ft_strncmp("WE ", line, 3) == 0)
		return (WE);
	return (INVALID_DIRECTION);
}

// returns the length of the digit portion at the start of str
// i.e. if there's a string "144,34abc" it'll return 3
size_t	strint_length(char *str)
{
	size_t	length;

	if (!str)
		return (0);
	length = 0;
	while (str[length] && is_digit(str[length]))
		length++;
	return (length);
}

// this function should never have to process an empty line.
// or rather, in the while loop, only non-empty lines
// containind only map data should ever be processed,
// as detected by is_map_line()
// figure out the leftmost wall, i.e. the map portion's left bound
// then figure out the right bound
// right - left = map width
void	get_map_dimensions(char **raw_map, t_map *map)
{
	size_t	i;
	size_t	right_bound;
	size_t	line_lb;
	size_t	line_rb;
	char	*current_line;

	i = 0;
	map->left_bound = ft_strlen(raw_map[i]);
	right_bound = 0;
	while (raw_map[i] && is_map_line(raw_map[i]))
	{
		line_lb = 0;
		current_line = raw_map[i++];
		while (is_whitespace(current_line[line_lb]))
			line_lb++;
		line_rb = ft_strlen(current_line) - 1;
		while (line_rb > line_lb && is_whitespace(current_line[line_rb]))
			line_rb--;
		if (line_lb < map->left_bound)
			map->left_bound = line_lb;
		if (line_rb > right_bound)
			right_bound = line_rb;
	}
	map->height = i;
	map->width = right_bound - map->left_bound + 1;
}
