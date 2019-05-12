/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_int_types.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:41:05 by student           #+#    #+#             */
/*   Updated: 2019/05/11 16:20:55 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdarg.h>

char	*int_conversion(va_list ap)
{
	int foo;
	foo = va_arg(ap, int);
	return (ft_itoa(foo));
}

char	*long_conversion(va_list ap)
{
	long foo;
	foo = va_arg(ap, long);
	return (ft_lltoa_base(foo, 10));
}

char	*uint_conversion(va_list ap)
{
	unsigned int foo;
	foo = va_arg(ap, unsigned int);
	return (ft_lltoa_base(foo, 10));
}

char	*ulong_conversion(va_list ap)
{
	unsigned long foo;
	foo = va_arg(ap, unsigned long);
	return (ft_ulltoa_base(foo, 10));
}
