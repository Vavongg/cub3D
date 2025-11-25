/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:39:05 by ainthana          #+#    #+#             */
/*   Updated: 2025/11/25 16:42:59 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_file(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
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

char *trim_newline(char *line)
{
    int len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    return line;
}

// char **read_cub_file(int fd)
// {
//     char    **tab = NULL;
//     char    *line;
//     char    **new_tab;
//     int     count = 0;
//     int     i;

//     while ((line = get_next_line(fd)) != NULL)
//     {
//         new_tab = malloc(sizeof(char *) * (count + 2));
//         if (!new_tab)
//             print_error("error: allocation failed while reading .cub file");
//         i = 0;
//         while (i < count)
//         {
//             new_tab[i] = tab[i];
//             i++;
//         }
//         new_tab[count] = line;
//         new_tab[count + 1] = NULL;
//         free(tab);
//         tab = new_tab;
//         count++;
//     }
//     return (tab);
// }

// char **read_cub_file(int fd)
// {
//     char    **tab = NULL;
//     char    *line;
//     char    **new_tab;
//     int     count = 0;
//     int     i;

//     while ((line = get_next_line(fd)) != NULL)
//     {
//         line = trim_newline(line);
//         new_tab = malloc(sizeof(char *) * (count + 2));
//         if (!new_tab)
//             print_error("error: allocation failed while reading .cub file");
//         i = 0;
//         while (i < count)
//         {
//             new_tab[i] = tab[i];
//             i++;
//         }
//         new_tab[count] = line;
//         new_tab[count + 1] = NULL;
//         free(tab);
//         tab = new_tab;
//         count++;
//     }
//     return tab;
// }

char **read_cub_file(int fd)
{
    char    **tab = NULL;
    char    *line;
    char    **new_tab;
    int     count = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        // retirer le \n
        int len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        // allouer un nouveau tableau de pointeurs
        new_tab = malloc(sizeof(char *) * (count + 2));
        if (!new_tab)
            print_error("error: allocation failed while reading .cub file");

        // copier les anciens pointeurs
        for (int i = 0; i < count; i++)
            new_tab[i] = tab[i];

        new_tab[count] = line;      // ajouter la nouvelle ligne
        new_tab[count + 1] = NULL;

        free(tab);                  // libérer seulement le tableau de pointeurs
        tab = new_tab;
        count++;
    }
    return tab;
}


