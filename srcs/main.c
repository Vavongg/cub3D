/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:56:07 by ainthana          #+#    #+#             */
/*   Updated: 2025/12/10 15:19:29 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_config(t_config *cfg)
{
	cfg->textures.north = NULL;
	cfg->textures.south = NULL;
	cfg->textures.west = NULL;
	cfg->textures.east = NULL;
	cfg->floor.r = -1;
	cfg->floor.g = -1;
	cfg->floor.b = -1;
	cfg->ceiling.r = -1;
	cfg->ceiling.g = -1;
	cfg->ceiling.b = -1;
	cfg->map.grid = NULL;
	cfg->map.width = 0;
	cfg->map.height = 0;
	cfg->player.x = -1;
	cfg->player.y = -1;
	cfg->player.dir = 0;
}

void	free_config(t_config *cfg)
{
	int	y;

	if (cfg->textures.north)
		free(cfg->textures.north);
	if (cfg->textures.south)
		free(cfg->textures.south);
	if (cfg->textures.west)
		free(cfg->textures.west);
	if (cfg->textures.east)
		free(cfg->textures.east);
	if (cfg->map.grid)
	{
		y = 0;
		while (y < cfg->map.height)
		{
			free(cfg->map.grid[y]);
			y++;
		}
		free(cfg->map.grid);
	}
}

int	main(int argc, char **argv)
{
	t_config	config;
	char		**tab;

	if (argc != 2)
		print_error("Usage: ./cub3d <map.cub>");
	init_config(&config);
	if (!check_file(argv[1]))
		exit(1);
	tab = read_cub_file(argv[1]);
	parse_cub(tab, &config);
	free_split(tab);
	free_config(&config);
	return (0);
}
