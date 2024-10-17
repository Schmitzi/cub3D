/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_structure_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:28:33 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/24 23:57:10 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	count_identifier(t_direction dir, t_type_identifiers *identifiers)
{
	if (dir == NO)
		identifiers->no++;
	if (dir == EA)
		identifiers->ea++;
	if (dir == SO)
		identifiers->so++;
	if (dir == WE)
		identifiers->we++;
	if (dir == DO)
		identifiers->d++;
	if (dir == S)
		identifiers->s++;
	if (dir == C)
		identifiers->c++;
	if (dir == F)
		identifiers->f++;
}

static t_error	assert_config_integrity(t_raw_map *raw_map, int *i)
{
	t_type_identifiers	identifiers;
	t_direction			dir;

	ft_bzero(&identifiers, sizeof(t_type_identifiers));
	while (raw_map->raw[*i] && (is_config_param_line(raw_map->raw[*i])
			|| is_whitespace_line(raw_map->raw[*i])))
	{
		dir = get_param_type(skip_ws(raw_map->raw[*i]));
		if (dir == INVALID_DIRECTION && !is_whitespace_line(raw_map->raw[*i]))
			return (E_INVALID_PARAM);
		count_identifier(dir, &identifiers);
		(*i)++;
	}
	if (identifiers.no != 1 || identifiers.ea != 1 || identifiers.so != 1
		|| identifiers.we != 1 || identifiers.c != 1 || identifiers.f != 1)
		return (E_INVALID_MAP_CONFIG);
	raw_map->sprite_count = identifiers.s;
	return (NO_ERROR);
}

t_error	validate_map_structure(t_config *config, t_raw_map *raw_map)
{
	int		i;
	t_error	err;

	i = 0;
	err = assert_config_integrity(raw_map, &i);
	if (!err)
		err = assert_map_portion_exists(raw_map->raw + i);
	if (err != NO_ERROR)
		return (err);
	config->map.sprite_count = raw_map->sprite_count;
	count_player_spawns(raw_map->raw + i);
	if (config->raw_map.player_count > 1)
		return (E_TOO_MANY_PLAYER_SPAWN);
	if (config->raw_map.player_count < 1)
		return (E_NO_PLAYER_SPAWN);
	while (raw_map->raw[i] && is_map_line(raw_map->raw[i]))
		i++;
	while (raw_map->raw[i] && is_whitespace_line(raw_map->raw[i]))
		i++;
	if (raw_map->raw[i])
		return (E_SOMETHING_AFTER_MAP);
	return (NO_ERROR);
}
