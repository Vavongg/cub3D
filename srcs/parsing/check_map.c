/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:09:51 by ainthana          #+#    #+#             */
/*   Updated: 2025/12/05 11:57:30 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void check_chars(t_config *config)
{
    int y;
    int x;
    char c;

    y = 0;
    while (y < config->map.height)
    {
        x = 0;
        while (x < config->map.width)
        {
            c = config->map.grid[y][x];
            if (c != '0' && c != '1' && c != ' '
                 && c != 'N' && c != 'S' && c != 'E' && c != 'W')
                print_error("Error : invalid character in map or forbidden space (' ')");
            x++;
        }
        y++;
    }
}

void check_player(t_config *config)
{
    int y;
    int x;
    int count;

    count = 0;
    y = 0;
    while (y < config->map.height)
    {
        x = 0;
        while (x < config->map.width)
        {
            char c = config->map.grid[y][x];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                count++;
            x++;
        }
        y++;
    }
    if (count != 1)
        print_error("Error : bro, u can't play with ur mate sry");
}

void    check_all_elements_present(t_config *config)
{
    if (!config->textures.north || !config->textures.south ||
        !config->textures.west || !config->textures.east)
        print_error("Error : one or more textures are missing");
    if (config->floor.r == -1 || config->ceiling.r == -1)
        print_error("Error : floor or ceiling color is missing");
}

void is_valid_map(t_config *config)
{
    check_chars(config);
    check_player(config);
    check_floodfill(config);
}

