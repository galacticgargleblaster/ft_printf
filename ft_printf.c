/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 01:19:05 by student           #+#    #+#             */
/*   Updated: 2019/04/07 13:25:38 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>

/*
**	va_arg is function-like macro that takes a type as an argument.
**	here's a possible implementation:
**
**typedef unsigned char *va_list;
**#define va_start(list, param) (list = (((va_list)&param) + sizeof(param)))
**#define va_arg(list, type) (*(type *)((list += sizeof(type)) - sizeof(type)))
*/


typedef struct	s_conversion
{
	char					*spec;
	t_doubly_linked_list	*functions;
}				t_conversion;

typedef struct	s_flag
{
	char	*identifier;
}				t_flag;

#define ALL_CONVERSION_CHRS "cspdiouxX"
#define ALL_FLAG_CHRS "#0-+ "
#define ALL_LENGTH_MODIFIER_CHRS "hl"
#define SPEC_CHR '%'

#define IS_FLAG_CHR(c) (ft_strchr(ALL_FLAG_CHRS, c) != NULL)
#define IS_CONVERSION_TYPE_CHR(c) (ft_strchr(ALL_CONVERSION_CHRS, c) != NULL)

#define _ISLMC(c) (ft_strchr(ALL_LENGTH_MODIFIER_CHRS, c) != NULL)
#define IS_LENGTH_MODIFIER_CHR(c) _ISLMC(c)

/*
**	A token may be either a string literal or a conversion specification,
**	but not both.
**	As soon as the conversion is done, 'conv' is freed and set to NULL.
*/

typedef struct	s_token
{
	char			*str;
	t_conversion	*conv;

}				t_token;

t_token		*new_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->str = NULL;
	token->conv = NULL;
	return (token);
}

void	*func_for_flag(char	flag)
{
	(void)flag;
	return (NULL);
}
void	*func_for_conv(char	flag)
{
	(void)flag;
	return (NULL);
}

/*
**	Given a spec, return a list of functions, that when applied in the order
**	they appear in the list, return a string in the specified format
*/

t_doubly_linked_list	*assemble_conversion_functions_for(char *spec)
{
	t_doubly_linked_list	*funcs;

	funcs = new_doubly_linked_list();
	while (IS_FLAG_CHR(*spec))
	{
		list_push_head(funcs, func_for_flag(*spec));
		spec++;
	}
	while (IS_CONVERSION_TYPE_CHR(*spec))
	{
		list_push_head(funcs, func_for_conv(*spec));
		spec++;
	}
	while (IS_LENGTH_MODIFIER_CHR(*spec))
		spec++;
	return (funcs);
}

t_conversion	*new_conversion(char *spec)
{
	t_conversion	*conv;

	conv = malloc(sizeof(t_conversion));
	conv->spec = spec;
	conv->functions = assemble_conversion_functions_for(spec);
	return (conv);
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
	return (len);
	while (IS_LENGTH_MODIFIER_CHR(str[len]))
		len++;
	while (IS_CONVERSION_TYPE_CHR(str[len]))
		len++;
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

t_token		*get_next_unexpanded_conversion(t_element_container *container)
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
	while ((token = get_next_unexpanded_conversion(container)))
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

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	t_doubly_linked_list	*token_list;
	char	*str;

	va_start(ap, format);
	token_list = expand_va_args(format, ap);
	va_end(ap);
	va_start(ap, format);
	apply_conversions(format, ap, token_list);
	va_end(ap);
	str = join_token_strings(token_list);
	delete_doubly_linked_list(token_list, &delete_token);
	ft_putstr(str);
	free(str);
	return (0);
}
