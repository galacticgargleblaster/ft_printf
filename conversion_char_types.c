/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_char_types.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:41:05 by student           #+#    #+#             */
/*   Updated: 2019/05/13 10:31:42 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#include "assert.h"

void 	*char_conversion(va_list ap)
{
	int		tmp;
	char	*str;

	tmp = va_arg(ap, int);
	str = ft_strndup((char *)(&tmp), 1);
	return (str);
}

void	*str_conversion(va_list ap)
{
	return ft_strdup(va_arg(ap, char *));
}

void	*hex_conversion(va_list ap)
{
	(void)ap;
	return 0;
}
