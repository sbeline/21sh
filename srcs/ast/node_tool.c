/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeline <sbeline@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 19:11:22 by sbeline           #+#    #+#             */
/*   Updated: 2017/04/29 15:39:02 by sbeline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast/ast.h"
#include "../../includes/prototypage/proto.h"

t_lexem			*rechatch_lexm(t_lexem *ptr, t_st_lexem *lex)
{
	t_lexem		*save;

	save = ptr;
	if (ptr->prev == NULL)
	{
		ptr->next->prev = NULL;
		lex->begin_lexem = ptr->next;
	}
	else if (ptr->next == NULL)
	{
		ptr->prev->next = NULL;
		lex->end_lexem = ptr->prev;
	}
	else
	{
		ptr->prev->next = ptr->next;
		ptr->next->prev = ptr->prev;
	}
	save->next = NULL;
	save->prev = NULL;
	return (save);
}

t_node			*create_node(t_lexem *ptr, t_st_lexem *lex)
{
	t_node		*new_node;

	new_node = (t_node*)ft_memalloc(sizeof(t_node));
	new_node->body = (t_body_node*)ft_memalloc(sizeof(t_body_node));
	new_node->left_op = NULL;
	new_node->right_op = NULL;
	new_node->parent = NULL;
	new_node->body->lexem = rechatch_lexm(ptr, lex);
	if (new_node->body->lexem->priority > 0)
		new_node->body->type_node = OP;
	else
		new_node->body->type_node = LEAF;
	new_node->body->fd = 1;
	return (new_node);
}

int				full_leaf(t_node **node, t_node **parent_node, t_node *new_node)
{
	if (*node == NULL)
	{
		new_node->parent = *parent_node;
		*node = new_node;
		return (1);
	}
	if ((*node)->body->type_node != LEAF)
	{
		if ((*node)->left_op != NULL)
			if ((full_leaf(&(*node)->left_op, node, new_node)) == 1)
				return (1);
		if ((*node)->left_op == NULL)
			if ((full_leaf(&(*node)->left_op, node, new_node)) == 1)
				return (1);
		if ((*node)->right_op != NULL)
			if ((full_leaf(&(*node)->right_op, node, new_node)) == 1)
				return (1);
		if ((*node)->right_op == NULL)
			if ((full_leaf(&(*node)->right_op, node, new_node)) == 1)
				return (1);
	}
	return (0);
}

void			add_node(t_node **node, t_node **parent_node, t_node *new_node)
{
	if (*node == NULL)
	{
		new_node->parent = *parent_node;
		*node = new_node;
		return ;
	}
	else if ((*node)->body->lexem->priority == new_node->body->lexem->priority)
		add_node(&(*node)->left_op, node, new_node);
	else if ((*node)->left_op == NULL ||
			new_node->body->lexem->priority < (*node)->body->lexem->priority)
		add_node(&(*node)->left_op, node, new_node);
	else
		add_node(&(*node)->right_op, node, new_node);
}
