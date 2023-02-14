/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 23:52:39 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/29 14:21:45 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	is_idat_chunk(uint8_t *prev_color, t_render *render, t_recon *recon)
{
	uint8_t	*temp_buff;

	temp_buff = render->pngtex;
	ft_bzero(prev_color, 3);
	if (temp_buff[recon->pos] == 'D' && temp_buff[recon->pos + 1] == 'A')
	{
		if (temp_buff[recon->pos + 2] == 'T')
		{
			if (recon->x >= 3)
				recon->x -= 3;
			else
			{
				recon->x = 63 - 3 - recon->x;
				recon->y -= 1;
			}
			recon->pos += 3;
		}
	}
}

static	void	get_pixel_color(t_recon_helper *recon_helper, t_render *render)
{
	t_recon			*recon;
	uint8_t			*prev_color;
	int				type;
	unsigned int	*texture;

	recon = recon_helper->recon;
	prev_color = recon_helper->prev_color;
	type = recon_helper->type;
	texture = recon_helper->tex;
	is_idat_chunk(prev_color, render, recon);
	call_recon_func_type(recon_helper);
	render_color(prev_color, render, recon->pos);
	texture[recon->y * TEX_HEIGHT + recon->x] = render->color;
	recon->pos += 3;
	recon->x++;
}

static	void	parse_file(t_render *render, unsigned int *tex)
{
	int				type;
	uint8_t			prev_color[3];
	t_recon			recon;
	t_recon_helper	recon_helper;

	recon.render = render;
	recon.pos = 49;
	recon.y = 0;
	type = render->pngtex[recon.pos - 1];
	while (recon.y < TEX_HEIGHT)
	{
		recon.x = 0;
		while (recon.x < TEX_WIDTH)
		{
			recon_helper.type = type;
			recon_helper.prev_color = prev_color;
			recon_helper.tex = tex;
			recon_helper.recon = &recon;
			get_pixel_color(&recon_helper, render);
		}
		type = render->pngtex[recon.pos];
		recon.pos++;
		recon.y++;
	}
}

void	load_tex(t_render *render, char *filename, unsigned int *tex)
{
	int	fd;
	int	size;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_program(NULL, 1, "texture error");
	size = read(fd, render->pngtex, TEX_HEIGHT * TEX_WIDTH * 16);
	parse_file(render, tex);
	close(fd);
}

void	get_textures(t_render *render)
{
	load_wall_textures(render);
	load_sprite_textures(render);
	load_soldier_textures(render);
	load_shotgun_textures(render);
}
