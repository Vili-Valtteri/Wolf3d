/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 23:41:10 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/29 14:22:36 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	default_settings(t_prm *prm)
{
	restart(prm);
	get_textures(prm->render);
}

static void	set_sprites(t_prm *prm)
{
	t_sprite	*sprite;

	sprite = prm->sprite;
	sprite[0] = (t_sprite){20.5, 22.5, 10, 0, 0};
	sprite[1] = (t_sprite){18.5, 4.5, 10, 0, 0};
	sprite[2] = (t_sprite){10.0, 4.5, 10, 0, 0};
	sprite[3] = (t_sprite){10.0, 12.5, 10, 0, 0};
	sprite[4] = (t_sprite){3.5, 6.5, 10, 0, 0};
	sprite[5] = (t_sprite){3.5, 20.5, 10, 0, 0};
	sprite[6] = (t_sprite){3.5, 14.5, 10, 0, 0};
	sprite[7] = (t_sprite){14.5, 20.5, 10, 0, 0};
	sprite[8] = (t_sprite){18.5, 10.5, 9, 0, 0};
	sprite[9] = (t_sprite){18.5, 11.5, 9, 0, 0};
	sprite[10] = (t_sprite){18.5, 12.5, 9, 0, 0};
	sprite[11] = (t_sprite){21.5, 1.5, 8, 0, 0};
	sprite[12] = (t_sprite){15.5, 1.5, 8, 0, 0};
	sprite[13] = (t_sprite){16.0, 1.8, 8, 0, 0};
	sprite[14] = (t_sprite){16.2, 1.2, 8, 0, 0};
	sprite[15] = (t_sprite){3.5, 2.5, 8, 0, 0};
	sprite[16] = (t_sprite){9.5, 15.5, 8, 0, 0};
	sprite[17] = (t_sprite){10.0, 15.1, 8, 0, 0};
	sprite[18] = (t_sprite){10.5, 15.8, 8, 0, 0};
	sprite[19] = (t_sprite){19.5, 13.5, 8, 0, 0};
	sprite[20] = (t_sprite){20.5, 22.5, 0, soldier, 9961608};
}

int	main(int argc, char **argv)
{
	t_prm		prm;
	t_mlx		mlx;
	t_player	player;
	t_ai_bot	ai_bot;
	t_render	render;

	if (argc != 2)
		exit_program(NULL, 1, "usage ./wolf3d map_filename");
	ft_bzero(&prm, sizeof(t_prm));
	ft_bzero(&mlx, sizeof(t_mlx));
	ft_bzero(&player, sizeof(t_player));
	ft_bzero(&ai_bot, sizeof(t_ai_bot));
	prm.render = &render;
	prm.player = &player;
	prm.ai_bot = &ai_bot;
	prm.mlx = &mlx;
	prm.filename = argv[1];
	prm.gamemode = edit;
	set_sprites(&prm);
	default_settings(&prm);
	create_window(&prm);
	return (0);
}
