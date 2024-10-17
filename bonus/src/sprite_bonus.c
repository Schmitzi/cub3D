/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 23:40:35 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/24 23:57:10 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

// We skip any missed frames just bc that's probably better than
// rapid-firing pictures at the viewer after a lag or something
t_image	*get_sprite_img(t_sprite *sprite, double current_time)
{
	t_image	*curr;

	if (!sprite || !sprite->frame_count)
		return (NULL);
	if (sprite->next_frame_time == 0.0f)
	{
		sprite->next_frame_time = get_precise_time();
		sprite->current_frame = 0;
	}
	while (current_time >= sprite->next_frame_time)
	{
		sprite->current_frame++;
		if (sprite->current_frame == sprite->frame_count)
			sprite->current_frame = 0;
		sprite->next_frame_time += sprite->frame_time;
	}
	curr = sprite->frames + sprite->current_frame;
	return (curr);
}

// for "one-shot" animations, if trigger is true the animation restarts
// by default and when done playing, returns NULL
t_image	*get_animation_img(t_sprite *sprite, int index, double current_time,
		bool trigger)
{
	if (sprite && index > 0)
		sprite += index;
	if (!sprite || !sprite->frame_count)
		return (NULL);
	if (trigger)
	{
		sprite->start_time = current_time;
		sprite->next_frame_time = current_time + sprite->frame_time;
		sprite->current_frame = 0;
		sprite->playing = true;
	}
	if (!sprite->playing)
		return (NULL);
	while (sprite->playing && current_time >= sprite->next_frame_time)
	{
		if (sprite->current_frame == sprite->frame_count - 1)
		{
			sprite->playing = false;
			sprite->current_frame = 0;
			return (NULL);
		}
		sprite->next_frame_time += sprite->frame_time;
		sprite->current_frame++;
	}
	return (sprite->frames + sprite->current_frame);
}

void	destroy_sprite(t_sprite *sprite)
{
	size_t	file_index;

	if (!sprite || !sprite->frames)
		return ;
	file_index = 0;
	while (file_index < sprite->frame_count)
	{
		destroy_image(&sprite->frames[file_index]);
		file_index++;
	}
	free(sprite->frames);
}

void	destroy_sprites(void)
{
	t_config	*config;
	size_t		i;

	config = *get_config(NULL);
	i = 0;
	if (!config->map.sprites)
		return ;
	while (i < config->map.sprite_count)
	{
		destroy_sprite(&config->map.sprites[i]);
		i++;
	}
	free(config->map.sprites);
	config->map.sprites = NULL;
	config->map.sprite_count = 0;
}
