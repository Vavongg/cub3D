/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:56:48 by ainthana          #+#    #+#             */
/*   Updated: 2025/10/29 17:40:08 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>


// Couleurs ANSI pour printf

# define RESET       "\033[0m"
# define BOLD        "\033[1m"

# define RED         "\033[31m"
# define GREEN       "\033[32m"
# define YELLOW      "\033[33m"
# define BLUE        "\033[34m"
# define MAGENTA     "\033[35m"
# define CYAN        "\033[36m"
# define WHITE       "\033[37m"

// keys

# define KEY_W        119
# define KEY_A        97
# define KEY_S        115
# define KEY_D        100
# define KEY_ESC      65307
# define KEY_LEFT     65361
# define KEY_RIGHT    65363


// Stuctures
typedef struct	s_textures {
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_textures;

typedef struct	s_color {
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct	s_map {
	char	**grid;
	int		width;
	int		height;		
}	t_map;

typedef struct s_player {
	double	x;
	double	y;
	char	dir; //point cardinaux
}	t_player;

typedef struct s_config {
    t_textures  textures;
    t_color     floor;
    t_color     ceiling;
    t_map       map;
    t_player    player;
} t_config;

// functions

int	check_file(char *filename);
int	ft_strlen(char *str);
int ft_strcmp(const char *s1, const char *s2);

#endif