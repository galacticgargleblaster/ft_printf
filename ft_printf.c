/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 01:19:05 by student           #+#    #+#             */
/*   Updated: 2019/04/06 19:49:45 by student          ###   ########.fr       */
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
	char	*identifier;
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

typedef struct	s_token
{
	char	*str;
}				t_token;


/*
**	iterates over the format string, returning a t_token instance for every
**	section of the string starting with '%'
*/

t_token		*get_next_token(char **fmt_str_ptr)
{
	t_token	*token;
	size_t	token_size;
	char	*next_spec_char;

	token = malloc(sizeof(t_token));
	if ((next_spec_char = ft_strchr(*fmt_str_ptr, SPEC_CHAR)))
		token_size =  next_spec_char - *fmt_str_ptr;
	else
		token_size = ft_strlen(*fmt_str_ptr);
	token->str = ft_strndup(*fmt_str_ptr, token_size);
	*fmt_str_ptr += token_size;
	return (token);
}

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list		args;
	t_doubly_linked_list	*token_list;
	t_token		*token;
	char		*fmt;

	fmt = ft_strdup(format);
	token_list = new_doubly_linked_list();
	va_start(args, format);
	while (*format)
		token = get_next_token((char **)&format);
		if (token)
			list_push_tail(token_list, token);
		(void)str;
		(void)size;
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