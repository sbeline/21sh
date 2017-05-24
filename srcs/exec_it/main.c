/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourget <mbourget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 17:04:58 by sbeline           #+#    #+#             */
/*   Updated: 2017/05/24 02:24:37 by mbourget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "termcaps.h"

int	dfd = -1;

int					find_varibale(char *str, char c)
{
	int				count;

	count = 0;
	while (str[count])
	{
		if (str[count] == c)
			return (1);
		count++;
	}
	return (-1);
}

void				print_ascii(void)
{
	ft_putstr("\033[1;36m");
	ft_putendl(" _____  ______   _______ _______ _______ _____   _____   ");
	ft_putendl("|  |  ||__    | |     __|   |   |    ___|     |_|     |_ ");
	ft_putendl("|__    |    __| |__     |       |    ___|       |       |");
	ft_putendl("   |__||______| |_______|___|___|_______|_______|_______|");
	ft_putstr("\033[0m");
}

int					prompt(void)
{
	char			*user;
	char			*pwd;
	int				lenght_prompt;

	lenght_prompt = 0;
	if ((user = ft_strjoin("\033[1;31m", search_env(g_env, "USER="))) != NULL)
	{
		lenght_prompt = ft_strlen(search_env(g_env, "USER="));
		ft_putstr(user);
		ft_putstr("\033[0m:");
		free(user);
	}
	if ((pwd = ft_strjoin("\033[1;69m", search_env(g_env, "PWD="))) != NULL)
	{
		lenght_prompt += ft_strlen(search_env(g_env, "PWD="));
		ft_putstr(pwd);
		ft_putstr("\033[0m:");
		free(pwd);
	}
	ft_putstr(" $>");
	return (lenght_prompt + 3);
}

void				end_memory(void)
{
	if (g_memory.line)
		free(g_memory.line);
	if (g_memory.key_ctrl)
		free(g_memory.key_ctrl);
	if (g_memory.variable == NULL)
		ft_lstdel(&(g_memory.variable), ft_bzero);
	if (g_memory.line_mode == NULL)
		free(g_memory.line_mode);
}

int					main(void)
{
	t_mode			mode;
	int				ctrl;

	if ((dfd = open("/dev/ttys002", O_WRONLY)) == -1)
		ft_putendl("log init failed");
	ctrl = 0;
	mode = SHELL;
	g_env = build_env();
	init_memory();
	ft_putstr_fd(PROMPT, STDERR_FILENO);
	while (42)
	{
		termcaps(&g_memory);
		if (g_memory.inp.cmdlen > 0)
		{
			g_memory.mode = lexer_parser(&g_memory);
			if (g_memory.mode == SHELL)
			{
				hst_push(&g_memory, NULL);
				g_memory.line = NULL;
				g_memory.line_lenght = 0;
				// dbg_history(&g_memory);
			}
		}
		cbuf_reset(&g_memory);
	}
	end_memory();
	return (0);
}
