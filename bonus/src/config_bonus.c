/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:55:01 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/24 23:57:10 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

t_config	**get_config(t_config *the_goods)
{
	static t_config	*config = NULL;

	if (the_goods)
		config = the_goods;
	return (&config);
}

t_error	init_config(t_config *config)
{
	t_error	err;

	ft_bzero(config, sizeof(t_config));
	init_window(&config->win);
	init_player(&config->player);
	init_map(&config->map);
	init_renderer(&config->render);
	init_engine(&config->engine);
	init_mouse(config);
	err = init_mlx(config);
	if (!err)
		err = init_image(&config->frame);
	if (!err)
		err = init_base_index_cache(config);
	if (!err)
		err = init_vertical_index_cache(config);
	if (!err)
		err = init_debug(&config->debug);
	config->fd = -1;
	return (err);
}

void	destroy_config(void)
{
	t_config	*config;

	config = *get_config(NULL);
	free_matrix(config->raw_map.raw);
	if (config->fd >= 0)
		close(config->fd);
	config->raw_map.raw = NULL;
	ft_strlst_clear(&config->raw_map.map_content);
	free_matrix(config->map.raster);
	config->map.raster = NULL;
	destroy_debug_info();
	destroy_sprites();
	destroy_image(&config->frame);
	destroy_base_index_cache();
	destroy_map();
	destroy_mlx();
	ft_bzero(config, sizeof(t_config));
}
