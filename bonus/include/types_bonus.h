/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:00:24 by xgossing          #+#    #+#             */
/*   Updated: 2024/10/02 21:26:56 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_BONUS_H
# define TYPES_BONUS_H
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef WINDOW_W
#  define WINDOW_W 1280
# endif
# ifndef WINDOW_H
#  define WINDOW_H 720
# endif
# ifndef DEFAULT_RENDER_FPS
#  define DEFAULT_RENDER_FPS 60
# endif
# ifndef DEFAULT_ENGINE_FPS
#  define DEFAULT_ENGINE_FPS 240
# endif
# ifndef DEFAULT_FOV
#  define DEFAULT_FOV 90.0f
# endif
# ifndef DEFAULT_MOVE_SPEED
#  define DEFAULT_MOVE_SPEED 2.0f
# endif
# ifndef DEFAULT_PLAYER_STEP_SIZE
#  define DEFAULT_PLAYER_STEP_SIZE 0.01f
# endif
# ifndef DEFAULT_ROT_SPEED
#  define DEFAULT_ROT_SPEED 6.0f
# endif
# ifndef DEFAULT_ACCELERATION
#  define DEFAULT_ACCELERATION 0.105f
# endif
# ifndef DEFAULT_DECELERATION
#  define DEFAULT_DECELERATION 0.0235f
# endif
# ifndef DEFAULT_MOUSE_SCALING_FACTOR
#  define DEFAULT_MOUSE_SCALING_FACTOR 0.0018f
# endif
# ifndef DIAGONAL_MOVE_SPEED
#  define DIAGONAL_MOVE_SPEED 0.70710678118f
# endif
# ifndef VALID_MAP_CHARS
#  define VALID_MAP_CHARS " 01NESWD\n"
# endif
# ifndef DEFAULT_MINIMAP_WIDTH
#  define DEFAULT_MINIMAP_WIDTH 240
# endif
# ifndef DEFAULT_MINIMAP_HEIGHT
#  define DEFAULT_MINIMAP_HEIGHT 240
# endif
# ifndef MAX_GRAPH_WIDTH
#  define MAX_GRAPH_WIDTH 128
# endif
# ifndef MAX_GRAPH_HEIGHT
#  define MAX_GRAPH_HEIGHT 256
# endif
# ifndef WALL_BUFFER_DISTANCE
#  define WALL_BUFFER_DISTANCE 0.25f
# endif
# ifndef PLAYER_INTERACTION_DISTANCE
#  define PLAYER_INTERACTION_DISTANCE 3
# endif
# define DEBUG_SHOW_GRAPH 6971
# define COOL_WALLS_ACTIVE 6969
# define TILE_SIZE 16
# define MINIMAP_PADDING 10
# define WALL_DISTANCE_EPSILON 1e-6
# define GRAPH_PADDING 10
# define MAX_STEP_SIZE 0.03f
# define SHREK_ONE_FRAME_COUNT 136680
# define MAX_SPRITE_FRAME_COUNT 2400

typedef enum e_error
{
	NO_ERROR = 0,
	E_INCORRECT_ARGC,
	E_MLX_INIT_FAIL,
	E_MLX_WINDOW_INIT_FAIL,
	E_MLX_IMAGE_INIT_FAIL,
	E_FRAMEBUF_INIT_FAIL,
	E_CACHE_INIT_FAIL,
	E_IMAGE_CACHE_INIT_FAIL,
	E_DEBUG_INIT_FAIL,
	E_INVALID_MAP_EXT,
	E_MAP_OPEN_FAIL,
	E_MAP_READ_FAIL,
	E_MAP_ALLOC_FAIL,
	E_MAP_CONV_FAIL,
	E_INVALID_MAP_STRUCTURE,
	E_INVALID_PARAM,
	E_INVALID_MAP_CONFIG,
	E_INVALID_TEX_PARAM,
	E_NO_PATH_IN_TEXTURE_PARAM,
	E_INVALID_TEXTURE_EXT,
	E_INVALID_COLOR_PARAM,
	E_COLOR_OUT_OF_BOUNDS,
	E_NO_MAP,
	E_MAP_TOO_SMALL,
	E_SOMETHING_AFTER_MAP,
	E_NO_PLAYER_SPAWN,
	E_TOO_MANY_PLAYER_SPAWN,
	E_FLOOR_TOUCHES_EDGE,
	E_FLOOR_TOUCHES_VOID,
	E_IMAGE_OPEN_FAIL,
	E_IMAGE_FORMAT_FAIL,
	E_SPRITE_ALLOC_FAIL,
	E_INVALID_SPRITE_EXT,
	E_INVALID_SPRITE_TAG,
	E_BAD_FLOAT_IN_SPRITE,
	E_BAD_SPRITE_PATH,
	E_SPRITE_ZERO_FRAMES,
	E_INVALID_SPRITE_INTEGER,
	E_STUPID_SPRITE_FRAME_COUNT,
	E_BIG_SPRITE_FRAME_COUNT,
	E_STUPID_SPRITE_FPS,
	E_TOO_MANY_SPRITES,
}					t_error;

typedef struct s_error_message
{
	t_error			num;
	char			*message;
}					t_error_message;

typedef enum e_direction
{
	NO,
	EA,
	SO,
	WE,
	DO,
	S,
	F,
	C,
	INVALID_DIRECTION,
}					t_direction;

typedef struct s_type_identifiers
{
	int				no;
	int				ea;
	int				so;
	int				we;
	int				d;
	int				s;
	int				f;
	int				c;
}					t_type_identifiers;

/**
 * Vector
 */
