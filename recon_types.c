/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recon_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 23:49:11 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/27 13:25:23 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	reconstruction_type_four(t_recon_helper *recon_helper)
{
	uint8_t			*prev_color;
	t_paeth_helper	paeth;

	prev_color = recon_helper->prev_color;
	paeth.xy[X] = recon_helper->recon->x;
	paeth.xy[Y] = recon_helper->recon->y;
	paeth.render = recon_helper->recon->render;
	paeth.tex = recon_helper->tex;
	paeth.index = 16;
	paeth.hex = 0xff0000;
	prev_color[0] = paeth_helper(&paeth);
	paeth.index = 8;
	paeth.hex = 0x00ff00;
	prev_color[1] = paeth_helper(&paeth);
	paeth.index = 0;
	paeth.hex = 0x0000ff;
	prev_color[2] = paeth_helper(&paeth);
}

void	reconstruction_type_three(t_recon_helper *recon_helper)
{
	int				floorx[3];
	t_render		*render;
	unsigned int	*tex;
	int				xy[2];
	uint8_t			*prev_color;

	render = recon_helper->recon->render;
	xy[Y] = recon_helper->recon->y;
	xy[X] = recon_helper->recon->x;
	tex = recon_helper->tex;
	prev_color = recon_helper->prev_color;
	ft_bzero(&floorx, sizeof(floorx));
	if (xy[X] > 0)
	{
		floorx[0] = (tex[xy[Y] * TEX_HEIGHT + (xy[X] - 1)] & 0xff0000) >> 16;
		floorx[1] = (tex[xy[Y] * TEX_HEIGHT + (xy[X] - 1)] & 0x00ff00) >> 8;
		floorx[2] = (tex[xy[Y] * TEX_HEIGHT + (xy[X] - 1)] & 0x0000ff) >> 0;
	}
	prev_color[0] = (floorx[0] + ((tex[(xy[Y] - 1) * TEX_HEIGHT + xy[X]] \
	& 0xff0000) >> 16)) / 2;
	prev_color[1] = (floorx[1] + ((tex[(xy[Y] - 1) * TEX_HEIGHT + xy[X]] \
	& 0x00ff00) >> 8)) / 2;
	prev_color[2] = (floorx[2] + ((tex[(xy[Y] - 1) * TEX_HEIGHT + xy[X]] \
	& 0x0000ff) >> 0)) / 2;
}

void	reconstruction_type_two(t_recon_helper *recon_helper)
{
	t_render		*render;
	unsigned int	*tex;
	uint8_t			*prev_color;
	int				xy[2];

	render = recon_helper->recon->render;
	xy[Y] = recon_helper->recon->y;
	xy[X] = recon_helper->recon->x;
	prev_color = recon_helper->prev_color;
	tex = recon_helper->tex;
	prev_color[0] = (tex[(xy[Y] - 1) * TEX_HEIGHT + xy[X]] & 0xff0000) >> 16;
	prev_color[1] = (tex[(xy[Y] - 1) * TEX_HEIGHT + xy[X]] & 0x00ff00) >> 8;
	prev_color[2] = (tex[(xy[Y] - 1) * TEX_HEIGHT + xy[X]] & 0x0000ff) >> 0;
}

void	reconstruction_type_one(t_recon_helper *recon_helper)
{
	t_render		*render;
	unsigned int	*tex;
	uint8_t			*prev_color;
	int				xy[2];
	int				tex_h;

	render = recon_helper->recon->render;
	xy[Y] = recon_helper->recon->y;
	xy[X] = recon_helper->recon->x;
	prev_color = recon_helper->prev_color;
	tex = recon_helper->tex;
	tex_h = TEX_HEIGHT;
	if (xy[X] != 0)
	{
		prev_color[0] = (tex[xy[Y] * tex_h + (xy[X] - 1)] & 0xff0000) >> 16;
		prev_color[1] = (tex[xy[Y] * tex_h + (xy[X] - 1)] & 0x00ff00) >> 8;
		prev_color[2] = (tex[xy[Y] * tex_h + (xy[X] - 1)] & 0x0000ff) >> 0;
	}
}

void	reconstruction_type_zero(t_recon_helper *recon_helper)
{
	t_render		*render;
	uint8_t			*prev_color;
	int				pos;

	render = recon_helper->recon->render;
	prev_color = recon_helper->prev_color;
	pos = recon_helper->recon->pos;
	prev_color[0] = render->pngtex[pos];
	prev_color[1] = render->pngtex[pos + 1];
	prev_color[2] = render->pngtex[pos + 2];
}
