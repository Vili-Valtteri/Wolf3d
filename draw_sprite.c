/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:20:03 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/30 13:29:58 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	sprite_pixel(t_draw_sprite *spr, t_prm *prm, int y, int i)
{
	t_render	*render;

	render = prm->render;
	spr->d = y * 256 - SCREEN_HEIGHT * 128 + spr->spriteheight * 128;
	spr->tex_xy[Y] = ((spr->d * TEX_HEIGHT) / spr->spriteheight) / 256;
	render->color = render->texture[prm->sprite[spr->spriteorder \
	[i]].texture][TEX_WIDTH * spr->tex_xy[Y] + spr->tex_xy[X]];
	render->color = get_color_from_tex(prm, spr, i);
	if (render->color != prm->sprite \
	[spr->spriteorder[i]].ignore_color)
		draw_pixel(spr->stripe, y, prm);
}

void	static	draw_sprite(t_draw_sprite *spr, t_prm *prm, int i)
{
	t_player		*player;
	t_render		*render;
	int				y;

	player = prm->player;
	render = prm->render;
	spr->stripe = spr->drawstartend_xy[0];
	while (spr->stripe < spr->drawstartend_xy[1])
	{
		spr->tex_xy[X] = (int)(256 * (spr->stripe - (-spr->spritewidth / \
		2 + spr->spritescreenx)) * TEX_WIDTH / spr->spritewidth) / 256;
		if (spr->transformxy[Y] > 0 && spr->stripe > 0 && spr->stripe < \
		SCREEN_WIDTH && spr->transformxy[Y] < render->zbuffer[spr->stripe])
		{
			y = spr->drawstartend_xy[2];
			while (y < spr->drawstartend_xy[3])
			{
				sprite_pixel(spr, prm, y, i);
				y++;
			}
		}
	spr->stripe++;
	}
}

void	draw_sprites(t_prm *prm)
{
	t_player		*player;
	t_draw_sprite	spr;
	int				i;

	player = prm->player;
	sortsprites(&spr, prm);
	i = 0;
	while (i < NUM_SPRITES)
	{
		set_sprite_pos(&spr, prm, i);
		sprite_width_height(&spr);
		draw_sprite(&spr, prm, i);
		i++;
	}
}
