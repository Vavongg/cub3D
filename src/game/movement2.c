/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 20:44:11 by ainthana          #+#    #+#             */
/*   Updated: 2026/01/18 20:44:11 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
