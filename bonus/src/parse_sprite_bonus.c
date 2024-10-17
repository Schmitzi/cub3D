/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprite_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:11:28 by xgossing          #+#    #+#             */
/*   Updated: 2024/10/02 21:26:24 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static char	**destroy_file_paths(char **file_paths, size_t i)
{
	while (i-- > 1)
		free(file_paths[i - 1]);
	free(file_paths);
	return (NULL);
}

static char	**make_sprite_file_paths(char *path, size_t n_frames, size_t i)
{
	char	**file_paths;
	char	*temp;

	if (n_frames == 0)
		return (NULL);
	file_paths = ft_calloc(n_frames, sizeof(char *));
	if (!file_paths)
		return (NULL);
	while (++i <= n_frames)
	{
		temp = ft_itoa(-i);
		if (!temp)
			return (destroy_file_paths(file_paths, i));
		file_paths[i - 1] = ft_strjoin(path, temp);
		free(temp);
		if (!file_paths[i - 1])
			return (destroy_file_paths(file_paths, i));
		temp = ft_strjoin(file_paths[i - 1], ".xpm");
		free(file_paths[i - 1]);
		if (!temp)
			return (destroy_file_paths(file_paths, i));
		file_paths[i - 1] = temp;
	}
	return (file_paths);
}

// receives a path, the number of frames to look for & the frame rate
// expects to find n frames, titled "<path>-1.xpm" through "<path>-<n>.xpm"
static t_error	init_sprite(t_sprite *sprite, char *base_path)
{
	t_error	err;
	char	**file_paths;
	size_t	i;

	sprite->frames = NULL;
	err = NO_ERROR;
	if (sprite->frame_count == 0)
		return (E_SPRITE_ZERO_FRAMES);
	sprite->frame_time = 1.0f / sprite->frames_per_second;
	sprite->frames = ft_calloc(sprite->frame_count, sizeof(t_image));
	if (!sprite->frames)
		return (E_SPRITE_ALLOC_FAIL);
	file_paths = make_sprite_file_paths(base_path, sprite->frame_count, 0);
	if (!file_paths)
		return (E_SPRITE_ALLOC_FAIL);
	err = open_images(sprite->frames, file_paths, sprite->frame_count);
	i = 0;
	while (i < sprite->frame_count)
	{
		if (file_paths[i])
			free(file_paths[i]);
		i++;
	}
	free(file_paths);
	return (err);
}

t_error	init_sprites(t_map *map)
{
	t_error	err;
	size_t	i;

	if (map->sprite_count == 0)
		return (NO_ERROR);
	i = 0;
	while (i < map->sprite_count)
	{
		err = init_sprite(map->sprites + i, map->sprites[i].base_path);
		if (err)
		{
			if (map->sprites[i].frames)
				free(map->sprites[i].frames);
			while (i-- > 0)
				destroy_sprite(map->sprites + i);
			ft_bzero(map->sprites, sizeof(t_sprite) * map->sprite_count);
			return (err);
		}
		i++;
	}
	return (NO_ERROR);
}

// sprite format is
// S <int frame_count> <int frames_per_second> <file path>
// including basename without ending dash, number & ".xpm"
// we reject any more than 2073600 frames because that is enough frames
// for 24 hours of video at 24fps and that is a silly amount
// also more than 10000fps, pretty sure we can still discern those temporally
t_error	parse_sprite(t_map *map, char *line)
{
	static size_t	i = 0;

	if (i > 2)
		return (E_TOO_MANY_SPRITES);
	line = skip_ws(line + 2);
	map->sprites[i].frame_count = ft_atoi(line);
	if (map->sprites[i].frame_count <= 0)
		return (E_INVALID_SPRITE_INTEGER);
	if (map->sprites[i].frame_count > MAX_SPRITE_FRAME_COUNT)
		return (E_STUPID_SPRITE_FRAME_COUNT);
	line += ft_nblen(map->sprites[i].frame_count);
	line = skip_ws(line);
	map->sprites[i].frames_per_second = ft_atoi(line);
	if (map->sprites[i].frames_per_second <= 0)
		return (E_INVALID_SPRITE_INTEGER);
	if (map->sprites[i].frames_per_second > 10000)
		return (E_STUPID_SPRITE_FPS);
	line += ft_nblen(map->sprites[i].frames_per_second);
	line = skip_ws(line);
	trim_whitespace(line);
	if (ft_strlen(line) < 1)
		return (E_BAD_SPRITE_PATH);
	map->sprites[i].base_path = line;
	i++;
	return (NO_ERROR);
}
