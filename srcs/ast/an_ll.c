/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   an_ll.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeline <sbeline@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 16:08:18 by sbeline           #+#    #+#             */
/*   Updated: 2017/04/11 14:54:09 by sbeline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast/ast.h"

t_lexem			*find_op(t_st_lexem *statement)
{
	t_lexem		*ptr;
	t_lexem		*max;

	ptr = statement->begin_lexem;
	max = ptr;
	while (ptr)
	{
		if (max->priority <= ptr->priority)
			max = ptr;
		ptr = ptr->next;
	}
	return (max);
}

t_lexem			*find_prev_max(t_lexem *ptr)
{
	t_lexem		*max;
	t_lexem		*pcr;

	pcr = ptr;
	max = pcr;
	while (pcr != NULL)
	{
		if (max->priority <= pcr->priority)
			max = pcr;
		pcr = pcr->prev;
	}
	return (max);
}

t_lexem			*find_next_max(t_lexem *ptr)
{
	t_lexem		*max;
	t_lexem		*pcr;

	pcr = ptr;
	max = pcr;
	while (pcr != NULL)
	{
		if (max->priority <= pcr->priority)
			max = pcr;
		pcr = pcr->next;
	}
	return (max);
}