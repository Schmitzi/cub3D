/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 08:43:43 by mgeiger-          #+#    #+#             */
/*   Updated: 2024/10/02 19:52:15 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

static void	next_cell(t_ray *ray, t_point *t_max, t_point *grid_pos)
{
	if (t_max->x < t_max->y)
	{
		t_max->x += ray->step.x;
		grid_pos->x += ray->step_dir.x;
		ray->side = 0;
		if (ray->dir.x > 0)
			ray->tex = WE;
		else
			ray->tex = EA;
	}
	else
	{
		t_max->y += ray->step.y;
		grid_pos->y += ray->step_dir.y;
		ray->side = 1;
		if (ray->dir.y > 0)
			ray->tex = NO;
		else
			ray->tex = SO;
	}
}

static void	calculate_ray(t_ray *ray, t_point dir, t_point pos)
{
	if (dir.x != 0)
		ray->step.x = fabs(1 / dir.x);
	else
		ray->step.x = 1e30;
	if (dir.y != 0)
		ray->step.y = fabs(1 / dir.y);
	else
		ray->step.y = 1e30;
	if (dir.x > 0)
		ray->t_max.x = (ceil(pos.x) - pos.x) * ray->step.x;
	else
		ray->t_max.x = (pos.x - floor(pos.x)) * ray->step.x;
	if (dir.y > 0)
		ray->t_max.y = (ceil(pos.y) - pos.y) * ray->step.y;
	else
		ray->t_max.y = (pos.y - floor(pos.y)) * ray->step.y;
	if (dir.x > 0)
		ray->step_dir.x = 1;
	else
		ray->step_dir.x = -1;
	if (dir.y > 0)
		ray->step_dir.y = 1;
	else
		ray->step_dir.y = -1;
}

static void	cast_ray(t_config *config, t_ray *ray, t_point grid_pos, int x)
{
	int		width;
	int		height;
	size_t	i;
	char	**raster;

	width = config->map.width;
	height = config->map.height;
	i = 0;
	raster = config->map.raster;
	while (grid_pos.x >= 0 && grid_pos.x < width && grid_pos.y >= 0
		&& grid_pos.y < height && i < 432)
	{
		if (raster[(int)grid_pos.y][(int)grid_pos.x] != '0')
		{
			ray->grid_pos.x = grid_pos.x;
			ray->grid_pos.y = grid_pos.y;
			get_intersection_data(config->win.height, ray);
			if (raster[(int)grid_pos.y][(int)grid_pos.x] == 'D')
				ray->tex = DO;
			draw_wall(config, ray, x);
			return ;
		}
		next_cell(ray, &ray->t_max, &grid_pos);
		i++;
	}
}

// should figure out which tile the player is centrally looking at
// (i.e. exactly at player.dir)
// and how far away that tile is, then store it in player->looking_at
static void	get_tile_in_front_of_player(t_config *config, t_tile *looking_at,
		char **raster)
{
	t_ray	ray;
	size_t	i;
	bool	visible;

	ray.pos = config->player.pos;
	ray.camera_x = 0;
	ray.dir = config->player.dir;
	ray.grid_pos = (t_point){(int)ray.pos.x, (int)ray.pos.y};
	calculate_ray(&ray, ray.dir, ray.pos);
	ft_bzero(&config->player.looking_at, sizeof(t_tile)
		* PLAYER_INTERACTION_DISTANCE);
	visible = true;
	i = 0;
	next_cell(&ray, &ray.t_max, &ray.grid_pos);
	while (i < PLAYER_INTERACTION_DISTANCE && ray.grid_pos.x >= 0
		&& ray.grid_pos.x < config->map.width && ray.grid_pos.y >= 0
		&& ray.grid_pos.y < config->map.height)
	{
		looking_at[i].pos = (t_point){(int)ray.grid_pos.x, (int)ray.grid_pos.y};
		looking_at[i].type = raster[(int)ray.grid_pos.y][(int)ray.grid_pos.x];
		looking_at[i].in_bounds = true;
		looking_at[i].visible = visible;
		visible = config->player.looking_at[i].type == '0';
		(next_cell(&ray, &ray.t_max, &ray.grid_pos), i++);
	}
}

void	render_scene(t_config *config, t_player *player)
{
	int		x;
	int		width;
	t_ray	ray;
	t_point	grid_pos;
	double	half_width;

	ft_bzero(&ray, sizeof(t_ray));
	half_width = config->win.half_width;
	width = config->win.width;
	ray.pos.x = player->pos.x;
	ray.pos.y = player->pos.y;
	grid_pos.x = (int)ray.pos.x;
	grid_pos.y = (int)ray.pos.y;
	x = -1;
	while (++x < width)
	{
		ray.camera_x = x / half_width - 1;
		ray.dir.x = player->dir.x + player->plane.x * ray.camera_x;
		ray.dir.y = player->dir.y + player->plane.y * ray.camera_x;
		ray.grid_pos.x = grid_pos.x;
		ray.grid_pos.y = grid_pos.y;
		calculate_ray(&ray, ray.dir, ray.pos);
		cast_ray(config, &ray, grid_pos, x);
	}
	get_tile_in_front_of_player(config, player->looking_at, config->map.raster);
}
