/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 00:49:46 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/29 12:28:23 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	write_map_to_file(t_prm *prm)
{
	int	x;
	int	y;

	y = 0;
	prm->file.fd = open(prm->filename, O_WRONLY);
	if (prm->file.fd == -1)
		exit_program(NULL, 1, "file error");
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			ft_putnbr_fd(prm->player->worldmap[y][x], prm->file.fd);
			ft_putchar_fd(' ', prm->file.fd);
			x++;
		}
		ft_putchar_fd('\n', prm->file.fd);
		y++;
	}
	close(prm->file.fd);
}

void	free_pathfind_lst(t_pathfind *lst)
{
	t_pathfind	*temp;

	while (lst)
	{
		temp = lst;
		lst = lst->next;
		free(temp);
		temp = NULL;
	}
	lst = NULL;
}

void	exit_program(t_prm *prm, int is_error, char *error_msg)
{
	if (is_error == 1)
		ft_putendl_fd(error_msg, 2);
	else if (prm)
		write_map_to_file(prm);
	exit(0);
}

int	on_red_cross_exit(int key, void *ptr)
{
	t_prm	*prm;

	prm = (t_prm *)ptr;
	exit(0);
	key += 0;
	return (0);
}
