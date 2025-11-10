/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:56:07 by ainthana          #+#    #+#             */
/*   Updated: 2025/11/10 16:38:56 by ainthana         ###   ########.fr       */
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
	char	**lines;
	int		i;

	if (ac != 2)
		return (printf("\033[31mError\nUsage : ./cub3d <map.cub>\033[0m\n"), 1);

	// Vérifie le fichier
	if (!check_file(av[1]))
		return (1);

	// Ouvre le fichier
	fd = open_cub_file(av[1]);

	// Lit le fichier et stocke les lignes
	lines = read_cub_file(fd);
	close(fd); // on ferme le fd après lecture
	if (!lines)
		return (fprintf(stderr, "Error: failed to read file\n"), 1);

	// Affiche les lignes pour test
	i = 0;
	while (lines[i])
	{
		printf("[%d]: %s", i, lines[i]);
		i++;
	}

	// Libère la mémoire
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);

	return (0);
}