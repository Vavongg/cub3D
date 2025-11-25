/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:39:44 by ainthana          #+#    #+#             */
/*   Updated: 2025/11/25 19:01:43 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int is_map_start(char *line)
{
    int i;

    i = 0;
    if (!line)
        return (0);
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == '\0' || line[i] == '\n')
        return (0);
    if (is_texture(&line[i]) || is_color(&line[i]))
        return (0);
    if (line[i] == '0' || line[i] == '1' || line[i] == 'N' 
		|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
        return (1);
    return (0);
}
int is_texture(char *str)
{
    return ((ft_strncmp(str, "NO", 2) == 0 && str[2] == '\0')
         || (ft_strncmp(str, "SO", 2) == 0 && str[2] == '\0')
         || (ft_strncmp(str, "WE", 2) == 0 && str[2] == '\0')
         || (ft_strncmp(str, "EA", 2) == 0 && str[2] == '\0'));
}

int is_color(char *str)
{
    return ((ft_strncmp(str, "F", 1) == 0 && str[1] == '\0')
         || (ft_strncmp(str, "C", 1) == 0 && str[1] == '\0'));
}
