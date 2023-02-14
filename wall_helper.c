/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:50:45 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/26 19:36:03 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	set_ray_pos(t_player *player, t_rc_wall *wall, int x)
{
	wall->camerax = 2 * x / (double)(SCREEN_WIDTH) - 1;
	wall->raydirxy[X] = player->dirxy[X] + player->planexy[X] * wall->camerax;
	wall->raydirxy[Y] = player->dirxy[Y] + player->planexy[Y] * wall->camerax;
	wall->mapxy[X] = (int)(player->posxy[X]);
	wall->mapxy[Y] = (int)(player->posxy[Y]);
	if (wall->raydirxy[X] == 0)
		wall->deltadisxy[X] = (double)INT_MAX;
	else
		wall->deltadisxy[X] = fabs(1 / wall->raydirxy[X]);
	if (wall->raydirxy[Y] == 0)
		wall->deltadisxy[Y] = (double)INT_MAX;
	else
		wall->deltadisxy[Y] = fabs(1 / wall->raydirxy[Y]);
	wall->hit = 0;
}

void	step_direction(t_player *player, t_rc_wall *wall)
{
	if (wall->raydirxy[X] < 0)
	{
		wall->stepxy[X] = -1;
		wall->sidedistxy[X] = (player->posxy[X] - wall->mapxy[X]) \
		* wall->deltadisxy[X];
	}
	else
	{
		wall->stepxy[X] = 1;
		wall->sidedistxy[X] = (wall->mapxy[X] + 1.0 - player->posxy[X]) \
		* wall->deltadisxy[X];
	}
	if (wall->raydirxy[Y] < 0)
	{
		wall->stepxy[Y] = -1;
		wall->sidedistxy[Y] = (player->posxy[Y] - wall->mapxy[Y]) \
		* wall->deltadisxy[Y];
	}
	else
	{
		wall->stepxy[Y] = 1;
		wall->sidedistxy[Y] = (wall->mapxy[Y] + 1.0 - player->posxy[Y]) \
		* wall->deltadisxy[Y];
	}
}

void	dda_algorithm(t_player *player, t_rc_wall *wall)
{
	while (wall->hit == 0)
	{
		if (wall->sidedistxy[X] < wall->sidedistxy[Y])
		{
			wall->sidedistxy[X] += wall->deltadisxy[X];
			wall->mapxy[X] += wall->stepxy[X];
			wall->side = 0;
		}
		else
		{
			wall->sidedistxy[Y] += wall->deltadisxy[Y];
			wall->mapxy[Y] += wall->stepxy[Y];
			wall->side = 1;
		}
		if (player->worldmap[wall->mapxy[X]][wall->mapxy[Y]] > 0)
			wall->hit = 1;
		else
			player->save[wall->mapxy[X]][wall->mapxy[Y]] = 1;
	}
	if (wall->side == 0)
		player->perpwalldist = (wall->sidedistxy[X] - wall->deltadisxy[X]);
	else
		player->perpwalldist = (wall->sidedistxy[Y] - wall->deltadisxy[Y]);
}
