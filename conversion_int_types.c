/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_int_types.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:41:05 by student           #+#    #+#             */
/*   Updated: 2019/05/13 22:01:29 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>
#include "conversion.h"

char	*prepend_sign(const t_conversion *c, const int sign, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (sign < 0)
		tmp = ft_strjoin("-", str);
	else if (c->flags & FLAG_ALWAYS_INCLUDE_SIGN)
		tmp = ft_strjoin("+", str);
	else if ((c->flags & FLAG_SPACE_BEFORE) && is_signed_conversion(c))
		tmp = ft_strjoin(" ", str);
	if (tmp)
	{
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

int		is_signed_conversion(const t_conversion *c)
{
	int	i;

	i = 0;
	while (SIGNED_CONVERSION_CHRS[i])
	{
		if (ft_strchr(c->spec, SIGNED_CONVERSION_CHRS[i]))
			return (1);
		i++;
	}
	return (0);
}

int		field_width_was_specified(const t_conversion *c)
{
	return (c->min_field_width >= 0);
}

char	*apply_precision(const t_conversion *c, char *str)
{
	if (c->precision > 0 && ft_strlen(str) < (size_t)c->precision)
		str = pad_with_char(c->precision, PAD_LEFT, '0', str);
	else if (c->precision == 0)
	{
		free (str);
		str = ft_strnew(0);
	}
	return (str);
}

char	*handle_everything(const t_conversion *c, const int sign, char *str)
{
	char	pad_char;

	str = apply_precision(c, str);
	if (field_width_was_specified(c))
	{
		if (should_zero_pad(c))
			pad_char = '0';
		else
		{
			pad_char = ' ';
			str = prepend_sign(c, sign, str);
		}
		if (c->flags & FLAG_NEGATIVE_FIELD_WIDTH)
			str = pad_with_char(c->min_field_width, PAD_RIGHT, pad_char, str);
		else
			str = pad_with_char(c->min_field_width, PAD_LEFT, pad_char, str);
		if (should_zero_pad(c))
		{
			if (str[0] != '0')
				str = prepend_sign(c, sign, str);
			else
			{
				if (sign < 0)
					str[0] = '-';
				else if (c->flags & FLAG_ALWAYS_INCLUDE_SIGN)
					str[0] = '+';
				else if ((c->flags & FLAG_SPACE_BEFORE) && is_signed_conversion(c))
					str[0] = ' ';
			}
		}
	}
	else
	{
		str = prepend_sign(c, sign, str);
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


char	*signed_char_conversion(const t_conversion *c, va_list ap)
{
	int			arg;
	char		*str;

	(void)c;
	arg = (signed char)va_arg(ap, int);
	str = ft_itoa(arg);
	str = strip_leading_negative_sign(str);
	str = handle_everything(c, (arg >= 0 ? 0 : -1), str);
	return (str);
}

char	*short_conversion(const t_conversion *c, va_list ap)
{
	int		arg;
	char	*str;

	(void)c;
	arg = (signed short)va_arg(ap, int);
	str = ft_itoa(arg);
	str = strip_leading_negative_sign(str);
	str = handle_everything(c, (arg >= 0 ? 0 : -1), str);
	return (str);
}

char	*int_conversion(const t_conversion *c, va_list ap)
{
	int		arg;
	char	*str;

	arg = va_arg(ap, int);
	str = ft_itoa(arg);
	str = strip_leading_negative_sign(str);
	str = handle_everything(c, (arg >= 0 ? 0 : -1), str);
	return (str);
}

/*
**	On the lab macs, 'long' and 'long long' appear to refer to the same type
*/

char	*long_conversion(const t_conversion *c, va_list ap)
{
	long arg;
	char *str;

	(void)c;
	arg = va_arg(ap, long);
	str = ft_lltoa_base(arg, 10);
	str = strip_leading_negative_sign(str);
	str = handle_everything(c, (arg >= 0 ? 0 : -1), str);
	return (str);
}

char	*unsigned_char_conversion(const t_conversion *c, va_list ap)
{
	unsigned char	arg;
	char			*str;

	(void)c;
	arg = va_arg(ap, unsigned char);
	str = ft_itoa(arg);
	return (str);
}

char	*ushort_conversion(const t_conversion *c, va_list ap)
{
	unsigned short	arg;
	char			*str;

	(void)c;
	arg = va_arg(ap, unsigned short);
	str = ft_itoa(arg);
	return (str);
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
