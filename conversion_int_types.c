/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_int_types.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:41:05 by student           #+#    #+#             */
/*   Updated: 2019/05/13 20:08:31 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>
#include "conversion.h"

char	*prepend_sign(const t_conversion *c, const int arg, char *str)
{
	char	*tmp;

	if (arg < 0)
	{
		tmp = ft_strjoin("-", str);
		free(str);
		str = tmp;
	}
	else if (c->flags & FLAG_ALWAYS_INCLUDE_SIGN && arg >= 0)
	{
		tmp = ft_strjoin("+", str);
		free(str);
		str = tmp;
	}
	return (str);
}

/*
**	If a precision is given with a numeric conversion (d, i, o, u, i, x, and X), the 0 flag is ignored.
*/

int		should_zero_pad(const t_conversion *c)
{
	return ((c->flags & FLAG_ZERO_PADDING) && c->precision < 0);
}

char	*handle_everything(const t_conversion *c, const int arg, char *str)
{
	char	pad_char;

	if (c->precision >= 0 && ft_strlen(str) < (size_t)c->precision)
		str = pad_with_char(c->precision, PAD_LEFT, '0', str);

	if (c->min_field_width >= 0)
	{
		if (should_zero_pad(c))
			pad_char = '0';
		else
		{
			pad_char = ' ';
			str = prepend_sign(c, arg, str);
		}
		if (c->flags & FLAG_NEGATIVE_FIELD_WIDTH)
			str = pad_with_char(c->min_field_width, PAD_RIGHT, pad_char, str);
		else
			str = pad_with_char(c->min_field_width, PAD_LEFT, pad_char, str);
		if (should_zero_pad(c))
		{
			if (str[0] != '0')
				str = prepend_sign(c, arg, str);
			else
			{
				if (arg < 0)
					str[0] = '-';
				else if (c->flags & FLAG_ALWAYS_INCLUDE_SIGN)
					str[0] = '+';
			}
		}
	}
	else
	{
		str = prepend_sign(c, arg, str);
	}
	return (str);
}

char	*strip_leading_negative_sign(char *str)
{
	char	*tmp;

	if (ft_strchr(str, '-'))
	{
		tmp = str;
		str = ft_strdup(str + 1);
		free(tmp);
	}
	return (str);
}

char	*int_conversion(const t_conversion *c, va_list ap)
{
	int		arg;
	char	*str;

	arg = va_arg(ap, int);
	str = ft_itoa(arg);
	str = strip_leading_negative_sign(str);
	str = handle_everything(c, arg, str);
	return (str);
}

char	*long_conversion(const t_conversion *c, va_list ap)
{
	long foo;

	(void)c;
	foo = va_arg(ap, long);
	return (ft_lltoa_base(foo, 10));
}

char	*uint_conversion(const t_conversion *c, va_list ap)
{
	unsigned int foo;

	(void)c;
	foo = va_arg(ap, unsigned int);
	return (ft_lltoa_base(foo, 10));
}

char	*ulong_conversion(const t_conversion *c, va_list ap)
{
	unsigned long foo;

	(void)c;
	foo = va_arg(ap, unsigned long);
	return (ft_ulltoa_base(foo, 10));
}
