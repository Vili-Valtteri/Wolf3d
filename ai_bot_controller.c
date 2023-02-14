/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_bot_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 23:40:00 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/26 19:25:13 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ai_bot_follow(t_prm *prm)
{
	t_player	*player;
	t_astar		astar;

	ft_bzero(&astar, sizeof(t_astar));
	ai_bot_walk_anim(prm);
	player = prm->player;
	astar.player = player;
	astar.ai_bot = prm->ai_bot;
	if (path_following(&astar))
	{
		prm->ai_bot->path = astar.current;
		if (prm->ai_bot->path)
		{
			get_next_path(prm);
			if (prm->ai_bot->path)
				ai_bot_move(prm);
		}
	}
	free_pathfind_lst(astar.closedlist);
	free_pathfind_lst(astar.openlist);
}

static void	ai_bot_attack(t_prm *prm)
{
	if (prm->player->currentframe <= 15)
	{
		if (prm->player->currentframe == 4)
			player_take_damage(15, prm);
		prm->sprite[20].texture = 1;
	}
	else
		prm->sprite[20].texture = 0;
}

void	ai_bot_take_damage(int damage_amount, t_prm *prm)
{
	prm->ai_bot->health -= damage_amount;
	if (prm->ai_bot->health <= 0)
		prm->ai_bot->mode = dead;
}

void	ai_bot_controller(t_prm *prm)
{
	int			distance_to_player[2];
	t_ai_bot	*ai_bot;

	ai_bot = prm->ai_bot;
	if (ai_bot->mode != dead)
		ai_bot->mode = follow;
	distance_to_player[X] = prm->ai_bot->posxy[X] - prm->player->posxy[X];
	distance_to_player[Y] = prm->ai_bot->posxy[Y] - prm->player->posxy[Y];
	if (distance_to_player[X] <= 1 && distance_to_player[X] >= -1)
		if (ai_bot->mode != dead)
			if (distance_to_player[Y] <= 1 && distance_to_player[Y] >= -1)
				ai_bot->mode = attack;
	if (ai_bot->mode == follow)
		ai_bot_follow(prm);
	else if (ai_bot->mode == attack)
		ai_bot_attack(prm);
	else if (ai_bot->mode == dead)
		ai_bot_dead(prm);
}
