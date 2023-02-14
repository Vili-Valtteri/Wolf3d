/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_following.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:44:19 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/27 15:51:47 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_pathfind	*lowest_f_value(t_pathfind *node)
{
	t_pathfind	*temp;

	temp = node;
	while (node)
	{
		if (node->f < temp->f)
			temp = node;
		node = node->next;
	}
	return (temp);
}

static void	astart_start_setup(t_astar *astar)
{
	astar->closedlist = NULL;
	astar->start = malloc(sizeof(t_pathfind));
	if (!astar->start)
		exit_program(NULL, 1, "malloc error");
	astar->goal = malloc(sizeof(t_pathfind));
	if (!astar->goal)
	{
		free(astar->start);
		exit_program(NULL, 1, "malloc error");
	}
	astar->goal->vector[X] = (int)astar->ai_bot->posxy[X];
	astar->goal->vector[Y] = (int)astar->ai_bot->posxy[Y];
	astar->start->vector[X] = (int)astar->player->posxy[X];
	astar->start->vector[Y] = (int)astar->player->posxy[Y];
	astar->start->next = NULL;
	astar->start->parent = NULL;
	astar->start->g = 0;
	astar->start->f = astar->start->g;
	astar->start->f += astar->start->vector[X] - astar->goal->vector[X];
	astar->start->f += astar->start->vector[Y] - astar->goal->vector[Y];
	astar->openlist = astar->start;
}

static int	current_node(t_astar *astar)
{
	astar->current = lowest_f_value(astar->openlist);
	if (astar->current->vector[X] == astar->goal->vector[X])
		if (astar->current->vector[Y] == astar->goal->vector[Y])
			return (1);
	astar->openlist = remove_node(astar->current, astar->openlist);
	astar->closedlist = add_node(astar->current, astar->closedlist);
	astar->neighbor = neighbors(astar->current, astar->player);
	return (0);
}

t_pathfind	*path_following(t_astar *astar)
{
	astart_start_setup(astar);
	while (astar->openlist)
	{
		if (current_node(astar) == 1)
		{
			free(astar->goal);
			return (astar->current);
		}
		while (astar->neighbor)
		{
			check_valid_neighbors(astar);
		}
	}
	free(astar->goal);
	return (NULL);
}
