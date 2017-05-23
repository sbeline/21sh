/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeline <sbeline@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 17:27:30 by sbeline           #+#    #+#             */
/*   Updated: 2017/05/15 17:01:19 by sbeline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void		i_need_place(t_line *nw, t_win *win)
{
	nw->next = win->begin;
	(win->begin)->prev = nw;
	win->begin = nw;
}

void		list_line_push(t_line *nw, t_win *win)
{
	t_line	*save;
	t_line	*ptr;
	int		i;

	i = 0;
	ptr = win->begin;
	if (win->cursor_line > 1)
	{
		while (++i != win->cursor_line - 1)
			ptr = ptr->next;
		save = ptr->next;
		nw->next = ptr->next;
		nw->prev = ptr;
		save->prev = nw;
		ptr->next = nw;
	}
	else
		i_need_place(nw, win);
	printline(nw);
	win->lenght_line++;
	win->cursor_line++;
	move_cursr(win, M_LEFT, win->lenght_line - win->cursor_line + 1);
}

t_line		*nw_char(unsigned int buffer)
{
	t_line	*nw;

	nw = (t_line*)ft_memalloc(sizeof(t_line));
	nw->l_char = buffer;
	nw->next = NULL;
	nw->prev = NULL;
	return (nw);
}

int			push_line(t_win *win, unsigned int buffer)
{
	t_line	*nw;

	nw = nw_char(buffer);
	if (win->cursor_line - 1 == win->lenght_line)
	{
		win->lenght_line++;
		win->cursor_line = win->lenght_line + 1;
		if (win->begin == NULL && win->end == NULL)
		{
			win->begin = nw;
			win->end = nw;
			ft_putchar(nw->l_char);
		}
		else
		{
			win->end->next = nw;
			nw->prev = win->end;
			win->end = nw;
			ft_putchar(nw->l_char);
		}
	}
	else
		list_line_push(nw, win);
	return (1);
}
