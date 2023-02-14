/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:33:52 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/30 13:24:06 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	move_left_right(int key, t_prm *prm)
{
	t_player	*player;

	player = prm->player;
	if (key == KEY_RIGHT)
	{
		if (prm->file.map_xy[X] < MAP_WIDTH - 1)
			prm->file.map_xy[X]++;
	}
	else if (key == KEY_LEFT)
	{
		if (prm->file.map_xy[X] > 0)
			prm->file.map_xy[X]--;
	}
}

static void	move_up_down(int key, t_prm *prm)
{
	t_player	*player;

	player = prm->player;
	if (key == KEY_UP)
	{
		if (prm->file.map_xy[Y] > 0)
			prm->file.map_xy[Y]--;
	}
	else if (key == KEY_DOWN)
	{
		if (prm->file.map_xy[Y] < MAP_HEIGHT - 1)
			prm->file.map_xy[Y]++;
	}
}

static void	player_keys(int key, t_prm *prm)
{
	if (prm->gamemode == edit)
	{
		if (key == KEY_UP || key == KEY_DOWN)
			move_up_down(key, prm);
		else if (key == KEY_LEFT || key == KEY_RIGHT)
			move_left_right(key, prm);
	}
	else if (key == KEY_SPACE)
		player_shoot(prm);
	else if (key == KEY_Q)
	{
		if (prm->player->compass_tex == 1)
			prm->player->compass_tex = 0;
		else
			prm->player->compass_tex = 1;
	}
}

static void	edit_keys(int key, t_prm *prm)
{
	if (key == KEY_0)
		prm->player->worldmap[prm->file.map_xy[Y]][prm->file.map_xy[X]] = 0;
	else if (key == KEY_1)
		prm->player->worldmap[prm->file.map_xy[Y]][prm->file.map_xy[X]] = 1;
	else if (key == KEY_2)
		prm->player->worldmap[prm->file.map_xy[Y]][prm->file.map_xy[X]] = 2;
	else if (key == KEY_3)
		prm->player->worldmap[prm->file.map_xy[Y]][prm->file.map_xy[X]] = 3;
	else if (key == KEY_4)
		prm->player->worldmap[prm->file.map_xy[Y]][prm->file.map_xy[X]] = 4;
	else if (key == KEY_5)
		prm->player->worldmap[prm->file.map_xy[Y]][prm->file.map_xy[X]] = 5;
	else if (key == KEY_6)
		prm->player->worldmap[prm->file.map_xy[Y]][prm->file.map_xy[X]] = 6;
	else if (key == KEY_7)
		prm->player->worldmap[prm->file.map_xy[Y]][prm->file.map_xy[X]] = 7;
	else if (key == KEY_8)
		prm->player->worldmap[prm->file.map_xy[Y]][prm->file.map_xy[X]] = 8;
	else if (key == KEY_9)
		prm->player->worldmap[prm->file.map_xy[Y]][prm->file.map_xy[X]] = 9;
}

int	keyboard_input(int key, void *ptr)
{
	t_prm		*prm;

	prm = ((t_prm *) ptr);
	if (key == KEY_ESC)
		exit_program(prm, 0, NULL);
	else if (key == KEY_R)
		restart(prm);
	else if (key == KEY_ENTER)
	{
		if (prm->gamemode == play)
			prm->gamemode = edit;
		else
		{
			check_map(prm);
			prm->gamemode = play;
		}
	}
	else
	{
		player_keys(key, prm);
		if (prm->gamemode == edit)
			edit_keys(key, prm);
	}
	return (0);
}
