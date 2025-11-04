/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djanardh <djanardh@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:22:23 by djanardh          #+#    #+#             */
/*   Updated: 2025/03/20 18:19:28 by djanardh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The malloc() function allocates size bytes of memory and returns a
// pointer to the allocated memory.
// Prototype:void *malloc(size_t size);

#include "libft.h"

// The calloc() function contiguously allocates enough space for count
// objects that are size bytes of memory each and returns a pointer to the
// allocated memory.  The allocated memory is filled with bytes of value zero.
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	final_size;

	final_size = count * size;
	ptr = malloc(final_size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, final_size);
	return (ptr);
}

// int	main(void)
// {
// 	size_t count = 1;
// 	size_t size = 0;
// 	char *ptr1;
// 	char *ptr2;

// 	ptr2 = ft_calloc(count, size);
// 	printf("%s\n", ptr2);
// 	ptr1 = calloc(count, size);
// 	printf("%s\n", ptr1);
// 	return (0);
// }