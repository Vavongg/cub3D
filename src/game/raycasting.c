/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:06:53 by wassim            #+#    #+#             */
/*   Updated: 2026/01/16 18:36:12 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	init_ray(t_ray *ray, t_config *config, int x)
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

	camera_x = -(2.0 * x / (double)WIDTH - 1.0);
	dir_x = cos(config->player.angle);
	dir_y = sin(config->player.angle);
	plane_x = -sin(config->player.angle);
	plane_y = cos(config->player.angle);
	ray->dir_x = dir_x + plane_x * camera_x;
	ray->dir_y = dir_y + plane_y * camera_x;
	ray->map_x = (int)config->player.x;
	ray->map_y = (int)config->player.y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
	ray->hit = 0;
}

static void	set_step(t_ray *ray, t_config *config)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (config->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - config->player.x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (config->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - config->player.y)
			* ray->delta_dist_y;
	}
}

static void	perform_dda(t_ray *ray, t_config *config)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= config->map.height || ray->map_x < 0
			|| ray->map_x >= config->map.width)
			break ;
		if (config->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	calculate_wall_dist(t_ray *ray, t_config *config)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - config->player.x + (1.0
					- ray->step_x) / 2.0) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - config->player.y + (1.0
					- ray->step_y) / 2.0) / ray->dir_y;
	if (ray->perp_wall_dist < 0.01)
		ray->perp_wall_dist = 0.01;
}

static void	calculate_line_height(t_ray *ray)
{
	int	line_height;

	line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

static double	get_wall_x(t_ray *ray, t_config *config)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = config->player.y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = config->player.x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

static t_texture	*get_texture(t_ray *ray, t_config *config)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (&config->tex_west);
		else
			return (&config->tex_east);
	}
	else
	{
		if (ray->dir_y > 0)
			return (&config->tex_south);
		else
			return (&config->tex_north);
	}
}

void	cast_ray(t_config *config, int x, t_ray *ray)
{
	init_ray(ray, config, x);
	set_step(ray, config);
	perform_dda(ray, config);
	calculate_wall_dist(ray, config);
	calculate_line_height(ray);
	ray->wall_x = get_wall_x(ray, config);
	ray->texture = get_texture(ray, config);
}
