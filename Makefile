CC=gcc
CFLAGS= -Wall -Wextra -Werror -Ofast
MAKE=/usr/bin/make
NAME=rt

OBJ_DIR=obj
SRC_DIR=src
LIB_DIR=lib
INCLUDE_DIR=include

FT_PATH=$$(pwd)/libft
SDL_PATH=$$(pwd)/SDL2

SRCS=antialiasing.c box.c box2.c camera.c cone.c cylinder.c effect_anaglyph.c effect_blur.c effect_bwnoise.c effect_cartoon.c effect_duotone.c effect_gray.c effect_laplacian.c effect_lofi.c effect_motionblur.c effect_negative.c effect_noise.c effect_pop.c effect_prewitt.c effect_sepia.c effect_utils.c equations.c events.c graphics.c hyperboloid.c intersections.c intersections2.c key_functions.c light.c light_shading.c limit.c limit2.c list_ray.c loading_screen.c main.c matrix.c matrix_ops.c matrix_ops2.c matrix_ops3.c matrix_transformations.c negative_obj.c object_light.c object_light2.c objects.c orb_light.c parallel_light.c parsing.c parsing2.c parsing_camera.c parsing_interval.c parsing_interval2.c parsing_lights.c parsing_lights2.c parsing_limit.c parsing_negative_obj.c parsing_objects.c parsing_objects2.c parsing_scene.c parsing_textures.c parsing_textures2.c parsing_tools.c parsing_transformations.c perlin.c pixel_utils.c plane.c reflect_refract_tree.c reflexion.c refract_list.c refraction.c rendering.c scanning.c scanning2.c scene.c scene_lights.c scene_objs.c screenshot.c shadows.c shadows2.c sphere.c spotlight.c textures.c textures2.c thread_data.c triangle.c utils.c vectors.c vectors2.c vectors_transformations.c view_plane.c
OBJS=$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
LIBS=-lft -lm
LSDL2=`$(SDL_PATH)/SDL2/bin/bin/sdl2-config --cflags --libs`

.PHONY: all clean fclean re libft sdl debug-linux debug-mac


all: libft sdl $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS)
	@echo "=================================================="
	@echo
	@echo "Objects generation : ""\x1B[38;5;40m""Done.""\x1B[0m"
	@echo
	@echo "                 Building $@..."
	@echo "--------------------------------------------------"
	$(CC) $(CFLAGS) $^ -o $@ $(LSDL2) -L$(LIB_DIR) $(LIBS)
	@echo
	@echo "\x1B[38;5;40m""Done.""\x1B[0m"
	@echo
	@echo "=================================================="

$(OBJ_DIR):
	@mkdir $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $^ -o $@ -c -I$(INCLUDE_DIR)

$(LIB_DIR):
	@mkdir $@

libft: $(LIB_DIR)
	@echo "                Compiling libft..."
	@echo "--------------------------------------------------------------------\
------------"
	$(MAKE) -C $(FT_PATH)
	@echo
	@echo "                Creating symlinks..."
	@echo "--------------------------------------------------------------------\
------------"
	ln -fs $(FT_PATH)/libft.a $(LIB_DIR)
	ln -fs $(FT_PATH)/includes/libft.h $(INCLUDE_DIR)
	@echo
	@echo "\x1B[38;5;40m""Done.""\x1B[0m"
	@echo


sdl: $(LIB_DIR)
	@echo "         Installing SDL2 in $(SDL_PATH)"
	@echo "--------------------------------------------------------------------\
------------"
	@if ! [ -e $(SDL_PATH) ]; then\
		curl -o SDL2 https://www.libsdl.org/release/SDL2-2.0.5.tar.gz;\
		gunzip -c SDL2 | tar xopf -;\
		rm -rf SDL2;\
		mv -f ./SDL2-2.0.5 $(SDL_PATH);\
	fi
	@if [ ! -e $(SDL_PATH)/bin ]; then\
		mkdir $(SDL_PATH)/bin && echo "mkdir $(SDL_PATH)/bin";\
		cd SDL2 && CC=./build-scripts/gcc-fat.sh ./configure -q \
--prefix=$(SDL_PATH)/bin && make && make install;\
	fi
	@echo
	@echo "               Creating symlinks..."
	@echo "--------------------------------------------------------------------\
------------"
	ln -fs $(SDL_PATH)/SDL2/bin/lib/libSDL2.a $(LIB_DIR)
	ln -fs $(SDL_PATH)/SDL2/bin/include/SDL2 $(INCLUDE_DIR)
	@echo
	@echo "\x1B[38;5;40m""Done.""\x1B[0m"
	@echo


clean:
	@echo "                Cleaning libft..."
	@echo "--------------------------------------------------------------------\
------------"
	$(MAKE) clean -C $(FT_PATH)
	@echo
	@echo "\x1B[38;5;40m""Done.""\x1B[0m"
	@echo
	@echo "                Removing objects..."
	@echo "--------------------------------------------------------------------\
------------"
	rm -f $(OBJS)
	@echo
	@echo "\x1B[38;5;40m""Done.""\x1B[0m"
	@echo


fclean: clean
	@echo "                 Removing $(NAME)..."
	@echo "--------------------------------------------------------------------\
------------"
	rm -f $(NAME)
	@echo
	@echo "\x1B[38;5;40m""Done.""\x1B[0m"
	@echo
	@echo "                Removing libft..."
	@echo "--------------------------------------------------------------------\
------------"
	rm -f $(FT_PATH)/libft.a
	@echo
	@echo "\x1B[38;5;40m""Done.""\x1B[0m"
	@echo
	@echo "                Removing SDL2..."
	@echo "--------------------------------------------------------------------\
------------"
	rm -rf $(SDL_PATH)
	@echo
	@echo "\x1B[38;5;40m""Done.""\x1B[0m"
	@echo
	@echo "                Removing symlinks"
	@echo "--------------------------------------------------"
	rm -f $(LIB_DIR)/*
	@echo
	@echo "\x1B[38;5;40m""Done.""\x1B[0m"
	@echo


re: fclean all

debug-linux: $(OBJS)
	$(CC) $(CFLAGS) $^ -L$(LIB_DIR) $(LIBS) -lSDL2
	$(MAKE) clean

debug-mac: $(OBJS)
	$(CC) $(CFLAGS) $^ `$(SDL_PATH)/SDL2/build/bin/sdl2-config --cflags --libs`\
 -L$(LIB_DIR) -lft -lm
