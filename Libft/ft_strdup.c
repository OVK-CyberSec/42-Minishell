/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:48:00 by mohifdi           #+#    #+#             */
/*   Updated: 2025/04/11 18:32:11 by mohifdi          ###   ########.fr       */
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

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*string;

	if (!s)
		return (NULL);
	len = ft_strlen((char *)s) + 1;
	string = (char *)malloc(len);
	if (!string)
		return (NULL);
	ft_memcpy(string, s, len);
	return (string);
}

/*
int main() {
    const char *original = "Bonjour, le monde!";
    
    // Dupliquer la chaîne
    char *copy = ft_strdup(original);
    
    if (copy == NULL) {
        printf("Erreur d'allocation mémoire !\n");
        return 1;
    }
    
    // Afficher la chaîne originale et la copie
    printf("Original: %s\n", original);
    printf("Copie: %s\n", copy);
    
    // Libérer la mémoire allouée pour la copie
    free(copy);

    return 0;
}
*/
