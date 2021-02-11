NAME = cub3D

LIBFT = libft.a
MMS = libmlx.dylib

FLAGS = gcc -g -fsanitize=address -Wall -Wextra -Werror $(HEADERS)

LIBFT_H = -I srcs/libft/
MMS_H = -I srcs/minilibx_mms/
GNL_H = -I srcs/gnl/
CUB3D_H = -I srcs/
GNL_BUFFER = -D BUFFER_SIZE=100000
HEADERS = $(LIBFT_H) $(MMS_H) $(GNL_H) $(CUB3D_H)

SRC_DIR = srcs/
OBJ_DIR = obj/
LIB_DIR = srcs/libft/
MMS_DIR = srcs/minilibx_mms/
GNL_DIR = srcs/gnl/

CFILES = main.c \
		get_next_line.c \
		get_next_line_utils.c \
		mem.c \
		parser.c \
		parser2.c \
		visual.c \
		appender.c \
		tracer.c \
		mlx_helper.c \
		printer.c \
		helper.c \
		helper2.c \
		mlx_hooks.c \
		player.c \
		init.c \
		angle_trace.c \
		trace_results.c \
		tracing_sprites.c \
		tracing_sprites2.c \
		set_vars.c \
		sort.c \
		bmp.c

CFIND = $(CFILES:%=$(SRC_DIR)%)

OFILES = $(CFILES:%.c=%.o)

OBJ = $(addprefix $(OBJ_DIR), $(OFILES))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
			@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
				@echo Building libft
				@make -C $(LIB_DIR)
				@echo Copy $(LIB_DIR)$(LIBFT) to root
				@cp $(LIB_DIR)$(LIBFT) .

	 			@echo Building metal lib
				@make -C $(MMS_DIR)
				@echo Copy $(MMS_DIR)$(MMS) to root
				@cp $(MMS_DIR)$(MMS) .
				$(FLAGS) $(HEADERS) -o $(NAME) $(addprefix $(OBJ_DIR), $(OFILES)) -lmlx -framework OpenGL -framework AppKit -lz -L. -lft

$(OBJ): $(CFIND)
				@$(MAKE) $(OFILES)
$(OFILES):
			@echo Compiled: $(@:obj/%=%)
			@gcc -Wall -Wextra -Werror $(HEADERS) $(GNL_BUFFER) -c -o $(OBJ_DIR)$@ $(SRC_DIR)$(@:%.o=%.c)
clean:
				/bin/rm -rf $(OBJ_DIR)
				@make -C $(MMS_DIR) clean
				@make -C $(LIB_DIR) clean

fclean:			clean
				@make -C $(LIB_DIR) fclean
				@make -C $(MMS_DIR) clean
				/bin/rm -f $(MMS)
				/bin/rm -f $(LIBFT)
				/bin/rm -f $(NAME)

re: 			fclean all

.PHONY:			all clean flcean re
