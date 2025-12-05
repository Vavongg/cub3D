/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:11:13 by ainthana          #+#    #+#             */
/*   Updated: 2025/12/05 13:16:48 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int  flood_fill(char **map, int x, int y, int width, int height)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return (0);
    if (map[y][x] == ' ')
        return (0);
    if (map[y][x] == '1' || map[y][x] == 'v')
        return (1);
    map[y][x] = 'v';
    if (!flood_fill(map, x + 1, y, width, height))
        return (0);
    if (!flood_fill(map, x - 1, y, width, height))
        return (0);
    if (!flood_fill(map, x, y + 1, width, height))
        return (0);
    if (!flood_fill(map, x, y - 1, width, height))
        return (0);
    return (1);
}

void	check_floodfill(t_config *config)
{
	int		x;
	int		y;
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (config->map.height + 1));
	if (!copy)
		print_error("Error : allocation failed for map validation");
	y = 0;
	while (y < config->map.height)
	{
		copy[y] = ft_strdup(config->map.grid[y]);
		if (!copy[y])
			print_error("Error : allocation failed for map validation row");
		y++;
	}
	x = (int)config->player.x;
	y = (int)config->player.y;
	if (!flood_fill(copy, x, y, config->map.width, config->map.height))
		print_error("Error: map is not closed");
	i = 0;
	while (i < config->map.height)
		free(copy[i++]);
	free(copy);
}
