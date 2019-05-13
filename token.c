/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 01:19:05 by student           #+#    #+#             */
/*   Updated: 2019/05/13 11:00:17 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>

#include "ft_printf.h"
#include "conversion.h"

t_token		*new_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->str = NULL;
	token->conv = NULL;
	return (token);
}

/*
**	Stores a parsed conversion specification
*/

size_t	store_conversion(t_token *token, const char *format)
{
	token->conv = new_conversion(format);
	return ft_strlen(token->conv->spec);
}

/*
**	Stores a plain string -- no conversion necessary
*/

#define NO_ESCAPE 0
#define ESCAPE_DOUBLE_PCT 1

size_t	store_string(t_token *token, const char *format, int escape)
{
	size_t	len;

	if (escape)
	{
		len = 1 + length_of_str_to_next_spec_char_or_null(format + 2);
		token->str = ft_strndup(format + 1, len);
		len += 1;
	}
	else
	{
		len = length_of_str_to_next_spec_char_or_null(format);
		token->str = ft_strndup(format, len);
	}
	return (len);
}

/*
**	iterates over the format string and returns a list of tokens
**
**	Find any '%' that isn't followed by another '%', and read until the
**	entire format spec is consumed.  This means eating flags,
**	conversion chars, and modifier chars.
*/

t_doubly_linked_list	*tokenize(const char *format)
{
	t_doubly_linked_list	*token_list;
	t_token		*token;
	size_t		len;
	
	token_list = new_doubly_linked_list();
	while (*format)
	{
		token = new_token();
		if (*format == SPEC_CHR && *(format + 1) && *(format + 1) != SPEC_CHR)
			len = store_conversion(token, format);
		else if (*format == SPEC_CHR && *(format + 1) && *(format + 1) == SPEC_CHR)
			len = store_string(token, format, ESCAPE_DOUBLE_PCT);
		else
			len = store_string(token, format, NO_ESCAPE);
		list_push_tail(token_list, token);
		format += len;
	}
	return (token_list);
}

/*
**	Given a list of tokens, returns a new string that is the concatenation of
**	all token->str
*/

char					*join_token_strings(t_doubly_linked_list *token_list)
{
	size_t				total_len;
	t_token				*token;
	char				*str;
	size_t				idx;

	total_len = 0;
	idx = 0;
	while ((token = list_get_index(token_list, idx++)))
		total_len += ft_strlen(token->str);
	str = ft_strnew(total_len);
	ft_memset(str, 0, total_len);
	idx = token_list->size - 1;
	while ((token = list_get_index(token_list, idx--)))
		str = ft_strcat(str, token->str);
	return (str);
}

void	delete_token(void *token_ptr)
{
	t_token	*token;

	token = token_ptr;
	if (token->str)
		free(token->str);
	if (token->conv)
		delete_conversion(token->conv);
	free(token);
}

t_token		*get_next_conversion(t_element_container *container)
{
	t_token	*token;

	while (container)
	{
		token = container->element;
		if (token->conv != NULL)
			return (token);
		else
			container = container->prev;
	}
	return (NULL);
}