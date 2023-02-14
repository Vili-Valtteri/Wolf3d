/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:20:11 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/27 15:30:53 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	step_draw(t_cast_floor *floor, t_prm *prm)
{
	t_render	*render;

	render = prm->render;
	floor->cellxy[X] = (int)(floor->floorxy[X]);
	floor->cellxy[Y] = (int)(floor->floorxy[Y]);
	floor->tex_xy[X] = (int)(TEX_WIDTH * \
	(floor->floorxy[X] - floor->cellxy[X])) & (TEX_WIDTH - 1);
	floor->tex_xy[Y] = (int)(TEX_HEIGHT * \
	(floor->floorxy[Y] - floor->cellxy[Y])) & (TEX_HEIGHT - 1);
	floor->floorxy[X] += floor->floorstepxy[X];
	floor->floorxy[Y] += floor->floorstepxy[Y];
	floor->floortex = 3;
	floor->ceilingtex = 6;
	render->color = render->texture[floor->floortex] \
	[TEX_WIDTH * floor->tex_xy[Y] + floor->tex_xy[X]];
	render->color = (render->color >> 1) & 8355711;
	draw_pixel(floor->xy[X], floor->xy[Y], prm);
	render->color = render->texture[floor->ceilingtex] \
	[TEX_WIDTH * floor->tex_xy[Y] + floor->tex_xy[X]];
	render->color = (render->color >> 1) & 8355711;
	draw_pixel(floor->xy[X], SCREEN_HEIGHT - floor->xy[Y] - 1, prm);
}

static void	calc_step_rowdist(t_cast_floor *floor, t_player *player)
{
	floor->raydirxy0[X] = player->dirxy[X] - player->planexy[X];
	floor->raydirxy0[Y] = player->dirxy[Y] - player->planexy[Y];
	floor->raydirxy1[X] = player->dirxy[X] + player->planexy[X];
	floor->raydirxy1[Y] = player->dirxy[Y] + player->planexy[Y];
	floor->p = floor->xy[Y] - SCREEN_HEIGHT / 2;
	floor->posz = 0.5 * SCREEN_HEIGHT;
	floor->rowdistance = floor->posz / floor->p;
	floor->floorstepxy[X] = floor->rowdistance * \
	(floor->raydirxy1[X] - floor->raydirxy0[X]) / SCREEN_WIDTH;
	floor->floorstepxy[Y] = floor->rowdistance * \
	(floor->raydirxy1[Y] - floor->raydirxy0[Y]) / SCREEN_WIDTH;
	floor->floorxy[X] = player->posxy[X] + floor->rowdistance \
	* floor->raydirxy0[X];
	floor->floorxy[Y] = player->posxy[Y] + floor->rowdistance \
	* floor->raydirxy0[Y];
}

void	casting_floor(t_prm *prm)
{
	t_player		*player;
	t_render		*render;
	t_cast_floor	floor;

	player = prm->player;
	render = prm->render;
	floor.xy[Y] = 0;
	while (floor.xy[Y] < SCREEN_HEIGHT)
	{
		calc_step_rowdist(&floor, player);
		floor.xy[X] = 0;
		while (floor.xy[X] < SCREEN_WIDTH)
		{
			step_draw(&floor, prm);
			floor.xy[X]++;
		}
		floor.xy[Y]++;
	}
}
