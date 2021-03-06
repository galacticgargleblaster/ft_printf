/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_char_types.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:41:05 by student           #+#    #+#             */
/*   Updated: 2019/05/13 11:55:55 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#include "assert.h"
#include "conversion.h"

char	*char_conversion(const t_conversion *c, va_list ap)
{
	int		tmp;
	char	*str;

	(void)c;
	tmp = va_arg(ap, int);
	str = ft_strndup((char *)(&tmp), 1);
	return (str);
}

char	*str_conversion(const t_conversion *c, va_list ap)
{
	char	*str;

	(void)c;
	str = ft_strdup(va_arg(ap, char *));
	str = expand_field_width(c, str);
	return str;
}

char	*hex_conversion(const t_conversion *c, va_list ap)
{
	(void)ap;
	(void)c;
	return 0;
}
