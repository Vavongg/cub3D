/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:11:13 by ainthana          #+#    #+#             */
/*   Updated: 2025/12/10 16:55:21 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int  flood_fill(char **tab, t_map *map, int x, int y)
{
    if (x < 0 || y < 0 || x >= map->width || y >= map->height)
        return (0);
    if (tab[y][x] == ' ')
        return (0);
    if (tab[y][x] == '1' || tab[y][x] == 'v')
        return (1);
    tab[y][x] = 'v';
    if (!flood_fill(tab, map, x + 1, y))
        return (0);
    if (!flood_fill(tab, map, x - 1, y))
        return (0);
    if (!flood_fill(tab, map, x, y + 1))
        return (0);
    if (!flood_fill(tab, map, x, y - 1))
        return (0);
    return (1);
}

int	check_floodfill(t_config *config)
{
	int		x;
	int		y;
	char	**copy;
	int		i;
	int		result;

	copy = malloc(sizeof(char *) * (config->map.height + 1));
	if (!copy)
		return (0);
	y = 0;
	while (y < config->map.height)
	{
		copy[y] = ft_strdup(config->map.grid[y]);
		y++;
	}
	copy[y] = NULL;
	x = (int)config->player.x;
	y = (int)config->player.y;
	result = flood_fill(copy, &config->map, x, y);
	i = 0;
	while (i < config->map.height)
		free(copy[i++]);
	free(copy);
	if (!result)
	{
		error_msg("Error : map is not closed");
		return (0);
	}
	return (1);
}
