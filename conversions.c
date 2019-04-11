/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:41:05 by student           #+#    #+#             */
/*   Updated: 2019/04/10 02:21:02 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define ALL_CONVERSION_CHRS "cspdiouxX"

#include <libft.h>
#include <ft_printf.h>

char	*int_conversion(va_list ap)
{
	int foo;
	foo = va_arg(ap, int);
	return (ft_itoa(foo));
}

void	*long_conversion(va_list ap)
{
	long foo;
	foo = va_arg(ap, long);
	return (ft_lltoa_base(foo, 10));
}

void	*uint_conversion(va_list ap)
{
	unsigned int foo;
	foo = va_arg(ap, unsigned int);
	return (ft_lltoa_base(foo, 10));
}

void	*ulong_conversion(va_list ap)
{
	unsigned long foo;
	foo = va_arg(ap, unsigned long);
	return (ft_ulltoa_base(foo, 10));
}

void 	*char_conversion(va_list ap)
{
	char	*foo;
	char	*str;
	int		tmp;

	tmp = va_arg(ap, int);
	foo = (char *)(&tmp);
	str = ft_strndup(foo, 1);
	return (str);
}

void	*str_conversion(va_list ap)
{
	(void)ap;
	ASSERT(1 == 0);
	return NULL;
}



/*
**	returns the conversion function corresponding to the provided
**	character
*/

void	*func_for_conv(char	flag)
{
	if (flag == 'c')
		return (&char_conversion);
	else if (flag == 's')
		return (&str_conversion);

	return (NULL);
}
