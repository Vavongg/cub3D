/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:54:53 by ainthana          #+#    #+#             */
/*   Updated: 2025/12/10 16:52:21 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	fill_map_row(char *row, char *line, int width)
{
	int	x;
	int	len;

	x = 0;
	len = ft_strlen(line);
	while (x < width)
	{
		if (x < len && line[x] != '\n' && line[x] != '\r')
		{
			if (line[x] == '\t')
				row[x] = ' ';
			else
				row[x] = line[x];
		}
		else
			row[x] = ' ';
		x++;
	}
	row[width] = '\0';
}

static void	find_player(char c, int x, int y, t_config *config)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		config->player.x = x + 0.5;
		config->player.y = y + 0.5;
		config->player.dir = c;
	}
}

static void	init_map(t_config *config, char **lines, int *height, int *width)
{
	int	i;
	int	len;
	int	max;

	*height = 0;
	i = 0;
	len = 0;
	max = 0;
	while (lines[*height])
	{
		len = ft_strlen(lines[*height]);
		if (len > max)
			max = len;
		(*height)++;
	}
	*width = max;
	config->map.grid = malloc(sizeof(char *) * (*height + 1));
	if (!config->map.grid)
		print_error("Error : allocation failed for map");
	config->map.height = *height;
	config->map.width = *width;
}

static void fill_line(char *dest, char *src, t_config *config, int y)
{
    int x;

    x = 0;
    while (x < (int)ft_strlen(src))
    {
        find_player(src[x], x, y, config);
        x++;
    }
    fill_map_row(dest, src, config->map.width);
}

void	parse_map(char **lines, t_config *config)
{
	int	y;
	int	height;
	int	width;

	init_map(config, lines, &height, &width);
	y = 0;
	while (y < height)
	{
		config->map.grid[y] = malloc(sizeof(char) * (width + 1));
		if (!config->map.grid[y])
			print_error("Error : allocation failed for map row");
		fill_line(config->map.grid[y], lines[y], config, y);
		y++;
	}
	config->map.grid[height] = NULL;
}
