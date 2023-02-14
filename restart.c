/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 00:29:17 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/27 14:19:59 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	void	draw_player_weapon(t_prm *prm)
{
	int			x;
	int			y;
	int			tex_pos;
	int			tex_nb;
	t_rc_wall	tex;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			tex.tex_xy[X] = TEX_WIDTH * (x / (SCREEN_WIDTH + 0.0));
			tex.tex_xy[Y] = TEX_HEIGHT * (y / (SCREEN_HEIGHT + 0.0));
			tex_nb = prm->player->shotgun_tex;
			tex_pos = TEX_HEIGHT * tex.tex_xy[Y] + tex.tex_xy[X];
			prm->render->color = prm->render->tex_shotgun[tex_nb][tex_pos];
			if (prm->render->color != prm->render->tex_shotgun[0][0])
				draw_pixel(x, y, prm);
			x++;
		}
		y++;
	}
}

void	player_weapon(t_prm *prm)
{
	if (prm->player->shotgun_tex > 0)
	{
		if (clock() >= prm->player->shotgun_anim + (CLOCKS_PER_SEC / 8))
		{
			prm->player->shotgun_tex++;
			if (prm->player->shotgun_tex == 5)
				prm->player->shotgun_tex = 0;
			prm->player->shotgun_anim = clock();
		}
	}
	draw_player_weapon(prm);
}

void	player_health_bar(t_prm *prm)
{
	int		x;
	int		y;
	double	x_range;

	y = SCREEN_HEIGHT - (SCREEN_HEIGHT / 20);
	while (y < SCREEN_HEIGHT)
	{
		x = SCREEN_WIDTH - (SCREEN_WIDTH / 4);
		while (x < SCREEN_WIDTH)
		{
			prm->render->color = INT_MAX;
			x_range = (x - (SCREEN_WIDTH - (SCREEN_WIDTH / 4))) / \
			(SCREEN_WIDTH / 4.0);
			if (x_range <= (prm->player->health / 100.0))
				prm->render->color = 16711680;
			draw_pixel(x, y, prm);
			x++;
		}
		y++;
	}
}

void	end_screen(t_prm *prm)
{
	int			x;
	int			y;
	int			tex_pos;
	t_rc_wall	tex;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			tex.tex_xy[X] = TEX_WIDTH * (x / (SCREEN_WIDTH + 0.0));
			tex.tex_xy[Y] = TEX_HEIGHT * (y / (SCREEN_HEIGHT + 0.0));
			tex_pos = TEX_HEIGHT * tex.tex_xy[Y] + tex.tex_xy[X];
			prm->render->color = prm->render->texture[11][tex_pos];
			draw_pixel(x, y, prm);
			x++;
		}
		y++;
	}
}

void	restart(t_prm *prm)
{
	prm->player->posxy[X] = 22.5;
	prm->player->posxy[Y] = 12.5;
	prm->player->dirxy[X] = -1;
	prm->player->dirxy[Y] = 0;
	prm->player->planexy[X] = 0;
	prm->player->planexy[Y] = 0.66;
	prm->player->health = 100;
	prm->ai_bot->posxy[X] = 20.5;
	prm->ai_bot->posxy[Y] = 22.5;
	prm->ai_bot->dirxy[X] = -1;
	prm->ai_bot->dirxy[Y] = 0;
	prm->ai_bot->health = 100;
	prm->ai_bot->mode = follow;
	prm->ai_bot->slowspeed = 2;
	prm->ai_bot->dirxy[X] = (prm->player->posxy[X] - prm->sprite[0].x);
	prm->ai_bot->dirxy[Y] = (prm->player->posxy[Y] - prm->sprite[0].y);
}
