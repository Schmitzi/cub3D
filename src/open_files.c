/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 00:36:46 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/25 00:38:17 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	can_open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	return (true);
}

static bool	open_image(t_image *o, char *fpath)
{
	void	*xvar;

	xvar = (*get_mlx(NULL))->xvar;
	o->mlx_img = mlx_xpm_file_to_image(xvar, fpath, &o->width, &o->height);
	if (!o->mlx_img)
		return (false);
	o->data = mlx_get_data_addr(o->mlx_img, &o->bpp, &o->line_len, &o->endian);
	return (true);
}

t_error	open_images(t_image *target, char **file_paths, size_t count)
{
	size_t	i;
	void	*xvar;

	xvar = (*get_mlx(NULL))->xvar;
	i = 0;
	while (i < count)
	{
		if (!can_open_file(file_paths[i]))
		{
			while (i-- > 0)
				(mlx_destroy_image(xvar, target[i].mlx_img),
					ft_bzero(&target[i], sizeof(t_image)));
			return (E_IMAGE_OPEN_FAIL);
		}
		if (!open_image(&target[i], file_paths[i]))
		{
			while (i-- > 0)
				(mlx_destroy_image(xvar, target[i].mlx_img),
					ft_bzero(&target[i], sizeof(t_image)));
			return (E_IMAGE_FORMAT_FAIL);
		}
		i++;
	}
	return (init_image_vcaches(target, count));
}
