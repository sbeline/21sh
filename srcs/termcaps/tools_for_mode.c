/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeline <sbeline@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 11:25:09 by sbeline           #+#    #+#             */
/*   Updated: 2017/05/16 19:46:12 by sbeline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/termcaps/termcaps.h"
#include "../../includes/shell.h"

void		printline(t_line *begin)
{
	t_line *ptr;

	ptr = begin;
	while (ptr)
	{
		ft_putchar(ptr->l_char);
		ptr = ptr->next;
	}
}

int			stop_her(t_line **end)
{
	int 	len;
	t_line	*ptr;
	t_line	*save;

	ptr = *end;
	len = ft_strlen(g_memory.key_ctrl) - 1;
	while (ptr && g_memory.key_ctrl[len] == ptr->l_char)
	{
		len--;
		ptr = ptr->prev;
	}
	if (len == -1)
	{
		g_memory.heredoc_sw = 1;
		return (0);
	}
	return (1);
}
