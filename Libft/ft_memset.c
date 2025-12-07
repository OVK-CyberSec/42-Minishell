/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:29:13 by mohifdi           #+#    #+#             */
/*   Updated: 2025/04/11 17:29:46 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

/*
int main()
{
    int arr[10];

    // Initialisation du tableau avec des zéros
    memset(arr, 0, sizeof(arr)); // On éviter les valeurs aléatoires

    // On affecte à chaque octet de arr la valeur ASCII de 'e' (101)
    ft_memset(arr, 'e', sizeof(arr));

    printf("Tableau après ft_memset() : ");
    printf("%s ", arr);

    printf("\n");

    return 0;
}
*/
