/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:45:06 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 18:27:23 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Parameters:
// lst: The address of a pointer to a node.
// f: The address of the function to apply to each node’s content.
// Description: Iterates through the list ’lst’ and applies the function ’f’
// to the content of each node.
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}
