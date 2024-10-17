/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:58:52 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/25 00:38:17 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// sketchy. could this break anything?
static char	*trim_trailing_newline(char *str)
{
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len < 1 || str[len - 1] != '\n')
		return (str);
	str[len - 1] = '\0';
	return (str);
}

static t_error	has_valid_file_extension(char *file_path)
{
	size_t	end_index;
	size_t	i;

	if (!file_path || !*file_path)
		return (E_INVALID_MAP_EXT);
	end_index = ft_strlen(file_path) - 1;
	if (end_index < 3)
		return (E_INVALID_MAP_EXT);
	i = end_index - 3;
	if (ft_strncmp(".cub", file_path + i, 5) == 0)
		return (NO_ERROR);
	return (E_INVALID_MAP_EXT);
}

static t_error	open_and_read_the_file(char *file_path, t_config *config)
{
	t_strlst	*tmp;
	char		*line;

	config->fd = open(file_path, O_RDONLY);
	if (config->fd < 0)
		return (E_MAP_OPEN_FAIL);
	line = get_next_line(config->fd);
	while (line)
	{
		tmp = ft_strlst_new(line);
		if (!tmp && (ft_strlst_clear(&config->raw_map.map_content), true))
			return (E_MAP_READ_FAIL);
		ft_strlst_push(&config->raw_map.map_content, tmp);
		line = get_next_line(config->fd);
	}
	config->raw_map.len = ft_strlst_len(config->raw_map.map_content);
	tmp = config->raw_map.map_content;
	config->raw_map.raw = ft_calloc(config->raw_map.len + 1, sizeof(char *));
	if (!config->raw_map.raw)
		return (E_MAP_CONV_FAIL);
	return (NO_ERROR);
}

static t_error	strlst_to_array(t_config *config)
{
	int			i;
	t_strlst	*tmp;

	i = 0;
	tmp = config->raw_map.map_content;
	while (i < config->raw_map.len)
	{
		config->raw_map.raw[i] = trim_trailing_newline(ft_strndup(tmp->str,
					ft_strlen(tmp->str)));
		if (!config->raw_map.raw[i])
		{
			while (i > 0)
				free(config->raw_map.raw[--i]);
			free(config->raw_map.raw);
			return (E_MAP_CONV_FAIL);
		}
		tmp = tmp->next;
		i++;
	}
	config->raw_map.raw[i] = NULL;
	return (NO_ERROR);
}

t_error	open_map(t_config *config, char *file_path)
{
	t_error	err;

	err = has_valid_file_extension(file_path);
	if (!err)
		err = open_and_read_the_file(file_path, config);
	if (!err)
		err = strlst_to_array(config);
	return (err);
}
