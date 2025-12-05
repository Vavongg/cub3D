/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:40:34 by ainthana          #+#    #+#             */
/*   Updated: 2025/12/05 13:14:31 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void    parse_texture(char **tokens, t_config *config)
{
    if (!tokens[1] || tokens[2])
    {
        free_split(tokens);
        print_error("Error : texture configuration requires exactly one path");
    }
    if (!ft_strncmp(tokens[0], "NO", 2))
    {
        if (config->textures.north)
        {
            free_split(tokens);
            print_error("Error : north texture defined multiple times");
        }
		remove_newline(tokens[1]);
        config->textures.north = ft_strdup(tokens[1]);
    }
    else if (!ft_strncmp(tokens[0], "SO", 2))
    {
        if (config->textures.south)
        {
            free_split(tokens);
            print_error("Error : south texture defined multiple times");
        }
		remove_newline(tokens[1]);
        config->textures.south = ft_strdup(tokens[1]);
    }
}

void	parse_texture2(char **tokens, t_config *config)
{
	if (!tokens[1] || tokens[2])
    {
        free_split(tokens);
        print_error("Error : texture configuration requires exactly one path");
    }
	if (!ft_strncmp(tokens[0], "WE", 2))
    {
        if (config->textures.west)
        {
            free_split(tokens);
            print_error("Error : west texture defined multiple times");
        }
		remove_newline(tokens[1]);
        config->textures.west = ft_strdup(tokens[1]);
    }
	else if (!ft_strncmp(tokens[0], "EA", 2))
    {
        if (config->textures.east)
        {
            free_split(tokens);
            print_error("Error : east texture defined multiple times");
        }
		remove_newline(tokens[1]);
        config->textures.east = ft_strdup(tokens[1]);
    }
}

void    assign_color(char *str, t_color *color)
{
    char    **rgb;

    rgb = ft_split(str, ',');
    if (!rgb)
        print_error("Error: ft_split allocation failed");
    if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
    {
        free_split(rgb);
        print_error("Error : invalid RGB format");
    }
    remove_newline(rgb[2]);
    if (!ft_isnumber(rgb[0]) || !ft_isnumber(rgb[1]) || !ft_isnumber(rgb[2]))
    {
        free_split(rgb);
        print_error("Error : non-numeric values");
    }
    color->r = ft_atoi(rgb[0]);
    color->g = ft_atoi(rgb[1]);
    color->b = ft_atoi(rgb[2]);
    free_split(rgb);
    if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
        || color->b < 0 || color->b > 255)
        print_error("Error : RGB out of range (must be 0-255)");
}

void    parse_color(char **tokens, t_config *config)
{

    if (!tokens[1] || tokens[2])
    {
        free_split(tokens);
        print_error("Error : color configuration requires exactly one RGB value");
    }
    if (!ft_strncmp(tokens[0], "F", 1))
    {
        if (config->floor.r != -1)
        {
            free_split(tokens);
            print_error("Error : floor color defined multiple times");
        }
        assign_color(tokens[1], &config->floor);
    }
    else if (!ft_strncmp(tokens[0], "C", 1))
    {
        if (config->ceiling.r != -1)
        {
            free_split(tokens);
            print_error("Error : celing color defined multiple times");
        }
        assign_color(tokens[1], &config->ceiling);
    }
}

void    parse_config_line(char *line, t_config *config)
{
    char    **tokens;

    tokens = ft_split(line, ' ');
    if (!tokens || !tokens[0])
        return ;
    if (is_texture(tokens[0]))
    {
        if (!ft_strncmp(tokens[0], "NO", 2) || !ft_strncmp(tokens[0], "SO", 2))
            parse_texture(tokens, config);
        else
            parse_texture2(tokens, config);
    }
    else if (is_color(tokens[0]))
        parse_color(tokens, config);
    else
        print_error("Error : unknown configuration line");
    free_split(tokens);
}
