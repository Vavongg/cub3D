/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:54:53 by ainthana          #+#    #+#             */
/*   Updated: 2025/11/10 14:06:10 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_file(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strcmp(filename + len - 4, ".cub") != 0)
	{
		printf(RED"Error\nFichier invalide: extension .cub requise\n"RESET);
		return (0);
	}
	return (1);
}

int	open_cub_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(RED"Error: cannot open .cub file");
		exit(1);
	}
	return (fd);
}

char **read_cub_file(int fd)
{
	char	**tab;
	char	*line;
	int		count;
	char	**new_tab;
	int		i;

	tab = NULL;
	count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		i = -1;
		new_tab = malloc(sizeof(char *) * (count + 2));
		if (!new_tab)
			return NULL;
		while (++i < count)
			new_tab[i] = tab[i];
		new_tab[count] = line;
		new_tab[count + 1] = NULL;
		free(tab);
		tab = new_tab;
		count++;
	}
	return (tab);
}
