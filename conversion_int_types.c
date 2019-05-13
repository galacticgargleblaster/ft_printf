/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_int_types.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:41:05 by student           #+#    #+#             */
/*   Updated: 2019/05/13 11:31:19 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>
#include "conversion.h"

char	*int_conversion(va_list ap, t_conversion *c)
{
	int		arg;
	char	*str;
	char	*tmp;

	arg = va_arg(ap, int);
	tmp = ft_itoa(arg);
	if (c->flags & FLAG_ALWAYS_INCLUDE_SIGN && arg >= 0)
	{
		str = ft_strjoin("+", tmp);
		free(tmp);
	}
	else
		str = tmp;
	return (str);
}

char	*long_conversion(va_list ap, t_conversion *c)
{
	long foo;

	(void)c;
	foo = va_arg(ap, long);
	return (ft_lltoa_base(foo, 10));
}

char	*uint_conversion(va_list ap, t_conversion *c)
{
	unsigned int foo;

	(void)c;
	foo = va_arg(ap, unsigned int);
	return (ft_lltoa_base(foo, 10));
}

char	*ulong_conversion(va_list ap, t_conversion *c)
{
	unsigned long foo;

	(void)c;
	foo = va_arg(ap, unsigned long);
	return (ft_ulltoa_base(foo, 10));
}
