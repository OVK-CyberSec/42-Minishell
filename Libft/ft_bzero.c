/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:54:20 by mohifdi           #+#    #+#             */
/*   Updated: 2025/04/11 18:54:56 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = 0;
		i++;
	}
}

/*
int main() {
    char buffer[10] = "Bonjour";
    printf("Avant bzero: %s\n", buffer);
    
    bzero(buffer, sizeof(buffer));  // Res zéros
    
    printf("Après bzero: '%s'\n", buffer);
    
    return 0;
}
*/
