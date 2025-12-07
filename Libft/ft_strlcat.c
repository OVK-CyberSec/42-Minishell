/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:46:29 by mohifdi           #+#    #+#             */
/*   Updated: 2025/04/15 16:46:33 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
signed int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	desl;
	unsigned int	srl;
	unsigned int	i;

	i = 0;
	srl = 0;
	desl = 0;
	while (dest[desl] != '\0')
		desl++;
	while (src[srl] != '\0')
		srl++;
	if (desl >= size)
		return (srl + size);
	while (src[i] != '\0' && desl + i < size - 1)
	{
		dest[desl + i] = src[i];
		i++;
	}
	dest[desl + i] = '\0';
	return (desl + srl);
}
/*
#include <stdio.h>
int main()
{
    // Initialisation des chaînes
    char dest[50] = "Hello";  dest est assez grand
    char *src = " World!";
    unsigned int size = 5;

    // Affichage avant la concaténation
    printf("Avant la concaténation:\n");
    printf("Dest : '%s'\n", dest);  // Affiche "Hello"
    printf("Src : '%s'\n", src);    // Affiche " World!"
    printf("Taille maximale : %u\n", size);  // Affiche "20"

    // Appel de ft_strlcat
    unsigned int result = ft_strlcat(dest, src, size);

    // Affichage après la concaténation
    printf("\nAprès la concaténation:\n");
    printf("Dest : '%s'\n", dest);  // Affiche "Hello World!"
    printf("Longueur totale de la chaîne résultante : %u\n", result);

    return 0;
}
*/
