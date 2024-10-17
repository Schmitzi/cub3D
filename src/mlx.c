/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 03:51:12 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/25 00:38:17 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_mlx	**get_mlx(t_mlx *mlx)
{
	static t_mlx	*stored = NULL;

	if (mlx)
		stored = mlx;
	return (&stored);
}

t_error	init_mlx(t_config *config)
{
	config->mlx.xvar = mlx_init();
	if (!config->mlx.xvar)
		return (E_MLX_INIT_FAIL);
	config->mlx.window = mlx_new_window(config->mlx.xvar, config->win.width,
			config->win.height, "Cub3D - We gots the best grafix!!!");
	if (!config->mlx.window)
		return (destroy_mlx(), E_MLX_WINDOW_INIT_FAIL);
	mlx_string_put(config->mlx.xvar, config->mlx.window, WINDOW_W / 2 - 48,
		WINDOW_H / 2 - 8, 0xFFFFFF, "Loading...");
	return (NO_ERROR);
}

void	destroy_mlx(void)
{
	t_mlx	*mlx;

	mlx = *get_mlx(NULL);
	if (mlx->window)
		mlx_destroy_window(mlx->xvar, mlx->window);
	if (mlx->xvar)
		mlx_destroy_display(mlx->xvar);
	if (mlx->xvar)
		free(mlx->xvar);
	ft_bzero(mlx, sizeof(t_mlx));
}
