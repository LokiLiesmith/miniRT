/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 21:13:13 by djanardh          #+#    #+#             */
/*   Updated: 2025/12/02 17:18:00 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_object	*create_new_obj(t_objtype type, void *data)
{
	t_object	*new_obj;

	new_obj = (t_object *)malloc(sizeof(t_object));
	if (!new_obj)
		return (printf("Error\nMalloc error - new node\n"), NULL);
	new_obj->type = type;
	new_obj->data = data;
	new_obj->next = NULL;
	return (new_obj);
}

void	add_obj(t_object **list, t_object *new)
{
	t_object	*current;

	if (new == NULL)
		return ;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	current = *list;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
}
