/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeline <sbeline@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 16:29:43 by sbeline           #+#    #+#             */
/*   Updated: 2017/05/07 18:53:14 by sbeline          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer_parser/lexer_parser.h"

void				stock_line(t_memory *memory)
{
	if (memory->line != NULL)
	{
		memory->key = memory->line[ft_strlen(memory->line)];
		memory->line_mode = ft_strdup(memory->line);
	}
}
