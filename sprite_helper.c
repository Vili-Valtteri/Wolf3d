/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:43:35 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/29 14:24:11 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	void	sort(int i, t_draw_sprite *spr)
{
	double	tempdist;
	int		j;
	int		temporder;

	tempdist = spr->spritedistance[i];
	temporder = spr->spriteorder[i];
	j = i - 1;
	while (j >= 0 && spr->spritedistance[j] < tempdist)
	{
		spr->spritedistance[j + 1] = spr->spritedistance[j];
		spr->spriteorder[j + 1] = spr->spriteorder[j];
		j = j - 1;
	}
	spr->spriteorder[j + 1] = temporder;
	spr->spritedistance[j + 1] = tempdist;
	i++;
}

void	sortsprites(t_draw_sprite *spr, t_prm *prm)
{
	int			i;
	double		dist_xy[2];
	t_player	*player;

	player = prm->player;
	i = 0;
	while (i < NUM_SPRITES)
	{
		spr->spriteorder[i] = i;
		dist_xy[X] = player->posxy[X] - prm->sprite[i].x;
		dist_xy[Y] = player->posxy[Y] - prm->sprite[i].y;
		spr->spritedistance[i] = pow(dist_xy[X], 2) + pow(dist_xy[Y], 2);
		i++;
	}
	i = 1;
	while (i < NUM_SPRITES)
	{
		sort(i, spr);
		i++;
	}
}

void	set_sprite_pos(t_draw_sprite *spr, t_prm *prm, int i)
{
	t_player	*player;

	player = prm->player;
	spr->spritexy[X] = prm->sprite[spr->spriteorder[i]].x - player->posxy[X];
	spr->spritexy[Y] = prm->sprite[spr->spriteorder[i]].y - player->posxy[Y];
	spr->invdet = 1.0 / (player->planexy[X] * player->dirxy[Y] - \
	player->dirxy[X] * player->planexy[Y]);
	spr->transformxy[X] = spr->invdet * (player->dirxy[Y] * \
	spr->spritexy[X] - player->dirxy[X] * spr->spritexy[Y]);
	spr->transformxy[Y] = spr->invdet * (-player->planexy[Y] * \
	spr->spritexy[X] + player->planexy[X] * spr->spritexy[Y]);
	spr->spritescreenx = (int)((SCREEN_WIDTH / 2) * \
	(1 + spr->transformxy[X] / spr->transformxy[Y]));
}

void	sprite_width_height(t_draw_sprite *spr)
{
	spr->spriteheight = fabs(SCREEN_HEIGHT / (spr->transformxy[Y]));
	spr->drawstartend_xy[2] = -spr->spriteheight / 2 + SCREEN_HEIGHT / 2;
	if (spr->drawstartend_xy[2] < 0)
	spr->drawstartend_xy[2] = 0;
	spr->drawstartend_xy[3] = spr->spriteheight / 2 + SCREEN_HEIGHT / 2;
	if (spr->drawstartend_xy[3] >= SCREEN_HEIGHT)
	spr->drawstartend_xy[3] = SCREEN_HEIGHT - 1;
	spr->spritewidth = fabs(SCREEN_HEIGHT / (spr->transformxy[Y]));
	spr->drawstartend_xy[0] = -spr->spritewidth / 2 + spr->spritescreenx;
	if (spr->drawstartend_xy[0] < 0)
	spr->drawstartend_xy[0] = 0;
	spr->drawstartend_xy[1] = spr->spritewidth / 2 + spr->spritescreenx;
	if (spr->drawstartend_xy[1] >= SCREEN_WIDTH)
	spr->drawstartend_xy[1] = SCREEN_WIDTH - 1;
}

unsigned int	get_color_from_tex(t_prm *prm, t_draw_sprite *spr, int i)
{
	t_render	*render;
	int			sprite_texture;

	render = prm->render;
	sprite_texture = prm->sprite[spr->spriteorder[i]].texture;
	if (prm->sprite[spr->spriteorder[i]].sprite_type == soldier)
		return (render->tex_soldier[sprite_texture] \
		[TEX_WIDTH * spr->tex_xy[Y] + spr->tex_xy[X]]);
	else
		return (render->texture[sprite_texture] \
		[TEX_WIDTH * spr->tex_xy[Y] + spr->tex_xy[X]]);
}
