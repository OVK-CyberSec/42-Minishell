/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:25:45 by mohifdi           #+#    #+#             */
/*   Updated: 2025/04/24 19:20:32 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}


int main() {

    // Le nom du fichier d'origine
    const char * originalFilename = "folder/image.jpg";

    // On prépare le nom du fichier de destination
    size_t size = strlen( originalFilename ) + 1;   // +1 pour le zéro terminal
    char * destinationFilename = (char *) malloc( size );
    strcpy( destinationFilename, originalFilename );

    // Et on y remplace l'extension du fichier par l'extension .png
    printf("%s",strrchr( destinationFilename, '.' ));
    //strcpy( lastDotPos, ".png" );

    // On affiche les deux noms de fichiers
    //puts( originalFilename );
    //puts( destinationFilename );

    return EXIT_SUCCESS;
}

