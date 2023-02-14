/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_neighbors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:47:05 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/27 15:18:11 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	pos_is_valid(int x_offset, int y_offset, t_player *player)
{
	if (x_offset > 23 || x_offset < 0)
		return (0);
	if (y_offset > 23 || y_offset < 0)
		return (0);
	if (player->worldmap[x_offset][y_offset] > 0)
		return (0);
	return (1);
}

static void	set_node_vector(t_pathfind *node, int x_offset, int y_offset)
{
	node->vector[X] = x_offset;
	node->vector[Y] = y_offset;
	node->next = NULL;
	node->parent = NULL;
	node->neighbor = NULL;
}

static t_pathfind	*malloc_neighbor(t_pathfind **src, t_pathfind **head)
{
	if (!*src)
	{
		*src = malloc(sizeof(t_pathfind));
		if (!*src)
			exit_program(NULL, 1, "malloc error");
	}
	else
	{
		(*src)->neighbor = malloc(sizeof(t_pathfind));
		if (!(*src)->neighbor)
			exit_program(NULL, 1, "malloc error");
		*src = (*src)->neighbor;
	}
	if (!*head)
		*head = *src;
	return (*src);
}

t_pathfind	*neighbors(t_pathfind *node, t_player *player)
{
	t_pathfind	*neighbors;
	t_pathfind	*head;
	int			x;
	int			y;

	x = node->vector[X];
	y = node->vector[Y];
	head = NULL;
	neighbors = NULL;
	if (pos_is_valid(x + 1, y, player))
		set_node_vector(malloc_neighbor(&neighbors, &head), x + 1, y);
	if (pos_is_valid(x - 1, y, player))
		set_node_vector(malloc_neighbor(&neighbors, &head), x - 1, y);
	if (pos_is_valid(x, y + 1, player))
		set_node_vector(malloc_neighbor(&neighbors, &head), x, y + 1);
	if (pos_is_valid(x, y - 1, player))
		set_node_vector(malloc_neighbor(&neighbors, &head), x, y - 1);
	neighbors = head;
	while (neighbors)
	{
		neighbors->g = node->g + 1;
		neighbors->parent = node;
		neighbors = neighbors->neighbor;
	}
	return (head);
}

void	check_valid_neighbors(t_astar *astar)
{
	if (is_node(astar->neighbor, astar->closedlist) == 0)
	{
		astar->neighbor->f = astar->neighbor->g;
		astar->neighbor->f += astar->start->vector[X] - astar->goal->vector[X];
		astar->neighbor->f += astar->start->vector[Y] - astar->goal->vector[Y];
		if (is_node(astar->neighbor, astar->openlist) == 0)
		{
			astar->openlist = add_node(astar->neighbor, astar->openlist);
			astar->neighbor = astar->neighbor->neighbor;
		}
		else
		{
			astar->head = astar->neighbor;
			astar->neighbor = astar->neighbor->neighbor;
			free(astar->head);
			astar->head = NULL;
		}
	}
	else
	{
		astar->head = astar->neighbor;
		astar->neighbor = astar->neighbor->neighbor;
		free(astar->head);
		astar->head = NULL;
	}
}
