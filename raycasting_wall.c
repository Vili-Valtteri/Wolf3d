/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:18:23 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/26 14:51:06 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	void	compass_tex(t_rc_wall *wall)
{
	if (wall->side == 0 && wall->raydirxy[X] > 0)
		wall->texnum = 0;
	else if (wall->side == 0 && wall->raydirxy[X] < 0)
		wall->texnum = 1;
	else if (wall->side == 1 && wall->raydirxy[Y] > 0)
		wall->texnum = 2;
	else
		wall->texnum = 3;
}

static	void	setup_wall_texture(t_player *player, t_rc_wall *wall)
{
	wall->lineheight = (int)(SCREEN_HEIGHT / player->perpwalldist);
	wall->drawstart = -wall->lineheight / 2 + SCREEN_HEIGHT / 2;
	if (wall->drawstart < 0)
		wall->drawstart = 0;
	wall->drawend = wall->lineheight / 2 + SCREEN_HEIGHT / 2;
	if (wall->drawend >= SCREEN_HEIGHT)
		wall->drawend = SCREEN_HEIGHT - 1;
	wall->texnum = player->worldmap[wall->mapxy[X]][wall->mapxy[Y]] - 1;
	if (player->compass_tex == 1)
		compass_tex(wall);
	if (wall->side == 0)
		wall->wallx = player->posxy[Y] + player->perpwalldist \
		* wall->raydirxy[Y];
	else
		wall->wallx = player->posxy[X] + player->perpwalldist \
		* wall->raydirxy[X];
	wall->wallx -= floor((wall->wallx));
	wall->tex_xy[X] = ((int)(wall->wallx * ((double)(TEX_WIDTH))));
	if (wall->side == 0 && wall->raydirxy[X] > 0)
		wall->tex_xy[X] = TEX_WIDTH - wall->tex_xy[X] - 1;
	if (wall->side == 1 && wall->raydirxy[Y] < 0)
		wall->tex_xy[X] = TEX_WIDTH - wall->tex_xy[X] - 1;
}

void	raycasting_wall(t_prm *prm, int x)
{
	t_player	*player;
	t_rc_wall	wall;
	t_render	*render;

	render = prm->render;
	player = prm->player;
	set_ray_pos(player, &wall, x);
	step_direction(player, &wall);
	dda_algorithm(player, &wall);
	setup_wall_texture(player, &wall);
	wall.step = 1.0 * TEX_HEIGHT / wall.lineheight;
	wall.texpos = (wall.drawstart - SCREEN_HEIGHT / 2 + wall.lineheight / 2) \
	* wall.step;
	wall.y = wall.drawstart;
	while (wall.y < wall.drawend)
	{
		wall.tex_xy[Y] = (int)wall.texpos & (TEX_HEIGHT - 1);
		wall.texpos += wall.step;
		render->color = render->texture[wall.texnum][TEX_HEIGHT \
		* wall.tex_xy[Y] + wall.tex_xy[X]];
		if (wall.side == 1)
			render->color = (render->color >> 1) & 8355711;
		draw_pixel(x, wall.y, prm);
		wall.y++;
	}
}
