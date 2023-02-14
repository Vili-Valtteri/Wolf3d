/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:18:20 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/29 12:38:13 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	dest_itoa(char *dest, int n)
{
	size_t		digits;
	size_t		nbr;

	digits = 1;
	nbr = n;
	while (n > 9)
	{
		n = n / 10;
		digits++;
	}
	dest[digits] = '\0';
	while (digits > 0)
	{
		dest[digits - 1] = (nbr % 10) + '0';
		nbr = nbr / 10;
		digits--;
	}
	ft_strcat(dest, " FPS");
}

static int	window_loop(void *ptr)
{
	t_prm	*prm;
	t_mlx	*mlx;

	prm = ((t_prm *) ptr);
	mlx = prm->mlx;
	ft_bzero(prm->mlx->image_add, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(int));
	if (prm->gamemode == edit)
	{
		edit_map(prm);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
		mlx->image_ptr, 0, 0);
	}
	else if (prm->gamemode == play)
	{
		wolf3d(prm);
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
		mlx->image_ptr, 0, 0);
		dest_itoa(prm->player->onscreen_fps, 1.0
			/ prm->player->delta_time);
		mlx_string_put(prm->mlx->mlx_ptr, prm->mlx->win_ptr, \
		SCREEN_WIDTH - 50, 15, INT_MAX, prm->player->onscreen_fps);
	}
	mlx_do_sync(mlx->mlx_ptr);
	return (0);
}

void	draw_pixel(int x, int y, t_prm *prm)
{
	int	image_pos;

	if (y > SCREEN_HEIGHT || y < 0)
		return ;
	if (x > SCREEN_WIDTH || x < 0)
		return ;
	image_pos = (prm->mlx->size_line / 4) * y + x;
	((unsigned int *)prm->mlx->image_add)[image_pos] = prm->render->color;
}

void	create_window(t_prm *prm)
{
	t_mlx	*mlx;

	mlx = prm->mlx;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = \
	mlx_new_window(mlx->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "win");
	mlx->image_ptr = mlx_new_image(mlx->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx->image_add = \
	mlx_get_data_addr(mlx->image_ptr, &mlx->bpp, &mlx->size_line, &mlx->erdian);
	mlx_loop_hook(mlx->mlx_ptr, window_loop, prm);
	mlx_key_hook(mlx->win_ptr, keyboard_input, prm);
	mlx_hook(mlx->win_ptr, 2, 2, input_key_down, prm);
	mlx_hook(mlx->win_ptr, 3, 3, input_key_up, prm);
	mlx_hook(mlx->win_ptr, 17, 0, on_red_cross_exit, prm);
	mlx_loop(mlx->mlx_ptr);
}
