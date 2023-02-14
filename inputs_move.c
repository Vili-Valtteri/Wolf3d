/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:48:48 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/29 12:17:47 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	input_key_down(int key, void *ptr)
{
	t_prm	*prm;

	prm = (t_prm *)ptr;
	if (prm->gamemode == play)
	{
		if (key == KEY_UP)
			prm->player->move = 1;
		else if (key == KEY_DOWN)
			prm->player->move = -1;
		else if (key == KEY_RIGHT)
			prm->player->turn = 1;
		else if (key == KEY_LEFT)
			prm->player->turn = -1;
	}
	keyboard_input(key, ptr);
	return (0);
}

int	input_key_up(int key, void *ptr)
{
	t_prm	*prm;

	prm = (t_prm *)ptr;
	if (prm->gamemode == play)
	{
		if (key == KEY_UP || key == KEY_DOWN)
			prm->player->move = 0;
		else if (key == KEY_RIGHT || key == KEY_LEFT)
			prm->player->turn = 0;
	}
	return (0);
}
