/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 01:19:05 by student           #+#    #+#             */
/*   Updated: 2019/05/13 11:24:50 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>

#include "ft_printf.h"
#include "conversion.h"


void	do_conversion(va_list ap, t_token *token)
{
	t_conversion	*c;

	if ((c = token->conv))
	{
		token->str = c->func(ap, c);
		delete_conversion(c);
		token->conv = NULL;
	}
}

/*
**	unmarshal the memory from va_list, and apply the conversion functions
**	necessary to expand it into a string.
*/

void	apply_conversions(va_list ap, t_doubly_linked_list *token_list)
{
	t_token					*token;
	size_t idx;

	idx = token_list->size - 1;
	while ((token = list_get_index(token_list, idx)))
	{
		do_conversion(ap, token);
		idx--;
	}
}

int	ft_va_list_printf(char *str, size_t size, const char *format, va_list args)
{
	t_doubly_linked_list	*token_list;
	char *tmp;

	token_list = tokenize(format);
	apply_conversions(args, token_list);
	tmp = join_token_strings(token_list);
	delete_doubly_linked_list(token_list, &delete_token);
	ft_strncpy(str, tmp, size);
	free(tmp);
	return (ft_strlen(str));
}

#define LARGE_NUMBER_REMOVE_ME	1000

int	ft_printf(const char *format, ...)
{
	char	*str;
	va_list	args;
	int		return_value;

	str = malloc(LARGE_NUMBER_REMOVE_ME);
	va_start(args, format);
	return_value = ft_va_list_printf(str, LARGE_NUMBER_REMOVE_ME, format, args);
	va_end(args);
	ft_putstr(str);
	free(str);
	return (return_value);
}

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list	args;
	int		return_value;

	va_start(args, format);
	return_value = ft_va_list_printf(str, size, format, args);
	va_end(args);
	return (return_value);
}
