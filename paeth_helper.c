/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paeth_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:53:41 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/29 13:05:49 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	int	paeth_predictor(int a, int b, int c)
{
	t_paeth	paeth;

	if (a == 0 && b == 0 && c == 0)
		return (0);
	paeth.p = a + b - c;
	paeth.pa = fabs((paeth.p - a) + 0.0);
	paeth.pb = fabs((paeth.p - b) + 0.0);
	paeth.pc = fabs((paeth.p - c) + 0.0);
	if (paeth.pa <= paeth.pb && paeth.pa <= paeth.pc)
		paeth.pr = a;
	else if (paeth.pb <= paeth.pc)
		paeth.pr = b;
	else
		paeth.pr = c;
	return (paeth.pr);
}

int	paeth_helper(t_paeth_helper *paeth)
{
	int				abc[3];
	int				xy[2];
	int				hex;
	int				index;
	unsigned int	*tex;

	xy[X] = paeth->xy[X];
	xy[Y] = paeth->xy[Y];
	hex = paeth->hex;
	index = paeth->index;
	tex = paeth->tex;
	ft_bzero(abc, sizeof(abc));
	if (xy[X] > 0)
		abc[0] = (tex[xy[Y] * TEX_HEIGHT + (xy[X] - 1)] & hex) >> index;
	if (xy[Y] > 0)
		abc[1] = (tex[(xy[Y] - 1) * TEX_HEIGHT + xy[X]] & hex) >> index;
	if (xy[X] > 0 && xy[Y] > 0)
		abc[2] = (tex[(xy[Y] - 1) * TEX_HEIGHT + (xy[X] - 1)] & hex) >> index;
	return (paeth_predictor(abc[0], abc[1], abc[2]));
}
