/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 01:19:05 by student           #+#    #+#             */
/*   Updated: 2019/04/14 00:37:44 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>

#include "ft_printf.h"
#include "conversion.h"

#define ALL_CONVERSION_CHRS "cspdiouxX"
#define ALL_FLAG_CHRS "#0-+ "
#define ALL_LENGTH_MODIFIER_CHRS "hl"
#define SPEC_CHR '%'

#define IS_FLAG_CHR(c) (ft_strchr(ALL_FLAG_CHRS, c) != NULL)
#define IS_CONVERSION_TYPE_CHR(c) (ft_strchr(ALL_CONVERSION_CHRS, c) != NULL)

#define _ISLMC(c) (ft_strchr(ALL_LENGTH_MODIFIER_CHRS, c) != NULL)
#define IS_LENGTH_MODIFIER_CHR(c) _ISLMC(c)

t_token		*new_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->str = NULL;
	token->conv = NULL;
	return (token);
}

/*
**	Given a spec (a string beginning with single '%'),
**	return the length in characters of the entire conversion spec
*/

size_t	conversion_spec_length(const char *str)
{
	size_t	len;

	len = 1;
	while (IS_FLAG_CHR(str[len]))
		len++;
	while (IS_DIGIT(str[len]))
		len++;
	while (str[len] == '.')
		len++;
	while (IS_DIGIT(str[len]))
		len++;
	while (IS_LENGTH_MODIFIER_CHR(str[len]))
		len++;
	while (IS_CONVERSION_TYPE_CHR(str[len]))
		len++;
	return (len);
}

size_t	length_of_str_to_next_spec_char_or_null(const char *str)
{
	size_t	len;
	char	*tmp;

	tmp = ft_strchr(str, SPEC_CHR);
	if (tmp == NULL)
		len = ft_strlen(str);
	else
		len = tmp - str;
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

t_doubly_linked_list	*expand_va_args(const char *format, va_list ap)
{
	t_doubly_linked_list	*token_list;
	t_element_container		*container;
	t_token					*token;
	int foo;

	token_list = tokenize(format);
	container = token_list->head;
	while ((token = get_next_conversion(container)))
	{
		foo = va_arg(ap, int);
		token->str = ft_itoa(foo);
		free(token->conv);
		token->conv = NULL;
	}
	return (token_list);
}

void	apply_conversions(const char *format, va_list ap, t_doubly_linked_list *token_list)
{
	(void)format;
	(void)ap;
	(void)token_list;
}

char	*join_token_strings(t_doubly_linked_list *token_list)
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


void	delete_conversion(t_conversion *conv)
{
	free (conv);
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

int	ft_va_list_printf(char *str, size_t size, const char *format, va_list args)
{
	t_doubly_linked_list	*token_list;
	char *tmp;

	token_list = expand_va_args(format, args);
	apply_conversions(format, args, token_list);
	tmp = join_token_strings(token_list);
	delete_doubly_linked_list(token_list, &delete_token);
	ft_strncpy(str, tmp, size);
	free(tmp);
	return (0);
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
