/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 00:38:13 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/26 15:38:24 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	on_death(t_prm *prm)
{
	if (prm->player->timerdead <= clock())
	{
		prm->player->isdead = 0;
		restart(prm);
	}
	end_screen(prm);
}

void	player_take_damage(int damage_amount, t_prm *prm)
{
	prm->player->health -= damage_amount;
	if (prm->player->health <= 0)
	{
		prm->player->isdead = 1;
		prm->player->timerdead = clock() + 1 * CLOCKS_PER_SEC;
	}
}

void	player_shoot(t_prm *prm)
{
	int	dist_to_bot[2];

	if (prm->player->shotgun_tex != 0)
		return ;
	dist_to_bot[X] = fabs(prm->player->posxy[X]) - fabs(prm->ai_bot->posxy[X]);
	dist_to_bot[Y] = fabs(prm->player->posxy[Y]) - fabs(prm->ai_bot->posxy[Y]);
	if (dist_to_bot[X] <= 1 && dist_to_bot[X] >= -1)
	{
		if (dist_to_bot[Y] <= 1 && dist_to_bot[Y] >= -1)
			ai_bot_take_damage(30, prm);
	}
	prm->player->shotgun_tex = 1;
	prm->player->shotgun_anim = clock();
}

void	player_controller(t_prm *prm)
{
	player_weapon(prm);
	player_health_bar(prm);
	if (prm->player->isdead == 1)
		on_death(prm);
	else
	{
		if (prm->player->move == 1)
			player_move_forward(prm->player);
		if (prm->player->move == -1)
			player_move_backward(prm->player);
		if (prm->player->turn == 1)
			player_turn_right(prm->player);
		if (prm->player->turn == -1)
			player_turn_left(prm->player);
	}
}
