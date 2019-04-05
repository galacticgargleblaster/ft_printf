/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 01:19:05 by student           #+#    #+#             */
/*   Updated: 2019/04/04 21:49:06 by student          ###   ########.fr       */
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

#define CONVERSIONS "cspdiouxX"
#define FLAGS ""

struct	s_generic
{
	char	*identifier;
}

union
{
	struct s_generic s_conversion;
	struct s_generic s_flag;
}

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list	args;
	va_start(args, format);
	va_end(args);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int d;
	char c, *s;
	void *p;

	va_start(ap, format);
	while (*format)
		if (*format == '%')
		{
			format++;
			if (*format == '%')
			{
				ft_strjoin()
				return ;
			}
			else
			{

			}

		}
		case 'c':                       /* char */
			/* Note: char is promoted to int. */
			c = va_arg(ap, int);
			printf("char %c\n", c);
			break;
		case 's':                       /* string */
			s = va_arg(ap, char *);
			printf("string %s\n", s);
			break;
		case 'p':
			p = va_arg(ap, void *);
			printf("pointer %p\n", p);
		case 'd':                       /* int */
			d = va_arg(ap, int);
			printf("int %d\n", d);
			break;

		}
	va_end(ap);
	return (0);
}