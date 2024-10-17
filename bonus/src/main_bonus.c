/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 03:49:27 by xgossing          #+#    #+#             */
/*   Updated: 2024/10/02 18:46:27 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static bool	set_up_game(t_config *config, char *file_path)
{
	t_error	err;

	err = init_config(config);
	if (!err)
		err = open_map(config, file_path);
	if (!err)
		err = parse_map_file(config, &config->raw_map, &config->map);
	if (!err)
		err = set_doors(&config->map);
	if (!err)
		err = open_images(config->map.tex, config->raw_map.texture_paths,
				config->map.texture_count);
	if (!err)
		err = init_sprites(&config->map);
	if (err != NO_ERROR)
	{
		print_error(err);
		return (false);
	}
	init_hooks(&config->mlx);
	return (true);
}

static void	set_up_getters(t_config *config)
{
	get_config(config);
	get_mlx(&config->mlx);
	get_map(&config->map);
	get_player(&config->player);
}

// hide mouse later - causes a memory leak!
// mlx_mouse_hide(config.mlx.xvar, config.mlx.window);
// mlx_mouse_show(config.mlx.xvar, config.mlx.window);
static int	run_game(int argc, char **argv)
{
	t_config	config;

	if (argc != 2)
	{
		print_error(E_INCORRECT_ARGC);
		return (1);
	}
	set_up_getters(&config);
	if (!set_up_game(&config, argv[1]))
	{
		destroy_config();
		return (1);
	}
	mlx_mouse_move(config.mlx.xvar, config.mlx.window, config.mouse.center.x,
		config.mouse.center.y);
	config.mouse.pos = config.mouse.center;
	set_player_plane(&config.player);
	mlx_do_key_autorepeatoff(config.mlx.xvar);
	mlx_loop(config.mlx.xvar);
	mlx_do_key_autorepeaton(config.mlx.xvar);
	destroy_config();
	return (0);
}

int	main(int argc, char **argv)
{
	return (run_game(argc, argv));
}
