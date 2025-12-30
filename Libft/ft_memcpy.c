/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:46:30 by mohifdi           #+#    #+#             */
/*   Updated: 2025/04/11 18:34:23 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	const char		*s;
	size_t			i;

	d = dest;
	s = src;
	i = 0;
	while (n > i)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
/*
int main() {
    char src[] = "Bonjour, monde!";
    char dest[20];

    // Copier 16 octets de la source vers la destination
    ft_memcpy(dest, src, 16);

    printf("Source: %s\n", src);
    printf("Destination: %s\n", dest);

    return 0;
}
*/