typedef struct s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct s_point_int
{
	int				x;
	int				y;
}					t_point_int;

typedef struct s_vector
{
	t_point			start;
	t_point			end;
}					t_vector;

typedef struct s_vec3
{
	t_point			a;
	t_point			b;
	t_point			c;
}					t_vec3;

typedef struct s_strlst
{
	char			*str;
	struct s_strlst	*next;
}					t_strlst;

typedef struct s_line
{
	t_point_int		slopes;
	t_point_int		delta;
	t_vector		v;
	int				col;
}					t_line;

/**
 * MinilibX properties
 */
typedef struct s_mlx
{
	void			*xvar;
	void			*window;
}					t_mlx;

typedef struct s_tile
{
	t_point			pos;
	char			type;
	bool			in_bounds;
	bool			visible;
}					t_tile;

/**
 * Player data
 * I.e. position, direction, velocity etc
 */
typedef struct s_player
{
	t_point			pos;
	t_point			dir;
	t_point			plane;
	double			fov;
	double			mov_speed;
	double			rot_speed;
	double			mouse_scaling_factor;
	t_point			velocity;
	float			acceleration;
	float			deceleration;
	float			focal_length;
	bool			keys[65536];
	t_tile			looking_at[PLAYER_INTERACTION_DISTANCE];
}					t_player;

typedef struct s_image
{
	void			*mlx_img;
	char			*data;
	int				width;
	int				height;
	int				bpp;
	int				line_len;
	int				endian;
	size_t			**vcache;
}					t_image;

/**
 * Window properties
 */
typedef struct s_window
{
	int				width;
	int				height;
	int				half_height;
	int				half_width;
}					t_window;

typedef struct s_raw_map
{
	char			**raw;
	t_strlst		*map_content;
	char			*texture_paths[6];
	uint32_t		ceiling[4];
	uint32_t		floor[4];
	unsigned int	player_count;
	unsigned int	sprite_count;
	int				len;
}					t_raw_map;

typedef struct s_mouse
{
	t_point			pos;
	t_point			center;
	bool			lmb;
	bool			rmb;
	bool			mmb;
}					t_mouse;

typedef struct s_renderer
{
	size_t			render_fps;
	double			last_frame;
	double			frame_time;
	size_t			frame_count;
}					t_renderer;

typedef struct s_engine
{
	size_t			tick_rate;
	double			last_tick;
	double			tick_duration;
	size_t			tick_count;
}					t_engine;

typedef struct s_door
{
	t_point			pos;
	bool			is_open;
}					t_door;
/**
 * Sprites
 */
typedef struct s_sprite
{
	t_image			*frames;
	size_t			frame_count;
	size_t			current_frame;
	double			frames_per_second;
	double			frame_time;
	double			next_frame_time;
	double			start_time;
	bool			playing;
	char			*base_path;
}					t_sprite;

/**
 * Map data
 */
typedef struct s_map
{
	char			**raster;
	unsigned int	width;
	unsigned int	height;
	unsigned int	left_bound;
	t_door			*door;
	size_t			door_count;
	t_image			tex[6];
	uint64_t		ceiling;
	uint64_t		floor;
	size_t			texture_count;
	t_sprite		*sprites;
	size_t			sprite_count;
}					t_map;

typedef struct s_wall
{
	t_point			tex;
	double			offset;
	double			step;
	double			tex_offset;
	uint32_t		color;
	int				img_height;
	int				draw_end;
}					t_wall;

typedef struct s_minimap
{
	size_t			height;
	size_t			width;
	char			tile;
	int				pixel;
	t_point			map;
	t_point			pos;
	t_point			player;
}					t_minimap;

typedef struct s_ray
{
	double			camera_x;
	t_point			dir;
	t_point			pos;
	t_point			grid_pos;
	t_point			step;
	t_point_int		step_dir;
	t_point			t_max;
	int				side;
	double			wall_dist;
	size_t			line_height;
	int				draw_start;
	int				draw_end;
	t_direction		tex;
}					t_ray;

typedef struct s_image_buffer_caches
{
	size_t			*image_vcache;
	size_t			**ivc;
	uint32_t		*image_data;
	size_t			*frame_vcache;
	size_t			**fvc;
	char			*frame_data;
}					t_image_buffer_caches;

typedef struct s_graph
{
	size_t			width;
	size_t			height;
	double			y_scale;
	double			cutoff;
	t_point			position;

}					t_graph;

typedef struct s_debug
{
	double			*tick_times;
	double			*frame_times;
	size_t			tt_index;
	size_t			ft_index;
	size_t			size;
}					t_debug;

typedef struct s_config
{
	int				fd;
	t_mlx			mlx;
	t_window		win;
	t_engine		engine;
	t_player		player;
	t_map			map;
	t_raw_map		raw_map;
	t_mouse			mouse;
	t_renderer		render;
	t_image			frame;
	size_t			*base_index_cache;
	size_t			**vertical_index_cache;
	size_t			cache_size;
	size_t			vcache_width;
	t_ray			ray;
	t_debug			debug;
}					t_config;

#endif
