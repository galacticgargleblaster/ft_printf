/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 01:19:05 by student           #+#    #+#             */
/*   Updated: 2019/04/07 00:11:31 by student          ###   ########.fr       */
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
	char	*spec;
}				t_conversion;

typedef struct	s_flag
{
	char	*identifier;
}				t_flag;

#define ALL_CONVERSION_CHRS "cspdiouxX"
#define ALL_FLAG_CHRS "#0-+ "
#define ALL_MODIFIER_CHRS "hl"
#define SPEC_CHAR '%'

#define IS_FLAG_CHR(c) (ft_strchr(ALL_FLAG_CHRS, c) != NULL)
#define IS_CONVERSION_CHR(c) (ft_strchr(ALL_CONVERSION_CHRS, c) != NULL)
#define IS_MODIFIER_CHR(c) (ft_strchr(ALL_MODIFIER_CHRS, c) != NULL)


/*
**	A token may be either a string literal, or a conversion specification.
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

t_conversion	*new_conversion(char *spec)
{
	t_conversion	*conv;

	conv = malloc(sizeof(t_conversion));
	conv->spec = spec;
	return (conv);
}

/*
**	iterates over the format string, returning a t_token instance for every
**	section of the string starting with '%'
**	
**	Find any '%' that isn't followed by another '%', and read until the
**	entire format spec is consumed.  This means eating flags, conversion chars, 
*/

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list		args;
	t_doubly_linked_list	*token_list;
	t_token		*token;
	char		*tmp;
	size_t		len;

	token_list = new_doubly_linked_list();
	va_start(args, format);
	while (*format)
	{
		if (*format == SPEC_CHAR)
		{
			if (*(format + 1) == SPEC_CHAR)
				format++;
			else
			{
				token = new_token();
				len = 1;
				while (IS_FLAG_CHR(format[len]))
					len++;
				while (IS_CONVERSION_CHR(format[len]))
					len++;
				while (IS_MODIFIER_CHR(format[len]))
					len++;
				token->conv = new_conversion(ft_strndup(format, len));
				list_push_tail(token_list, token);
				format += len;
				continue;
			}
		}
		token = new_token();
		tmp = ft_strchr(format, SPEC_CHAR);
		if (tmp == NULL)
			len = ft_strlen(format);
		else
			len = tmp - format;
		token->str = ft_strndup(format, len);
		list_push_tail(token_list, token);
		format += len;
		(void)str;
		(void)size;
	}
	va_end(args);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	char	*printme;

	printme = ft_strnew(ft_strlen(format));
	ft_snprintf(printme, ft_strlen(format), format);
	return (0);
}


/*

		c = va_arg(ap, int);
		printf("char %c\n", c);
		break;
	case 's':                   
		s = va_arg(ap, char *);
		printf("string %s\n", s);
		break;
	case 'p':
		p = va_arg(ap, void *);
		printf("pointer %p\n", p);
	case 'd':                  
		d = va_arg(ap, int);
		printf("int %d\n", d);
		break;

			*/