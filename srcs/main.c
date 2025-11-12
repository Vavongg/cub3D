/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:56:07 by ainthana          #+#    #+#             */
/*   Updated: 2025/11/12 12:49:41 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// int	main(int ac, char **av)
// {
// 	if (ac != 2)
// 		return (printf(RED"Error\nUsage : ./cub3d <maps.cub>\n"RESET), 1);
// 	if (!check_file(av[1]))
// 		return (1);
// 	printf(GREEN"Loading map %s\n"RESET, av[1]);
// 	return (0);
// }

int	main(int ac, char **av)
{
	int		fd;
	char	**tab;
	int		i;

	if (ac != 2)
		return (printf("\033[31mError\nUsage : ./cub3d <map.cub>\033[0m\n"), 1);
	if (!check_file(av[1]))
		return (1);
	fd = open_cub_file(av[1]);
	tab = read_cub_file(fd);
	close(fd);
	if (!tab)
		return (fprintf(stderr, "Error: failed to read file\n"), 1);
	i = 0;
	while (tab[i])
	{
		printf("[%d]: %s", i, tab[i]);
		i++;
	}
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}