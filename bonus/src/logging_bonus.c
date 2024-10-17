/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:55:29 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/24 23:57:10 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	log_tick_time(t_config *config, double time)
{
	config->debug.tt_index++;
	if (config->debug.tt_index == config->debug.size)
		config->debug.tt_index = 0;
	config->debug.tick_times[config->debug.tt_index] = time;
}

void	log_frame_time(t_config *config, double time)
{
	config->debug.ft_index++;
	if (config->debug.ft_index == config->debug.size)
		config->debug.ft_index = 0;
	config->debug.frame_times[config->debug.ft_index] = time;
}
