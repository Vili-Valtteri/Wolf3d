/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:21:02 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/29 14:22:05 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	void	tick_every_frame(t_prm *prm)
{
	t_player	*player;

	player = prm->player;
	ai_bot_controller(prm);
	player_controller(prm);
	player->currentframe++;
	if (player->currentframe == 61)
		player->currentframe = 0;
}

static	void	raycast(t_prm *prm)
{
	t_player	*player;
	t_render	*render;
	int			x;

	player = prm->player;
	render = prm->render;
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		raycasting_wall(prm, x);
		render->zbuffer[x] = player->perpwalldist;
		x++;
	}
	draw_sprites(prm);
	tick_every_frame(prm);
	draw_minimap(prm);
	player->delta_time = clock() - player->oldtime;
	player->delta_time /= 1000000.0;
	if (player->delta_time < 1 / 60.0)
		player->delta_time = 1 / 60.0;
	player->movespeed = 3 * player->delta_time;
	player->rotspeed = 2.5 * player->delta_time;
}

void	wolf3d(t_prm *prm)
{
	t_player	*player;
	int			t1;
	int			t2;
	int			x;

	player = prm->player;
	player->oldtime = clock();
	casting_floor(prm);
	x = 0;
	t1 = 0;
	t2 = 0;
	while (t1 < MAP_HEIGHT)
	{
		t2 = 0;
		while (t2 < MAP_HEIGHT)
		{
			player->save[t1][t2] = 0;
			t2++;
		}
		t1++;
	}
	raycast(prm);
}
