/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 23:53:41 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/27 14:33:09 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	void	draw_player_on_map(t_prm *prm, int x, int y)
{
	int	end_x;
	int	start_x;
	int	end_y;

	x -= 5;
	y -= 5;
	end_x = x + 10;
	end_y = y + 10;
	start_x = x;
	while (y < end_y)
	{
		x = start_x;
		while (x < end_x)
		{
			draw_pixel(y, x, prm);
			x++;
		}
		y++;
	}
}

static	void	get_player_pos_on_map(t_prm *prm)
{
	int	x;
	int	y;

	x = prm->player->posxy[X] * (MINIMAP_SIZE / (MAP_HEIGHT - 1));
	y = prm->player->posxy[Y] * (MINIMAP_SIZE / (MAP_HEIGHT - 1));
	prm->render->color = 16776960;
	draw_player_on_map(prm, x, y);
	x = prm->ai_bot->posxy[X] * (MINIMAP_SIZE / (MAP_HEIGHT - 1));
	y = prm->ai_bot->posxy[Y] * (MINIMAP_SIZE / (MAP_HEIGHT - 1));
	prm->render->color = 16711680;
	draw_player_on_map(prm, x, y);
}

static	void	get_color_from_map(t_prm *prm, t_rc_wall *map, int x, int y)
{
	prm->render->color = 0;
	map->mapxy[X] = x / (MINIMAP_SIZE / MAP_HEIGHT);
	map->mapxy[Y] = y / (MINIMAP_SIZE / MAP_HEIGHT);
	map->texnum = prm->player->worldmap[map->mapxy[Y]][map->mapxy[X]] - 1;
	if (map->texnum >= 0)
		prm->render->color = 65280;
}

static	void	minimapvision(t_prm *prm, int x, int y)
{
	int	map_xy[2];

	map_xy[X] = x / (MINIMAP_SIZE / 24);
	map_xy[Y] = y / (MINIMAP_SIZE / 24);
	if (prm->player->save[map_xy[Y]][map_xy[X]] == 1)
		prm->render->color = 3093247;
}

void	draw_minimap(t_prm *prm)
{
	int			x;
	int			y;
	int			grid;
	t_rc_wall	map;
	t_mlx		*mlx;

	mlx = prm->mlx;
	grid = MINIMAP_SIZE / MAP_HEIGHT;
	y = 0;
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			get_color_from_map(prm, &map, x, y);
			if (x % (grid) == 0 || y % (grid) == 0)
				prm->render->color = INT_MAX;
			else if (x + 1 == MINIMAP_SIZE || y + 1 == MINIMAP_SIZE)
				prm->render->color = INT_MAX;
			minimapvision(prm, x, y);
			draw_pixel(x++, y, prm);
		}
		y++;
	}
	get_player_pos_on_map(prm);
}
