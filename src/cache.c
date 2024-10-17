/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 01:04:49 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/25 00:38:17 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_error	init_base_index_cache(t_config *config)
{
	size_t	x;
	size_t	y;
	size_t	i;

	config->base_index_cache = ft_calloc(config->win.width * config->win.height
			/ 2, sizeof(size_t));
	if (!config->base_index_cache)
		return (E_CACHE_INIT_FAIL);
	y = -1;
	i = 0;
	while (++y < (size_t)config->win.height)
	{
		x = 0;
		while (x < (size_t)config->win.width)
		{
			config->base_index_cache[i] = ((x * 4) + (y
						* config->frame.line_len)) / 8;
			x += 2;
			i++;
		}
	}
	config->cache_size = i;
	return (NO_ERROR);
}

t_error	init_vertical_index_cache(t_config *config)
{
	size_t	x;
	size_t	y;

	config->vertical_index_cache = ft_calloc(config->win.width,
			sizeof(size_t *));
	if (!config->vertical_index_cache)
		return (E_CACHE_INIT_FAIL);
	x = -1;
	while (++x < (size_t)config->win.width)
	{
		config->vertical_index_cache[x] = ft_calloc(config->win.height,
				sizeof(size_t));
		if (!config->vertical_index_cache[x])
			return (E_CACHE_INIT_FAIL);
		y = 0;
		while (y < (size_t)config->win.height)
		{
			config->vertical_index_cache[x][y] = ((x * 4) + (y
						* config->frame.line_len)) / 4;
			y++;
		}
	}
	config->vcache_width = config->win.width;
	return (NO_ERROR);
}

// technically, the if (vcache[i]) check while looping is redundant
// we either have a fully initialized, ready-to-use cache or vcache is NULL
static void	free_vcache(size_t **vcache, size_t size)
{
	size_t	i;

	i = 0;
	if (!vcache)
		return ;
	while (i < size)
	{
		if (vcache[i])
			free(vcache[i]);
		i++;
	}
	free(vcache);
}

void	destroy_base_index_cache(void)
{
	t_config	*config;

	config = *get_config(NULL);
	if (config->base_index_cache)
		free(config->base_index_cache);
	if (config->vertical_index_cache)
		free_vcache(config->vertical_index_cache, config->vcache_width);
	config->base_index_cache = NULL;
}
