/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:45:54 by vlaine            #+#    #+#             */
/*   Updated: 2022/09/26 15:00:55 by vlaine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	t_pathfind	*check_prev(t_pathfind *prev, t_pathfind *node)
{
	t_pathfind	*head;

	head = NULL;
	if (prev)
	{
		prev->next = NULL;
		if (node->next)
			prev->next = node->next;
	}
	else if (node->next)
		head = node->next;
	node->next = NULL;
	return (head);
}

t_pathfind	*remove_node(t_pathfind *node, t_pathfind *src)
{
	t_pathfind	*prev;
	t_pathfind	*head;

	prev = NULL;
	head = NULL;
	while (src)
	{
		if (src->vector[X] == node->vector[X])
			if (src->vector[Y] == node->vector[Y])
				return (check_prev(prev, node));
		prev = src;
		src = src->next;
	}
	node->next = NULL;
	node->parent = NULL;
	return (NULL);
}

t_pathfind	*add_node(t_pathfind *node, t_pathfind *head)
{
	t_pathfind	*src;

	if (!head)
	{
		head = node;
		return (head);
	}
	src = head;
	while (src->next)
	{
		src = src->next;
	}
	src->next = node;
	node->next = NULL;
	return (head);
}

int	is_node(t_pathfind *node, t_pathfind *src)
{
	while (src)
	{
		if (node->vector[X] == src->vector[X])
			if (node->vector[Y] == src->vector[Y])
				return (1);
		src = src->next;
	}
	return (0);
}

t_pathfind	*find_node(t_pathfind *node, t_pathfind *src)
{
	while (1)
	{
		if (src->vector[X] == node->vector[X])
			if (src->vector[Y] == node->vector[Y])
				break ;
		src = src->next;
	}
	return (src);
}
