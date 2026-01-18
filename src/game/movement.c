/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:09:41 by wassim            #+#    #+#             */
/*   Updated: 2026/01/16 19:00:21 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_wall(t_config *config, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= config->map.height || map_x < 0
		|| map_x >= config->map.width)
		return (1);
	if (config->map.grid[map_y][map_x] == '1')
		return (1);
	return (0);
}

static int	can_move(t_config *config, double new_x, double new_y)
{
	double	margin;

	margin = 0.2;
	if (is_wall(config, new_x, new_y))
		return (0);
	if (is_wall(config, new_x + margin, new_y))
		return (0);
	if (is_wall(config, new_x - margin, new_y))
		return (0);
	if (is_wall(config, new_x, new_y + margin))
		return (0);
	if (is_wall(config, new_x, new_y - margin))
		return (0);
	return (1);
}

static void	apply_movement(t_config *config, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = config->player.x + dx;
	new_y = config->player.y + dy;
	if (can_move(config, new_x, new_y))
	{
		config->player.x = new_x;
		config->player.y = new_y;
	}
	else if (can_move(config, new_x, config->player.y))
	{
		config->player.x = new_x;
	}
	else if (can_move(config, config->player.x, new_y))
	{
		config->player.y = new_y;
	}
}

void	move_forward(t_config *config)
{
	double	dx;
	double	dy;

	dx = cos(config->player.angle) * MOVE_SPEED;
	dy = sin(config->player.angle) * MOVE_SPEED;
	apply_movement(config, dx, dy);
}

void	move_backward(t_config *config)
{
	double	dx;
	double	dy;

	dx = -cos(config->player.angle) * MOVE_SPEED;
	dy = -sin(config->player.angle) * MOVE_SPEED;
	apply_movement(config, dx, dy);
}

void	move_left(t_config *config)
{
	double	dx;
	double	dy;

	dx = -sin(config->player.angle) * MOVE_SPEED;
	dy = cos(config->player.angle) * MOVE_SPEED;
	apply_movement(config, dx, dy);
}

void	move_right(t_config *config)
{
	double	dx;
	double	dy;

	dx = sin(config->player.angle) * MOVE_SPEED;
	dy = -cos(config->player.angle) * MOVE_SPEED;
	apply_movement(config, dx, dy);
}

void	rotate_left(t_config *config)
{
	config->player.angle -= ROT_SPEED;
	if (config->player.angle < 0)
		config->player.angle += 2 * M_PI;
}

void	rotate_right(t_config *config)
{
	config->player.angle += ROT_SPEED;
	if (config->player.angle >= 2 * M_PI)
		config->player.angle -= 2 * M_PI;
}
