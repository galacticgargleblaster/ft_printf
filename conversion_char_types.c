/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_char_types.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:41:05 by student           #+#    #+#             */
/*   Updated: 2019/04/13 23:12:22 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>

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
