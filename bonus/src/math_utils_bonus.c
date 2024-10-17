/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xgossing <xgossing@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:04:21 by xgossing          #+#    #+#             */
/*   Updated: 2024/09/24 23:57:10 by xgossing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

double	deg_to_rad(double deg)
{
	return (deg * (M_PI / 180.0));
}

double	rad_to_deg(double rad)
{
	return (rad * (180.0 / M_PI));
}

t_point	rotate_point(t_point p, t_point origin, float angle)
{
	t_point	rotated_point;
	float	rad_angle;

	rad_angle = angle * M_PI / 180.0;
	rotated_point.x = cos(rad_angle) * (p.x - origin.x) - sin(rad_angle) * (p.y
			- origin.y) + origin.x;
	rotated_point.y = sin(rad_angle) * (p.x - origin.x) + cos(rad_angle) * (p.y
			- origin.y) + origin.y;
	return (rotated_point);
}
