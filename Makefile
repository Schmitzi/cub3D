ifdef KEYBOARD_LAYOUT
	ifeq ($(KEYBOARD_LAYOUT), colemak)
		CFLAGS += -DCOLEMAK
	else
		CFLAGS += -DQWERTY
	endif
else
	CFLAGS += -DQWERTY
endif

# tell make to compile in parallel
NUM_JOBS	=	$(shell nproc)
MAKEFLAGS	+=	--no-print-directory --jobs=$(NUM_JOBS)

CFILES	=	cache.c \
		collision.c \
		config.c \
		debug.c \
		draw_line.c \
		drawing_utils.c \
		drawing.c \
		engine.c \
		errors.c \
		exit.c \
		game_loop.c \
		graph.c \
		hooks.c \
		image.c \
		logging.c \
		main.c \
		map.c \
		math_utils.c \
		mlx.c \
		mouse.c \
		movement.c \
		open_files.c \
		open_map.c \
		parse_map.c \
		parse_map_structure.c \
		parse_map_utils.c \
		parse_param.c \
		parse_utils.c \
		player.c \
		put_pixel.c \
		raycast.c \
		raycast_utils.c \
		renderer.c \
		string_utils.c \
		strlst.c \
		texture.c \
		utils.c \
		utils2.c \
		utils3.c \
		validation_utils.c \
		window.c 

CFILES_B	=	cache_bonus.c \
		collision_bonus.c \
		config_bonus.c \
		door_bonus.c \
		debug_bonus.c \
		draw_line_bonus.c \
		drawing_utils_bonus.c \
		drawing_bonus.c \
		engine_bonus.c \
		errors_bonus.c \
		exit_bonus.c \
		game_loop_bonus.c \
		graph_bonus.c \
		hooks_bonus.c \
		image_bonus.c \
		logging_bonus.c \
		main_bonus.c \
		map_bonus.c \
		math_utils_bonus.c \
		minimap_bonus.c \
		mlx_bonus.c \
		mouse_bonus.c \
		movement_bonus.c \
		open_files_bonus.c \
		open_map_bonus.c \
		parse_map_bonus.c \
		parse_map_structure_bonus.c \
		parse_map_utils_bonus.c \
		parse_param_bonus.c \
		parse_sprite_bonus.c \
		parse_utils_bonus.c \
		player_bonus.c \
		put_pixel_bonus.c \
		raycast_bonus.c \
		raycast_utils_bonus.c \
		renderer_bonus.c \
		sprite_bonus.c \
		string_utils_bonus.c \
		strlst_bonus.c \
		texture_bonus.c \
		utils_bonus.c \
		utils2_bonus.c \
		utils3_bonus.c \
		validation_utils_bonus.c \
		window_bonus.c 

NAME    =	cub3D
BONUS    =	cub3D_bonus

CC      =	cc
CFLAGS  +=	-g -Wall -Wextra -Werror -pedantic

CDIR    =	src
CDIR_B    =	bonus/src

ODIR    =	obj
ODIR_B    =	bonus/obj

HEADER  =	include
HEADER_B  =	bonus/include

OBJECTS =	$(addprefix $(ODIR)/, $(CFILES:.c=.o))
OBJECTS_B =	$(addprefix $(ODIR_B)/, $(CFILES_B:.c=.o))

MLX_DIR	:=	minilibx-linux
MLX_FLAGS :=	-lmlx -lXext -lX11 -lm

GNL	:=	./get_next_line
GNL_LIB	:=	$(GNL)/libget_next_line.a

all: $(NAME) $(BONUS)

bonus: $(BONUS)

$(NAME): $(GNL_LIB) $(OBJECTS) $(HEADER)/* Makefile
	@$(CC) -o $(NAME) $(CFLAGS) -I $(HEADER) $(OBJECTS) $(MLX_FLAGS) -L $(GNL) -l get_next_line
	@echo "~ CUB3D - Compiled successfully"
	@echo
	@echo "<==============================>"
	@echo "     CUB3D - Ready to play!     "
	@echo "<==============================>"
	@echo

$(BONUS): $(GNL_LIB) $(OBJECTS_B) $(HEADER_B)/* Makefile
	@$(CC) -o $(BONUS) $(CFLAGS) -I $(HEADER_B) $(OBJECTS_B) $(MLX_FLAGS) -L $(GNL) -l get_next_line
	@echo "~ CUB3D - Compiled successfully"
	@echo
	@echo "<==============================>"
	@echo "  CUB3D Bonus ~ Ready to slay!  "
	@echo "<==============================>"
	@echo

$(GNL_LIB):
	@$(MAKE) -C $(GNL)

$(ODIR)/%.o: $(CDIR)/%.c
	@mkdir -p $(ODIR)
	@$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@
	@echo "~ CUB3D - Compiled $@"

$(ODIR_B)/%.o: $(CDIR_B)/%.c
	@mkdir -p $(ODIR_B)
	@$(CC) $(CFLAGS) -I $(HEADER_B) -c $< -o $@
	@echo "~ CUB3D - Compiled $@"

clean:
	@$(MAKE) -C $(GNL) clean
	@if [ -d $(ODIR) ]; then echo "~ CUB3D - Object files deleted"; fi
	@rm -f $(OBJECTS)
	@rm -rf $(ODIR)
	@if [ -d $(ODIR_B) ]; then echo "~ CUB3D - Bonus object files deleted"; fi
	@rm -f $(OBJECTS_B)
	@rm -rf $(ODIR_B)

fclean: clean
	@$(MAKE) -C $(GNL) fclean
	@if [ -n $(NAME) ]; then echo "~ CUB3D - Binary file deleted"; fi
	@rm -f $(NAME)
	@if [ -n $(BONUS) ]; then echo "~ CUB3D - Bonus binary file deleted"; fi
	@rm -f $(BONUS)

re:	fclean
	@$(MAKE) all

valgrind: re
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME) maps/good/cheese_maze.cub
	@echo "~ CUB3D - Grinding values..."

ballgrind: re
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(BONUS) maps/bonus/creepysprites.cub
	@echo "~ CUB3D - Grinding herb ..."

.PHONY: all bonus clean fclean re valgrind ballgrind
