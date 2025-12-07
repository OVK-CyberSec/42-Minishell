/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:30:33 by mohifdi           #+#    #+#             */
/*   Updated: 2025/04/14 15:11:10 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)ptr1;
	p2 = (unsigned char *)ptr2;
	i = 0;
	while (num > i)
	{
		if (p1[i] > p2[i])
			return (1);
		else if (p1[i] < p2[i])
			return (-1);
		i++;
	}
	return (0);
}

/*
int main() {
    char buffer1[] = "Bonjour";
    char buffer2[] = "Bonjour";
    char buffer3[] = "Bonsoir";

    // Comparer buffer1 et buffer2 (identiques)
    int result = ft_memcmp(buffer1, buffer2, 7);
    if (result == 0) {
        printf("buffer1 et buffer2 sont identiques.\n");
    } else {
        printf("buffer1 et buffer2 sont différents.\n");
    }

    // Comparer buffer1 et buffer3 (différents)
    result = memcmp(buffer1, buffer3, 7);  // Comparer 7 premiers octets
    if (result == 0) {
        printf("buffer1 et buffer3 sont identiques.\n");
    } else {
        printf("buffer1 et buffer3 sont différents.\n");
    }

    return 0;
}
*/
