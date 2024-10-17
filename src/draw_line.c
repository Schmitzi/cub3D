/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:06:19 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/25 00:38:17 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	line(t_point_int slopes, t_vector *v, int col, t_config *config)
{
	while (slopes.x == 0 && slopes.y > 0 && v->start.y <= v->end.y)
	{
		slow_write_pxl(config, v->start.x, v->start.y, col);
		v->start.y += slopes.y;
	}
	while (slopes.x == 0 && slopes.y < 0 && v->start.y >= v->end.y)
	{
		slow_write_pxl(config, v->start.x, v->start.y, col);
		v->start.y += slopes.y;
	}
	while (slopes.y == 0 && slopes.x > 0 && v->start.x <= v->end.x)
	{
		slow_write_pxl(config, v->start.x, v->start.y, col);
		v->start.x += slopes.x;
	}
	while (slopes.y == 0 && slopes.x < 0 && v->start.x >= v->end.x)
	{
		slow_write_pxl(config, v->start.x, v->start.y, col);
		v->start.x += slopes.x;
	}
}

// static void	fast_plot_line(t_config *config, t_point start, t_point end,
// 		uint32_t color)
// {
// 	// somehow figure out how to draw super fast,
// 	// using fast_write_pxl and/or other trickery.
// }

static void	slanted_line(t_line *line, t_config *config)
{
	int	err;
	int	err2;

	err = line->delta.x + line->delta.y;
	while (true)
	{
		slow_write_pxl(config, line->v.start.x, line->v.start.y, line->col);
		err2 = 2 * err;
		if (err2 >= line->delta.y)
		{
			err += line->delta.y;
			line->v.start.x += line->slopes.x;
		}
		if (err2 <= line->delta.x)
		{
			err += line->delta.x;
			line->v.start.y += line->slopes.y;
		}
		if ((line->slopes.x > 0 && line->v.start.x >= line->v.end.x)
			|| (line->slopes.x < 0 && line->v.start.x <= line->v.end.x)
			|| (line->slopes.y > 0 && line->v.start.y >= line->v.end.y)
			|| (line->slopes.y < 0 && line->v.start.y <= line->v.end.y))
			break ;
	}
}

void	plot_line(t_vector vec, uint32_t color)
{
	t_config	*config;
	t_point_int	slopes;
	t_point_int	delta;

	config = *get_config(NULL);
	delta.x = fabs(vec.end.x - vec.start.x);
	delta.y = -fabs(vec.end.y - vec.start.y);
	if (vec.start.x < vec.end.x)
		slopes.x = 1;
	else if (vec.start.x == vec.end.x)
		slopes.x = 0;
	else
		slopes.x = -1;
	if (vec.start.y < vec.end.y)
		slopes.y = 1;
	else if (vec.start.y == vec.end.y)
		slopes.y = 0;
	else
		slopes.y = -1;
	if (slopes.x == 0 || slopes.y == 0)
		line(slopes, &vec, color, config);
	else
		slanted_line(&(t_line){slopes, delta, vec, color}, config);
}
