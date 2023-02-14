/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:05:43 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/30 13:34:03 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	is_valid_spacing(int x, t_file *file)
{
	if (x > 0)
	{
		file->error = -1;
		if (ft_isdigit(file->buffer[x - 1]) && file->buffer[x] == 32)
			file->error = 0;
		if (file->buffer[x - 1] == 32 && ft_isdigit(file->buffer[x]))
			file->error = 0;
	}
	else if (ft_isdigit(file->buffer[0]) == 0)
		file->error = -1;
}

static int	read_gnl(t_prm *prm, int y)
{
	int		x;
	int		x1;
	t_file	*file;

	file = &prm->file;
	x = 0;
	x1 = 0;
	file->gnl = get_next_line(file->fd, &file->buffer);
	while (file->buffer[x] && file->gnl > 0 && file->error != -1)
	{
		if (ft_isdigit(file->buffer[x]))
			prm->player->worldmap[y][x1++] = ft_atoi(&file->buffer[x]);
		is_valid_spacing(x, file);
		x++;
	}
	if (file->buffer)
		free(file->buffer);
	if (file->error == -1)
		exit_program(prm, 1, "file map wrong");
	return (x1);
}

static void	file_parser(t_prm *prm)
{
	int		xy[2];
	t_file	*file;

	file = &prm->file;
	xy[Y] = 0;
	while (xy[Y] < MAP_HEIGHT)
	{
		xy[X] = read_gnl(prm, xy[Y]);
		while (xy[X] < MAP_WIDTH)
			prm->player->worldmap[xy[Y]][xy[X]++] = 0;
		xy[Y]++;
	}
}

void	open_file(t_prm *prm)
{
	t_file	*file;

	file = &prm->file;
	file->fd = open(prm->filename, O_RDONLY);
	if (file->fd == -1)
		exit_program(prm, 1, "error open file");
	file_parser(prm);
	close(file->fd);
}
