/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 22:51:55 by djanardh          #+#    #+#             */
/*   Updated: 2025/10/30 22:56:00 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void free_objects(t_object **list)
{
    t_object *current;
    t_object *next;

    if (!list || !*list)
        return;
    current = *list;
    while (current)
    {
        next = current->next;
        if (current->data)
            free(current->data);
        free(current);
        current = next;
    }
    *list = NULL;
}
