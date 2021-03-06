/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeline <sbeline@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 17:04:58 by sbeline           #+#    #+#             */
/*   Updated: 2017/04/13 09:40:40 by sbeline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/libft.h"

void		ft_lstadd(t_llist **alst, t_llist *n)
{
	t_llist *ptr;

	ptr = *alst;
	if (ptr == NULL)
		*alst = n;
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = n;
		ptr->next->maillon_nb = ptr->maillon_nb + 1;
	}
}
