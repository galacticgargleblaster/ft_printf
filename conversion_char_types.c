/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_char_types.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:41:05 by student           #+#    #+#             */
/*   Updated: 2019/05/13 11:24:21 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#include "assert.h"
#include "conversion.h"

char	*char_conversion(va_list ap, t_conversion *c)
{
	int		tmp;
	char	*str;

	(void)c;
	tmp = va_arg(ap, int);
	str = ft_strndup((char *)(&tmp), 1);
	return (str);
}

char	*str_conversion(va_list ap, t_conversion *c)
{
	char	*str;
	char	*tmp;
	ssize_t	len;

	str = ft_strdup(va_arg(ap, char *));
	if (c->min_field_width >= 0)
	{
		len = c->min_field_width - ft_strlen(str);
		tmp = ft_strnew(len);
		ft_memset(tmp, ' ', len);
		tmp = ft_strjoin(tmp, str);
		free(str);
		str = tmp;
	}
	return str;
}

char	*hex_conversion(va_list ap, t_conversion *c)
{
	(void)ap;
	(void)c;
	return 0;
}
