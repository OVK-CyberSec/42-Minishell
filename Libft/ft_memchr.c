/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:56:36 by mohifdi           #+#    #+#             */
/*   Updated: 2025/04/11 17:58:25 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*s;

	s = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (s[i] == (unsigned char)c)
			return ((void *)&s[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int main() {
   const char str1[] = "abcdef";
   const char ch = 'd';

   char* result = (char*)ft_memchr(str1, ch, 4);

   if (result != NULL) {
       printf("'%c' found at position %ld\n", ch, result - str1);
   } else {
       printf("'%c' not found in the string\n", ch);
   }

   return 0;
}
*/
