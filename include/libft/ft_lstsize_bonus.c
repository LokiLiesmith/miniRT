/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:40:01 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 18:29:21 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Parameters: lst:  The beginning of the list.
// Return value: The length of the list
// Description: Counts the number of nodes in the list.
int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

// int	main(void)
// {
// 	t_list *lst;
// 	lst = malloc(sizeof(t_list));
// 	if (!lst)
// 		return (0);
// 	int x = 6;
// 	int *ptr = &x;
// 	int y = 7;
// 	int *ptr2 = &y;
// 	lst->content = ptr;
// 	lst->next = ft_lstnew(ptr2);
// 	printf("%i\n", ft_lstsize(lst));
// 	free(lst);
// 	return (0);
// }