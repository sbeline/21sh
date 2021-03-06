/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourget <mbourget@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 11:21:00 by sbeline           #+#    #+#             */
/*   Updated: 2017/05/25 01:28:47 by mbourget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	sig_set(int signo)
{
	g_memory.signo = signo;
	ioctl(STDIN_FILENO, TIOCSTI, "");
}

void	sig_init(void)
{
	signal(SIGWINCH, &sig_set);
	signal(SIGINT, &sig_set);
}

void	sig_handler(t_memory *sh)
{
	if (sh->signo == SIGINT)
	{
		ft_putchar('\n');
		cbuf_reset(sh);
	}
	else if (sh->signo == SIGWINCH)
		tc_refresh(sh);
	sh->signo = 0;
}
