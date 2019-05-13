/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:41:05 by student           #+#    #+#             */
/*   Updated: 2019/05/13 13:36:44 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conversion.h"
#include "assert.h"

char	*pad_with_char(const int width, const int padding_direction, const char c, char *str)
{
	char	*tmp;
	char	*padding;
	ssize_t	len;

	len = width - ft_strlen(str);
	if (len > 0)
	{
		padding = ft_strnew(len);
		ft_memset(padding, c, len);
		if (padding_direction == PAD_RIGHT)
			tmp = ft_strjoin(str, padding);
		else if (padding_direction == PAD_LEFT)
			tmp = ft_strjoin(padding, str);
		else
			ASSERT(0);
		free(padding);
		free(str);
		str = tmp;
	}
	return (str);
}

char	*expand_field_width(const t_conversion *c, char *str)
{
	if (c->min_field_width >= 0)
	{
		if (c->flags & FLAG_NEGATIVE_FIELD_WIDTH)
			str = pad_with_char(c->min_field_width, PAD_RIGHT, ' ', str);
		else
			str = pad_with_char(c->min_field_width, PAD_LEFT, ' ', str);
	}
	return str;
}
