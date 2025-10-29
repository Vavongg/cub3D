# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/29 12:00:59 by ainthana          #+#    #+#              #
#    Updated: 2025/10/29 13:03:24 by ainthana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ==========================================================
#                       CONFIGURATION
# ==========================================================
NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3
MLX_DIR     = minilibx-linux
MLX_LIB     = $(MLX_DIR)/libmlx.a
MLX_LINUX   = $(MLX_DIR)/libmlx_Linux.a
LFLAGS      = $(MLX_LIB) $(MLX_LINUX) -lX11 -lXext

SRC         = srcs/main.c
OBJ_DIR     = obj
OBJ         = $(SRC:%.c=$(OBJ_DIR)/%.o)

BONUS_SRC   = 
BONUS_OBJ   = $(BONUS_SRC:%.c=$(OBJ_DIR)/%.o)

# ==========================================================
#                       RULES
# ==========================================================
all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB) $(MLX_LINUX)
	$(CC) $(OBJ) $(LFLAGS) -o $(NAME)

# ==========================================================
# Object files
# ==========================================================
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# ==========================================================
# MiniLibX
# ==========================================================
$(MLX_LIB) $(MLX_LINUX):
	$(MAKE) -C $(MLX_DIR)

# ==========================================================
# Cleaning
# ==========================================================
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

# ==========================================================
# Bonus
# ==========================================================
bonus: $(BONUS_OBJ)
	$(CC) $(OBJ) $(BONUS_OBJ) $(LFLAGS) -o $(NAME)

.PHONY: all clean fclean re bonus
