/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:54:53 by ainthana          #+#    #+#             */
/*   Updated: 2025/11/24 19:34:32 by ainthana         ###   ########.fr       */
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

int is_map_start(char *line)
{
    int i;

	i = 0;
    if (!line)
        return (0);
    while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
    	i++;
    if (line[i] == '0' || line[i] == '1' || line[i] == 'N' ||
        line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
        return (1);
    return (0);
}
int	is_texture(char *str)
{
	return (
		(ft_strncmp(str, "NO", 2) == 0 && str[2] == '\0')
		|| (ft_strncmp(str, "SO", 2) == 0 && str[2] == '\0')
		|| (ft_strncmp(str, "WE", 2) == 0 && str[2] == '\0')
		|| (ft_strncmp(str, "EA", 2) == 0 && str[2] == '\0')
	);
}

int	is_color(char *str)
{
	return (
		(ft_strncmp(str, "F", 1) == 0 && str[1] == '\0')
		|| (ft_strncmp(str, "C", 1) == 0 && str[1] == '\0')
	);
}


void	parse_texture(char **tokens, t_config *config)
{
	if (!ft_strncmp(tokens[0], "NO ", 3))
		config->textures.north = ft_strdup(tokens[1]);
	if (!ft_strncmp(tokens[0], "SO ", 3))
		config->textures.south = ft_strdup(tokens[1]);
	if (!ft_strncmp(tokens[0], "WE ", 3))
		config->textures.west = ft_strdup(tokens[1]);
	if (!ft_strncmp(tokens[0], "EA ", 3))
		config->textures.east = ft_strdup(tokens[1]);
}

void	assign_color(char *str, t_color *color)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(str, ',');
	if (!str)
		print_error("error : allocation failed in assign_color");
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		print_error("error : invalid RGB format");
	if (!ft_isnumber(rgb[0]) || !ft_isnumber(rgb[1]) || !ft_isnumber(rgb[2]))
		print_error("error : invalid RGB values");
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		print_error("error : RGB out of range (must be between 0 and 255)");
	color->r = r;
	color->g = g;
	color->b = b;
	free_split(rgb);
}

void	parse_color(char **tokens, t_config *config)
{
	if (!ft_strncmp(tokens[0], "F", 1))
		assign_color(tokens[1], &config->floor); //faire assign_color qui decoupera le rgb;
	else if (!ft_strncmp(tokens[0], "C", 1))
		assign_color(tokens[1], &config->ceiling);
	else
		print_error("Invalid color identifier");
}

void	parse_config_line(char *line, t_config *config)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
		return ;
	if (is_texture(tokens[0]))
		parse_texture(tokens, config);
	else if (is_color(tokens[0]))
		parse_color(tokens, config);
	else
		print_error("Unknown configuration line");
	free_split(tokens);
}

void	parse_cub(char **tab, t_config *config)
{
	int	i;

	i = 0;
	if (!tab[i])
		print_error("No map found in .cub file");
	while (tab[i] && is_empty_line(tab[i]))
		i++;
	while (tab[i] && !is_map_start(tab[i]))
	{
		if (!is_empty_line(tab[i]))
			parse_config_line(tab[i], config);
		i++;
	}
	parse_map(&tab[i], config);
	is_valid_map(config);
}
