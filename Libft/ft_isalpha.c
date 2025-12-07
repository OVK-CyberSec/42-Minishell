/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:27:17 by mohifdi           #+#    #+#             */
/*   Updated: 2025/04/11 17:27:59 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalpha(int value)
{
	if ((value > 64 && value < 91) || (value > 96 && value < 123))
		return (1);
	else
		return (0);
	return (0);
}

/*
void	main(void)
{
	printf("%d",isalpha('/'));
}
*/
