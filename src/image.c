/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:58:39 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/25 00:38:17 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_error	init_image(t_image *image)
{
	t_config	*config;

	config = *get_config(NULL);
	image->mlx_img = mlx_new_image(config->mlx.xvar, config->win.width,
			config->win.height);
	if (!image->mlx_img)
		return (E_MLX_IMAGE_INIT_FAIL);
	image->data = mlx_get_data_addr(image->mlx_img, &image->bpp,
			&image->line_len, &image->endian);
	image->height = config->win.height;
	image->width = config->win.width;
	return (NO_ERROR);
}

static void	destroy_image_vcache(t_image *image)
{
	int	i;

	if (!image->vcache)
		return ;
	i = 0;
	while (i < image->width)
	{
		if (image->vcache[i])
			free(image->vcache[i]);
		i++;
	}
	free(image->vcache);
}

void	destroy_image(t_image *image)
{
	t_config	*config;

	if (!image)
		return ;
	config = *get_config(NULL);
	if (image->mlx_img)
		mlx_destroy_image(config->mlx.xvar, image->mlx_img);
	destroy_image_vcache(image);
	ft_bzero(image, sizeof(t_image));
}

static t_error	init_image_vcache(t_image *image)
{
	int	x;
	int	y;

	image->vcache = ft_calloc(image->width, sizeof(size_t *));
	if (!image->vcache)
		return (E_IMAGE_CACHE_INIT_FAIL);
	x = -1;
	while (++x < image->width)
	{
		image->vcache[x] = ft_calloc(image->height, sizeof(size_t));
		if (!image->vcache[x])
			return (E_IMAGE_CACHE_INIT_FAIL);
		y = 0;
		while (y < image->height)
		{
			image->vcache[x][y] = ((x * 4) + (y * image->line_len)) / 4;
			y++;
		}
	}
	return (NO_ERROR);
}

t_error	init_image_vcaches(t_image *images, size_t count)
{
	size_t	i;
	t_error	err;

	err = NO_ERROR;
	i = 0;
	while (i < count && !err)
	{
		err = init_image_vcache(images + i);
		i++;
	}
	return (err);
}
