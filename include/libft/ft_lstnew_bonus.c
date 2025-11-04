/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:37:56 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 19:22:55 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Parameters: content:  The content to store in the new node.
// Return value: A pointer to the new node
// Description: Allocates memory (using malloc(3)) and returns a new node.
// The ’content’ member variable is initialized with the given parameter
// ’content’. The variable ’next’ is initialized to NULL.
t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

// int	main(void)
// {
// 	char *s = "hello";
// 	t_list *result = ft_lstnew(s);
// 	printf("%s\n", result->content);
// 	free(result);
// 	return (0);
// }