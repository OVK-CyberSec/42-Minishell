/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:55:10 by mohifdi           #+#    #+#             */
/*   Updated: 2025/04/11 17:55:15 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	slenght;
	unsigned int	i;

	i = 0;
	slenght = 0;
	while (src[slenght] != '\0')
		slenght++;
	if (size == 0)
		return (slenght);
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (slenght);
}
/*
#include <string.h>
#include <stdio.h>
int main() {
    // Chaîne source
    char src[] = "Un exemple simple de copie avec strlcpy";

    // Tableau de destination suffisamment grand
    char dest[50]; // Plus grand que la chaîne source, donc pas de troncature

    // Utilisation de strlcpy pour copier la chaîne
    size_t len = ft_strlcpy(dest, src, sizeof(dest));

    // Affichage de la chaîne copiée dans dest
printf("Chaîne copiée : %s\n", dest);  // "Un ex de copie avec strlcpy"
    
    // Affichage de la longueur de la chaîne source
    printf("Longueur de la chaîne source : %zu\n", len);  // 41
    
    // Affichage de la longueur de la chaîne copiée
    printf("Longueur de la chaîne copiée : %zu\n", strlen(dest));  // 41

    return 0;
}
*/
