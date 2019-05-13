/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 01:19:05 by student           #+#    #+#             */
/*   Updated: 2019/05/13 11:59:31 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>

#include "ft_printf.h"
#include "conversion.h"

void	do_conversion(va_list ap, t_token *token)
{
	t_conversion	*c;
	char			*str;

	c = token->conv;
	str = c->func(c, ap);
	delete_conversion(c);
	token->conv = NULL;
	token->str = str;
}

/*
**	Iterates over the token list, converting tokens in need of conversion
*/

void	do_conversions(va_list ap, t_doubly_linked_list *token_list)
{
	t_token					*token;
	size_t idx;

	idx = token_list->size - 1;
	while ((token = list_get_index(token_list, idx--)))
	{
		if (token->conv)
			do_conversion(ap, token);
	}
}

int	ft_va_list_printf(char *str, size_t size, const char *format, va_list args)
{
	t_doubly_linked_list	*token_list;
	char *tmp;

	token_list = tokenize(format);
	do_conversions(args, token_list);
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
