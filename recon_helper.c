/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recon_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:14:13 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/29 12:59:11 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	rgb_to_int(uint8_t Red, uint8_t Green, uint8_t Blue)
{
	return ((Red << 16) + (Green << 8) + (Blue));
}

void	render_color(uint8_t *prev_color, t_render *render, int pos)
{
	uint8_t	rgb[3];

	rgb[0] = render->pngtex[pos + 0] + prev_color[0];
	rgb[1] = render->pngtex[pos + 1] + prev_color[1];
	rgb[2] = render->pngtex[pos + 2] + prev_color[2];
	render->color = rgb_to_int(rgb[0], rgb[1], rgb[2]);
}

void	call_recon_func_type(t_recon_helper *recon_helper)
{
	int				type;
	static void		(*recon_func[5])(t_recon_helper *) = \
	{
		reconstruction_type_zero,
		reconstruction_type_one,
		reconstruction_type_two,
		reconstruction_type_three,
		reconstruction_type_four
	};

	type = recon_helper->type;
	(*recon_func[type])(recon_helper);
}
