/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_pt2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeline <sbeline@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 17:04:58 by sbeline           #+#    #+#             */
/*   Updated: 2017/05/16 16:51:36 by sbeline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer_parser/lexer_parser.h"

int				ctrl_heredoc(t_memory *memory, char *line)
{
	memory->key_ctrl = ft_strndup(line, 0,
						(memory->line_lenght = find_str(line)));
	return (HEREDOC_CODE);
}

int				ctrl_quot(int first, int second)
{
	if (first == 34)
		return (D_QUOTE_CODE);
	else if (first == 39)
		return (QUOTE_CODE);
	else if (first == 96)
		return (BACKQUOTE_CODE);
	else if (first == '<' && second == '<' && g_memory.heredoc_sw == 0)
		return (HEREDOC_CODE);
	return (0);
}

void			save_mode(t_memory *memory, char *line, int end)
{
	int			i;
	int			y;

	i = 0;
	y = 1;
	memory->line_mode_tmp = (char*)ft_memalloc(sizeof(char) * end);
	while (i < end - 1)
	{
		memory->line_mode_tmp[i] = line[y];
		line++;
		y++;
	}
	memory->line_mode_tmp[end] = 0;
}

int				ctrl_mode(char *line, t_memory *memory)
{
	int			count;
	int			tmp;

	count = 0;
	if ((tmp = ctrl_quot(line[count], line[count + 1])) > 0)
	{
		count++;
		if (tmp == HEREDOC_CODE)
			return (ctrl_heredoc(memory, line + 3));
		if (tmp == D_QUOTE_CODE)
			memory->key_ctrl = ft_strdup("\"");
		if (tmp == QUOTE_CODE)
			memory->key_ctrl = ft_strdup("\'");
		if (tmp == BACKQUOTE)
			memory->key_ctrl = ft_strdup("`");
		while (line[count])
		{
			if (tmp == ctrl_quot(line[count], 0))
				return (count);
			count++;
		}
		return (tmp);
	}
	return (0);
}

int				is_bulltin(char *cmd)
{
	if (ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unsetenv") == 0
		|| ft_strcmp(cmd, "setenv") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "history") == 0
		|| ft_strcmp(cmd, "var") == 0)
		return (1);
	return (0);
}
