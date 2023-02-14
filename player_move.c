/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:22:37 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/26 13:22:55 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	player_turn_left(t_player *player)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = player->dirxy[X];
	old_planex = player->planexy[X];
	player->dirxy[X] = player->dirxy[X] * cos(player->rotspeed) - \
	player->dirxy[Y] * sin(player->rotspeed);
	player->dirxy[Y] = old_dirx * sin(player->rotspeed) + \
	player->dirxy[Y] * cos(player->rotspeed);
	player->planexy[X] = player->planexy[X] * cos(player->rotspeed) - \
	player->planexy[Y] * sin(player->rotspeed);
	player->planexy[Y] = old_planex * sin(player->rotspeed) + \
	player->planexy[Y] * cos(player->rotspeed);
}

void	player_turn_right(t_player *player)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = player->dirxy[X];
	old_planex = player->planexy[X];
	player->dirxy[X] = player->dirxy[X] * cos(-player->rotspeed) - \
	player->dirxy[Y] * sin(-player->rotspeed);
	player->dirxy[Y] = old_dirx * sin(-player->rotspeed) + \
	player->dirxy[Y] * cos(-player->rotspeed);
	player->planexy[X] = player->planexy[X] * cos(-player->rotspeed) - \
	player->planexy[Y] * sin(-player->rotspeed);
	player->planexy[Y] = old_planex * sin(-player->rotspeed) + \
	player->planexy[Y] * cos(-player->rotspeed);
}

void	player_move_forward(t_player *player)
{
	int	map_xy[2];

	map_xy[X] = (int)(player->posxy[X] + player->dirxy[X] * player->movespeed);
	map_xy[Y] = (int)(player->posxy[Y] + player->dirxy[Y] * player->movespeed);
	if (player->worldmap[map_xy[X]][(int)player->posxy[Y]] == 0)
		player->posxy[X] += player->dirxy[X] * player->movespeed;
	if (player->worldmap[(int)(player->posxy[X])][map_xy[Y]] == 0)
		player->posxy[Y] += player->dirxy[Y] * player->movespeed;
}

void	player_move_backward(t_player *player)
{
	int	map_xy[2];

	map_xy[X] = (int)(player->posxy[X] - player->dirxy[X] * player->movespeed);
	map_xy[Y] = (int)(player->posxy[Y] - player->dirxy[Y] * player->movespeed);
	if (player->worldmap[map_xy[X]][(int)(player->posxy[Y])] == 0)
		player->posxy[X] -= player->dirxy[X] * player->movespeed;
	if (player->worldmap[(int)(player->posxy[X])][map_xy[Y]] == 0)
		player->posxy[Y] -= player->dirxy[Y] * player->movespeed;
}
