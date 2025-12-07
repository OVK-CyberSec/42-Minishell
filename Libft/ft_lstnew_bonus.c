/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohifdi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:49:20 by mohifdi           #+#    #+#             */
/*   Updated: 2025/04/15 16:49:23 by mohifdi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*t;

	t = (t_list *)malloc(sizeof(t_list));
	if (!t)
		return (NULL);
	t->content = content;
	t ->next = NULL;
	return (t);
}
