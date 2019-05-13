/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:41:05 by student           #+#    #+#             */
/*   Updated: 2019/05/13 12:10:59 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conversion.h"
#include "assert.h"

char	*expand_field_width(const t_conversion *c, char *str)
{
	char	*tmp;
	ssize_t	len;

	if (c->min_field_width >= 0)
	{
		len = c->min_field_width - ft_strlen(str);
		if (len > 0)
		{
			tmp = ft_strnew(len);
			ft_memset(tmp, ' ', len);
			tmp = ft_strjoin(tmp, str);
			free(str);
			str = tmp;
		}
	}
	return str;
}
