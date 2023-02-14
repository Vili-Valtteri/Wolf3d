/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 03:38:38 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/30 13:23:30 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	draw_texture(t_prm *prm, int x, int y)
{
	int	temp_xy[2];
	int	texnum;
	int	map_xy[2];
	int	tex_pos;

	temp_xy[X] = x % (SCREEN_WIDTH / MAP_WIDTH);
	temp_xy[Y] = y % (SCREEN_HEIGHT / MAP_HEIGHT);
	temp_xy[X] = temp_xy[X] * (TEX_WIDTH / (SCREEN_WIDTH / MAP_WIDTH));
	temp_xy[Y] = temp_xy[Y] * (TEX_HEIGHT / (SCREEN_HEIGHT / MAP_HEIGHT));
	map_xy[X] = ((x + 0.0) / SCREEN_WIDTH) * MAP_WIDTH;
	map_xy[Y] = ((y + 0.0) / SCREEN_HEIGHT) * MAP_HEIGHT;
	texnum = prm->player->worldmap[map_xy[Y]][map_xy[X]] - 1;
	tex_pos = TEX_HEIGHT * temp_xy[Y] + temp_xy[X];
	prm->render->color = prm->render->texture[texnum][tex_pos];
	if (texnum == -1)
		prm->render->color = 0;
	draw_pixel(x, y, prm);
}

static void	draw_block_hovered(t_prm *prm)
{
	int	x;
	int	y;
	int	temp_xy[2];

	y = prm->file.map_xy[Y] * (SCREEN_HEIGHT / (MAP_HEIGHT));
	x = prm->file.map_xy[X] * (SCREEN_WIDTH / (MAP_WIDTH));
	temp_xy[Y] = y + SCREEN_HEIGHT / MAP_HEIGHT;
	temp_xy[X] = x + SCREEN_WIDTH / MAP_WIDTH;
	while (y < temp_xy[Y])
	{
		x = prm->file.map_xy[X] * (SCREEN_WIDTH / (MAP_WIDTH));
		while (x < temp_xy[X])
		{
			prm->render->color = 65280;
			draw_pixel(x, y, prm);
			x++;
		}
		y++;
	}
}

static	void	draw_map(t_prm *prm)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			if (x % (SCREEN_WIDTH / 24) == 0 || y % (SCREEN_HEIGHT / 24) == 0)
			{
				prm->render->color = INT_MAX;
				draw_pixel(x, y, prm);
			}
			else
				draw_texture(prm, x, y);
			x++;
		}
		y++;
	}
}

void	check_map(t_prm *prm)
{
	int	x;
	int	y;
	int	texnum;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			texnum = prm->player->worldmap[y][x];
			if (texnum < 1 || texnum > 9)
				if (x == 0 || x == 23 || y == 0 || y == 23)
					prm->player->worldmap[y][x] = 2;
			x++;
		}
		y++;
	}
}

void	edit_map(t_prm *prm)
{
	if (prm->file.has_read_file == 0)
	{
		prm->file.has_read_file = 1;
		open_file(prm);
		restart(prm);
	}
	check_map(prm);
	draw_map(prm);
	draw_block_hovered(prm);
}
