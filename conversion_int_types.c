/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_int_types.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:41:05 by student           #+#    #+#             */
/*   Updated: 2019/05/13 13:38:54 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>
#include "conversion.h"

char	*handle_sign(const t_conversion *c, const int arg, char *str)
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

char	*handle_precision(const t_conversion *c, const int arg, char *str)
{
	(void) arg;
	if (c->precision >= 0 && ft_strlen(str) < (size_t)c->precision)
		str = pad_with_char(c->precision, PAD_LEFT, '0', str);
	return (str);
}

char	*int_conversion(const t_conversion *c, va_list ap)
{
	int		arg;
	char	*str;
	char	*tmp;

	arg = va_arg(ap, int);
	str = ft_itoa(arg);
	if (ft_strchr(str, '-'))
	{
		tmp = str;
		str = ft_strdup(str + 1);
		free(tmp);
	}
	str = handle_precision(c, arg, str);
	str = handle_sign(c, arg, str);
	str = expand_field_width(c, str);
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
