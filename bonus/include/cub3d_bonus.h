/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 03:49:34 by xgossing          #+#    #+#             */
/*   Updated: 2024/10/02 20:18:33 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H
# define _USE_MATH_DEFINES
# ifdef COLEMAK
#  include "colemak_bonus.h"
# else
#  include "qwerty_bonus.h"
# endif
# include "get_next_line_bonus_bonus.h"
# include "types_bonus.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/**
 * Inintializers
 */
t_error		init_config(t_config *config);
t_error		init_mlx(t_config *config);
void		init_player(t_player *player);
void		init_window(t_window *window);
void		init_map(t_map *map);
void		init_renderer(t_renderer *render);
void		init_hooks(t_mlx *mlx);
void		init_engine(t_engine *engine);
t_error		init_image(t_image *image);
t_error		init_base_index_cache(t_config *config);
t_error		init_vertical_index_cache(t_config *config);
t_error		init_image_vcaches(t_image *images, size_t count);
void		init_mouse(t_config *config);
t_error		init_debug(t_debug *debug);
t_error		init_sprites(t_map *map);

/**
 * Getters for convenience
 */
t_config	**get_config(t_config *the_goods);
t_mlx		**get_mlx(t_mlx *mlx);
t_player	**get_player(t_player *the_goods);
t_map		**get_map(t_map *map);

/**
 * Destroyers
 */
void		destroy_mlx(void);
void		destroy_player(void);
void		destroy_map(void);
void		destroy_config(void);
void		destroy_image(t_image *image);
void		destroy_base_index_cache(void);
void		destroy_debug_info(void);
void		destroy_sprites(void);
void		destroy_sprite(t_sprite *sprite);

/**
 * Debug
 */
void		log_tick_time(t_config *config, double time);
void		log_frame_time(t_config *config, double time);
void		draw_debug_info(t_config *config);
void		draw_graph(void);
void		put_debug_info_to_window(t_config *config, t_mlx *mlx);

/**
 * Map validation & parsing
 */
void		print_error(t_error error);
t_error		open_map(t_config *config, char *file_path);
t_error		open_images(t_image *target, char **file_paths, size_t count);
t_error		parse_map_file(t_config *config, t_raw_map *raw_map, t_map *map);
bool		is_one_of(char c, char *set);
t_error		is_valid_map(t_map *map);
t_error		validate_map_structure(t_config *config, t_raw_map *raw_map);
t_error		assert_map_portion_exists(char **raw);
void		get_colours(t_config *config);

/**
 * Hooks & event handling
 */
int			loop_hook(t_config *config);
bool		any_key_pressed(t_player *player, int *keys, int size);

/**
 * Player movement / Physics
 */
int			move_player(t_config *config, double delta_time);
double		do_engine_tick(t_config *config, double current_time);
void		decelerate_player(t_player *player, double delta_time);
void		handle_player_collision(t_player *p, double distance,
				double delta_time);

/**
 * Maths stuff
 */
double		deg_to_rad(double deg);
double		rad_to_deg(double rad);
void		normalize_vector(t_point *v);

/**
 * Drawing
 */
void		plot_line(t_vector vec, uint32_t color);
void		write_rect(t_config *config, t_point start, t_point end, int color);
void		fast_write_rect(t_image *frame, t_point start, t_point end,
				uint64_t color);
void		draw_player_fov(t_player *player);
void		draw_ui(t_config *config);
void		wrap_overflow(int *val, int max);

/**
 * Rendering
 */

void		fast_draw_background(t_config *config, size_t *cache,
				char *img_data);
double		render_frame(t_config *config, double current_time);

/**
 * Raycasting
 */
void		set_player_plane(t_player *player);
void		draw_minimap(t_config *config);
void		render_scene(t_config *config, t_player *player);
void		get_intersection_data(int window_height, t_ray *ray);

/**
 * Textures
 */
void		draw_wall(t_config *config, t_ray *ray, int x);
void		pick_texture(t_ray *ray, t_map *map);
void		scale_image(t_image *src, uint32_t *s_data, t_image *target,
				uint32_t *t_data);

/**
 *  Doors
 */
bool		get_door_status(t_door *door, t_ray *ray, t_map *map);
void		toggle_door(t_player *player, t_map *map, size_t i);
t_error		set_doors(t_map *map);

/**
 * Sprites
 */
t_image		*get_sprite_img(t_sprite *sprite, double current_time);
t_image		*get_animation_img(t_sprite *sprite, int index, double current_time,
				bool trigger);
t_image		*get_sprite_if_true(t_image *defaulet, t_sprite *the_alternative,
				bool condition);

/**
 * MinilibX Utilities
 */
void		slow_write_pxl(t_config *config, int x, int y, int color);
void		fast_write_pxl(char *data, size_t base_index, uint32_t color);
void		fast_write_2pxl(char *data, size_t base_index, uint64_t color);
int			get_rgb(int r, int g, int b);

void		ft_mlx_line(t_vector line, int vector);

/**
 * Strlst
 */
t_strlst	*ft_strlst_new(char *str);
void		ft_strlst_push(t_strlst **head, t_strlst *item);
void		ft_strlst_delete(t_strlst *node);
void		ft_strlst_clear(t_strlst **head);
size_t		ft_strlst_len(t_strlst *head);

/**
 * General utilities
 */
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
size_t		ft_strlen(const char *s);
int			ft_strncmp(char *s1, char *s2, size_t n);
char		*ft_strndup(const char *s, size_t len);
char		*ft_strndup_with_padding(const char *s, size_t len,
				size_t desired_len, char pad);
void		free_matrix(char **matrix);
char		*ft_strjoin(char *s1, char *s2);
bool		is_whitespace(char c);
bool		is_whitespace_line(char *line);
bool		is_map_line(char *line);
bool		is_config_param_line(char *line);
bool		is_digit(char c);
int			ft_atoi(char *str);
char		*ft_itoa(int n);
double		get_precise_time(void);
uint32_t	get_rg_gradient(double offset);
size_t		ft_nblen(int n);

/**
 * Parsing utilities
 */

char		*skip_ws(char *str);
void		trim_whitespace(char *str);
t_direction	get_param_type(char *line);
size_t		strint_length(char *str);
bool		is_valid_color_param(char *line, int i);
t_error		parse_config_param(t_raw_map *raw_map, char *line);
t_error		parse_sprite(t_map *map, char *line);
void		count_player_spawns(char **raw);
void		get_map_dimensions(char **raw_map, t_map *map);

/**
 * Exit
 */
int			exit_game(void);

// /**
//  * Logging
//  */
// void		log_debug(void);

#endif
