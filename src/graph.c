/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 00:51:39 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/25 00:38:17 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	draw_graph_axes(t_graph *graph)
{
	t_vector	x_axis;
	t_vector	y_axis;
	t_vector	median_line;

	x_axis.start.x = graph->position.x;
	x_axis.start.y = graph->position.y + graph->height;
	x_axis.end.x = graph->position.x + graph->width;
	x_axis.end.y = graph->position.y + graph->height;
	y_axis.start.x = graph->position.x;
	y_axis.start.y = graph->position.y;
	y_axis.end.x = graph->position.x;
	y_axis.end.y = graph->position.y + graph->height;
	median_line.start.x = graph->position.x;
	median_line.start.y = graph->position.y + (graph->height >> 1);
	median_line.end.x = graph->position.x + graph->width;
	median_line.end.y = graph->position.y + (graph->height >> 1);
	plot_line(x_axis, 0xFFFFFF);
	plot_line(y_axis, 0xFFFFFF);
	plot_line(median_line, 0xFFFFFF);
}

static uint32_t	apply_desaturation(uint32_t color, double saturation)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (int)((r * saturation) + (255 * (1 - saturation)));
	g = (int)((g * saturation) + (255 * (1 - saturation)));
	b = (int)((b * saturation) + (255 * (1 - saturation)));
	return ((r << 16) | (g << 8) | b);
}

static double	get_tick_age(size_t i, t_config *config)
{
	size_t	tt_index;
	size_t	size;
	double	age;

	tt_index = config->debug.tt_index;
	size = config->debug.size;
	if (i == tt_index)
		return (1.0);
	if (tt_index > i)
		age = (double)(tt_index - i) / size;
	else
		age = (double)(size - i + tt_index) / size;
	return (1.0 - age);
}

static void	draw_bars(t_config *config, t_graph *graph)
{
	size_t		i;
	uint32_t	color;
	t_vector	line;
	float		bar_age;

	i = 0;
	line.start.x = graph->position.x;
	line.start.y = graph->position.y + graph->height;
	line.end.x = graph->position.x;
	line.end.y = graph->position.y + graph->height;
	while (i < graph->width)
	{
		bar_age = get_tick_age(i, config);
		line.end.y = graph->position.y + graph->height
			- (config->debug.tick_times[i] * graph->y_scale);
		if (line.end.y < graph->position.y + 8)
			line.end.y = graph->position.y + 8;
		if (line.end.y > graph->position.y + graph->height)
			line.end.y = graph->position.y + graph->height;
		color = get_rg_gradient(config->debug.tick_times[i] / graph->cutoff);
		plot_line(line, apply_desaturation(color, bar_age));
		i++;
		line.start.x++;
		line.end.x++;
	}
}

//       make sure nothing breaks in case some evaluator gets funny ideas
void	draw_graph(void)
{
	t_graph		graph;
	t_config	*config;

	config = *get_config(NULL);
	if (config->win.width < 400 || config->win.height < 300)
		return ;
	graph.width = config->debug.size;
	graph.height = 256;
	graph.cutoff = config->engine.tick_duration * 16
		/ ((double)config->engine.tick_rate / config->render.render_fps);
	graph.y_scale = graph.height / graph.cutoff;
	graph.position = (t_point){GRAPH_PADDING, WINDOW_H - GRAPH_PADDING
		- graph.height};
	draw_bars(config, &graph);
	draw_graph_axes(&graph);
}
