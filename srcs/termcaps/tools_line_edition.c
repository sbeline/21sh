/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_line_edition.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeline <sbeline@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 09:30:05 by sbeline           #+#    #+#             */
/*   Updated: 2017/05/16 23:49:14 by sbeline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/termcaps/termcaps.h"
#include "../../includes/shell.h"

void			free_lchar(t_win *win)
{
	t_line		*ptr;

	ptr = win->begin;
	while (ptr)
	{
		ptr = ptr->next;
		free(win->begin);
		win->begin = ptr;
	}
	win->begin = NULL;
	win->end = NULL;
}

static char		*simpl_lchar(t_win *win)
{
	t_line		*ptr;
	char		*str;
	int			i;

	i = 0;
	str = (char*)ft_memalloc(sizeof(char) * win->lenght_line + 1);
	g_memory.line_lenght += win->lenght_line;
	ptr = win->begin;
	while (ptr)
	{
		str[i] = ptr->l_char;
		ptr = ptr->next;
		free(win->begin);
		win->begin = ptr;
		i++;
	}
	win->begin = NULL;
	win->end = NULL;
	str[i] = '\0';
	return (str);
}

void 			purge_key(char *key, t_win *win)
{
	t_line		*ptr;
	t_line		*save;
	int			pos;


	ptr = win->end;
	pos = ft_strlen(key) - 1;
	while (ptr && ptr->l_char == key[pos])
	{
		save = ptr;
		if (ptr->prev)
			ptr = ptr->prev;
		else
			ptr = NULL;
		free(save);
		pos--;
	}
	if (ptr == NULL)
	{
		win->end = NULL;
		win->begin = NULL;
	}
	else
		win->end = ptr;
	free(g_memory.key_ctrl);
	g_memory.key_ctrl = NULL;
}

void			list_to_array(t_win *win)
{
	int			tmp;

	tmp = 0;
	if (g_memory.key_ctrl)
		purge_key(g_memory.key_ctrl, win);
	if (g_memory.line_mode)
	{
		g_memory.line = ft_strdup(g_memory.line_mode);
		tmp += ft_strlen(g_memory.line_mode);
		free(g_memory.line_mode);
		g_memory.line_mode = NULL;
	}
	if (win->begin != NULL)
	{
		if (g_memory.line)
			g_memory.line = ft_strjoin(g_memory.line, simpl_lchar(win));
		else
			g_memory.line = simpl_lchar(win);
	}
	if (g_memory.line_mode_after)
	{
		if (g_memory.line)
			g_memory.line = ft_strjoin(g_memory.line, g_memory.line_mode_after);
		else
			g_memory.line = ft_strdup(g_memory.line_mode);
		tmp += ft_strlen(g_memory.line_mode_after);
		free(g_memory.line_mode_after);
		g_memory.line_mode_after = NULL;
	}
	if (tmp)
		g_memory.line_lenght += tmp;
	ft_putnbr(g_memory.line_lenght);
}

void			list_lchar(char *str, t_win *win)
{
	int			i;
	int			y;

	y = 0;
	i = 0;
	while (str[y])
	{
		if (str[y] == ';')
			i = y + 1;
		y++;
	}
	while (str[i])
	{
		push_line(win, str[i]);
		i++;
	}
}

char			*lchar_list(t_line *line, int lenght)
{
	char	*str;
	t_line	*ptr;
	int		i;

	i = 0;
	ptr = line;
	str = (char*)ft_memalloc(sizeof(char) * lenght + 1);
	while (i < lenght)
	{
		str[i] = ptr->l_char;
		ptr = ptr->next;
		i++;
	}
	str[i] = '\0';
	return (str);
}
