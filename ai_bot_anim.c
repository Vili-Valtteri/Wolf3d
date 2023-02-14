/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_bot_anim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:02:12 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/26 15:01:11 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ai_bot_walk_anim(t_prm *prm)
{
	if (prm->player->currentframe <= 7)
		prm->sprite[20].texture = 8;
	else if (prm->player->currentframe <= 15)
		prm->sprite[20].texture = 9;
	else if (prm->player->currentframe <= 22)
		prm->sprite[20].texture = 10;
	else if (prm->player->currentframe <= 30)
		prm->sprite[20].texture = 11;
	else if (prm->player->currentframe <= 38)
		prm->sprite[20].texture = 8;
	else if (prm->player->currentframe <= 45)
		prm->sprite[20].texture = 9;
	else if (prm->player->currentframe <= 52)
		prm->sprite[20].texture = 10;
	else
		prm->sprite[20].texture = 11;
}

void	ai_bot_dead(t_prm *prm)
{
	if (prm->sprite[20].texture >= 12 || prm->player->currentframe == 0)
	{
		if (prm->sprite[20].texture != 16)
		{
			if (prm->player->currentframe <= 12)
				prm->sprite[20].texture = 12;
			else if (prm->player->currentframe <= 24)
				prm->sprite[20].texture = 13;
			else if (prm->player->currentframe <= 36)
				prm->sprite[20].texture = 14;
			else if (prm->player->currentframe <= 48)
				prm->sprite[20].texture = 15;
			else if (prm->player->currentframe <= 60)
				prm->sprite[20].texture = 16;
		}
	}
}

void	ai_bot_move(t_prm *prm)
{
	t_player	*player;
	t_ai_bot	*ai_bot;
	int			map_xy[2];

	player = prm->player;
	ai_bot = prm->ai_bot;
	ai_bot->dirxy[X] = ((ai_bot->path->vector[X] + 0.5) - ai_bot->posxy[X]);
	ai_bot->dirxy[Y] = ((ai_bot->path->vector[Y] + 0.5) - ai_bot->posxy[Y]);
	map_xy[X] = (int)(ai_bot->posxy[X] + ai_bot->dirxy[X] * \
	(player->movespeed / ai_bot->slowspeed));
	map_xy[Y] = (int)(ai_bot->posxy[Y] + ai_bot->dirxy[Y] * \
	(player->movespeed / ai_bot->slowspeed));
	if (player->worldmap[map_xy[X]][(int)ai_bot->posxy[Y]] == 0)
		ai_bot->posxy[X] += (ai_bot->path->vector[X] + 0.5 - prm->sprite[20].x) \
		* (player->movespeed / ai_bot->slowspeed);
	if (player->worldmap[(int)(ai_bot->posxy[X])][map_xy[Y]] == 0)
		ai_bot->posxy[Y] += (ai_bot->path->vector[Y] + 0.5 - prm->sprite[20].y) \
		* (player->movespeed / ai_bot->slowspeed);
	prm->sprite[20].x = ai_bot->posxy[X];
	prm->sprite[20].y = ai_bot->posxy[Y];
}

void	get_next_path(t_prm *prm)
{
	t_player	*player;
	t_ai_bot	*ai_bot;

	player = prm->player;
	ai_bot = prm->ai_bot;
	if (ai_bot->path)
		if (ai_bot->path->vector[X] == (int)ai_bot->posxy[X])
			if (ai_bot->path->vector[Y] == (int)ai_bot->posxy[Y])
				if (ai_bot->path->parent)
					ai_bot->path = ai_bot->path->parent;
}
