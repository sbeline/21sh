/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexem.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeline <sbeline@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 17:04:58 by sbeline           #+#    #+#             */
/*   Updated: 2017/05/07 21:18:17 by sbeline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer_parser/lexer_parser.h"

t_lexem				*new_lexem(char *line)
{
	t_lexem			*new_lexem;

	new_lexem = (t_lexem*)ft_memalloc(sizeof(t_lexem));
	new_lexem->name_lexem = ft_strdup(line);
	new_lexem->next = NULL;
	new_lexem->prev = NULL;
	new_lexem->index = 0;
	new_lexem->option = NULL;
	new_lexem->token_type = define_token(new_lexem->name_lexem);
	new_lexem->priority = define_prio(new_lexem->token_type);
	return (new_lexem);
}

static void			option_lexem(t_st_lexem *lex, t_lexem *new)
{
	if ((new->option = init_option(new->name_lexem, new->option, new->index)))
	{
		lex->save = new;
		new->index++;
	}
}

void				push_lexem(t_st_lexem *lex, t_lexem *new)
{
	if ((lex->end_lexem->token_type == OP_REDIR_LEFT ||
		lex->end_lexem->token_type == OP_REDIR_RIGHT))
	{
		new->token_type = OP_FILES;
		new->priority = define_prio(new->token_type);
	}
	new->prev = lex->end_lexem;
	lex->end_lexem->next = new;
	lex->end_lexem = new;
	if (new->token_type == CMD)
	{
		option_lexem(lex, new);
		lex->nb_of_lexem++;
	}
}

static void			ctrl_lexem(t_st_lexem *lex, char *tmp, t_lexem *new)
{
	if (lex->end_lexem->token_type == OP_FILES && new->token_type == CMD)
	{
		lex->save->option = init_option(tmp, lex->save->option,
												lex->save->index);
		lex->save->index++;
		free_lexem(new);
		return ;
	}
	if (lex->end_lexem->token_type == CMD && new->token_type == CMD)
	{
		lex->end_lexem->option = init_option(tmp,
								lex->end_lexem->option, lex->end_lexem->index);
		lex->end_lexem->index++;
		free_lexem(new);
		return ;
	}
	push_lexem(lex, new);
}

void				save_lexem(t_st_lexem *lex, char *line, int end, int begin)
{
	t_lexem			*new;
	char			*tmp;

	tmp = ft_strndup(line, 0, end - begin);
	new = new_lexem(tmp);
	if (new->token_type == CMD)
		lex->cnt_op++;
	if (lex->begin_lexem == NULL)
	{
		lex->begin_lexem = new;
		lex->end_lexem = new;
		lex->nb_of_lexem = 1;
		if (new->token_type == CMD)
			option_lexem(lex, new);
		free(tmp);
		return ;
	}
	else
	{
		ctrl_lexem(lex, tmp, new);
		free(tmp);
	}
}
