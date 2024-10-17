/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:36:16 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/09/24 23:57:10 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	calculate_wall(t_ray *ray, t_wall *wall, t_image *img,
		t_config *config)
{
	double	offset;
	double	tex_x;
	double	step;

	if (ray->side == 0)
		offset = ray->pos.y + ray->wall_dist * ray->dir.y;
	else
		offset = ray->pos.x + ray->wall_dist * ray->dir.x;
	offset -= (int)offset;
	tex_x = round(offset * (double)img->width);
	if (tex_x < 0.0f)
		tex_x = 0.0f;
	else if (tex_x >= img->width)
		tex_x = img->width - 1;
	if ((!ray->side && ray->dir.x > 0) || (ray->side == 1 && ray->dir.y < 0))
		tex_x = img->width - tex_x - 1;
	step = (double)img->height / ray->line_height;
	wall->tex_offset = ((double)ray->draw_start - (config->win.half_height)
			+ (ray->line_height >> 1)) * step;
	wall->offset = offset;
	wall->tex.x = tex_x;
	wall->step = step;
}

static t_image	*get_sprite_if_so_inclined(t_image *defaulet,
		t_sprite *the_alternative, bool inclination)
{
	t_image	*image;

	if (!inclination)
		return (defaulet);
	image = get_sprite_img(the_alternative, get_precise_time());
	if (!image)
		return (defaulet);
	return (image);
}

void	draw_wall(t_config *config, t_ray *ray, int x)
{
	t_image_buffer_caches	caches;
	t_wall					wall;
	t_image					*img;
	int						y;

	img = get_sprite_if_so_inclined((config->map.tex) + (ray->tex),
			config->map.sprites, config->player.keys[COOL_WALLS_ACTIVE]);
	calculate_wall(ray, &wall, img, config);
	caches.image_vcache = img->vcache[img->width - 1 - (int)wall.tex.x];
	caches.image_data = (uint32_t *)(img->data);
	caches.frame_vcache = config->vertical_index_cache[x];
	caches.frame_data = config->frame.data;
	wall.img_height = img->height;
	wall.draw_end = ray->draw_end;
	y = ray->draw_start;
	while (y < wall.draw_end)
	{
		fast_write_pxl(caches.frame_data, caches.frame_vcache[y],
			caches.image_data[caches.image_vcache[(int)wall.tex_offset
			% wall.img_height]]);
		wall.tex_offset += wall.step;
		y++;
	}
}

void	scale_image(t_image *src, uint32_t *s_data, t_image *target,
		uint32_t *t_data)
{
	int		x;
	int		y;
	double	unscaled_y;
	double	scale_x;
	double	scale_y;

	scale_x = (double)src->width / (double)target->width;
	scale_y = (double)src->height / (double)target->height;
	y = 0;
	while (y < target->height)
	{
		unscaled_y = y * scale_y;
		x = 0;
		while (x < target->width)
		{
			t_data[(y * target->line_len / 4) + x] = s_data[((int)unscaled_y
					* src->line_len / 4) + (int)(x * scale_x)];
			x++;
		}
		y++;
	}
}
