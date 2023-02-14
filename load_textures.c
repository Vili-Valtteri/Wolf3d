/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:46:06 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/29 14:21:33 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	load_wall_textures(t_render *render)
{
	load_tex(render, "pics/eagle.png", render->texture[0]);
	load_tex(render, "pics/redbrick.png", render->texture[1]);
	load_tex(render, "pics/purplestone.png", render->texture[2]);
	load_tex(render, "pics/greystone.png", render->texture[3]);
	load_tex(render, "pics/bluestone.png", render->texture[4]);
	load_tex(render, "pics/mossy.png", render->texture[5]);
	load_tex(render, "pics/wood.png", render->texture[6]);
	load_tex(render, "pics/colorstone.png", render->texture[7]);
}

void	load_sprite_textures(t_render *render)
{
	load_tex(render, "pics/barrel.png", render->texture[8]);
	load_tex(render, "pics/pillar.png", render->texture[9]);
	load_tex(render, "pics/greenlight.png", render->texture[10]);
	load_tex(render, "pics/screen_dead.png", render->texture[11]);
}

void	load_soldier_textures(t_render *render)
{
	unsigned	int	(*t)[17][4096];

	t = &render->tex_soldier;
	load_tex(render, "pics/soldier_anim/soldier_attack_1.png", (*t)[0]);
	load_tex(render, "pics/soldier_anim/soldier_attack_2.png", (*t)[1]);
	load_tex(render, "pics/soldier_anim/soldier_death_1.png", (*t)[2]);
	load_tex(render, "pics/soldier_anim/soldier_death_2.png", (*t)[3]);
	load_tex(render, "pics/soldier_anim/soldier_death_3.png", (*t)[4]);
	load_tex(render, "pics/soldier_anim/soldier_death_4.png", (*t)[5]);
	load_tex(render, "pics/soldier_anim/soldier_death_5.png", (*t)[6]);
	load_tex(render, "pics/soldier_anim/soldier_idle.png", (*t)[7]);
	load_tex(render, "pics/soldier_anim/soldier_run_1.png", (*t)[8]);
	load_tex(render, "pics/soldier_anim/soldier_run_2.png", (*t)[9]);
	load_tex(render, "pics/soldier_anim/soldier_run_3.png", (*t)[10]);
	load_tex(render, "pics/soldier_anim/soldier_run_4.png", (*t)[11]);
	load_tex(render, "pics/soldier_anim/soldier_death_1.png", (*t)[12]);
	load_tex(render, "pics/soldier_anim/soldier_death_2.png", (*t)[13]);
	load_tex(render, "pics/soldier_anim/soldier_death_3.png", (*t)[14]);
	load_tex(render, "pics/soldier_anim/soldier_death_4.png", (*t)[15]);
	load_tex(render, "pics/soldier_anim/soldier_death_5.png", (*t)[16]);
}

void	load_shotgun_textures(t_render *render)
{
	unsigned	int	(*t)[5][4096];

	t = &render->tex_shotgun;
	load_tex(render, "pics/shotgun_anim/shotgun1.png", (*t)[0]);
	load_tex(render, "pics/shotgun_anim/shotgun2.png", (*t)[1]);
	load_tex(render, "pics/shotgun_anim/shotgun3.png", (*t)[2]);
	load_tex(render, "pics/shotgun_anim/shotgun4.png", (*t)[3]);
	load_tex(render, "pics/shotgun_anim/shotgun5.png", (*t)[4]);
}
