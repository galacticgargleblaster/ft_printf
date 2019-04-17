/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 01:19:05 by student           #+#    #+#             */
/*   Updated: 2019/04/17 01:37:32 by student          ###   ########.fr       */
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
		if (*format == SPEC_CHR && *(format + 1) != SPEC_CHR)
		{
			len = conversion_spec_length(format);
			token->conv = new_conversion(ft_strndup(format, len));
		}
		else if (*format == SPEC_CHR && *(format + 1) != SPEC_CHR)
		{
			format++;
			len = length_of_str_to_next_spec_char_or_null(format);
			token->str = ft_strndup(format, len);
		}
		else
		{
			len = length_of_str_to_next_spec_char_or_null(format);
			token->str = ft_strndup(format, len);
		}
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
	t_element_container	*container;
	char				*str;

	total_len = 0;
	container = token_list->head;
	while (container)
	{
		token = container->element;
		total_len += ft_strlen(token->str);
		container = container->prev;
	}
	str = ft_strnew(total_len);
	container = token_list->head;
	while (container)
	{
		token = container->element;
		str = ft_strcat(str, token->str);
		container = container->prev;
	}
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