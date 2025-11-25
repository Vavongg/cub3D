/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:56:07 by ainthana          #+#    #+#             */
/*   Updated: 2025/11/25 16:34:08 by ainthana         ###   ########.fr       */
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

// int	main(int ac, char **av)
// {
// 	int		fd;
// 	char	**tab;
// 	int		i;

// 	if (ac != 2)
// 		return (printf("\033[31mError\nUsage : ./cub3d <map.cub>\033[0m\n"), 1);
// 	if (!check_file(av[1]))
// 		return (1);
// 	fd = open_cub_file(av[1]);
// 	tab = read_cub_file(fd);
// 	close(fd);
// 	if (!tab)
// 		return (fprintf(stderr, "Error: failed to read file\n"), 1);
// 	i = 0;
// 	while (tab[i])
// 	{
// 		printf("[%d]: %s", i, tab[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// 	return (0);
// }

int main(int argc, char **argv)
{
    t_config config;
    int fd;
    char **tab;

    if (argc != 2)
        print_error("Usage: ./cub3d <map.cub>");
    fd = open_cub_file(argv[1]);
    tab = read_cub_file(fd);
    close(fd);
    parse_cub(tab, &config);
    free_split(tab);
    return 0;
}

