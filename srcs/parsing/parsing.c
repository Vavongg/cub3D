/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:54:53 by ainthana          #+#    #+#             */
/*   Updated: 2025/10/29 17:37:40 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_file(char *filename)
{
	int len = ft_strlen(filename);

	if (len < 4  || ft_strcmp(filename + len - 4, ".cub") != 0)
	{
		printf(RED"Error\nFichier invalide: extension .cub requise\n"RESET);
		return (0);
	}
	return (1);
}