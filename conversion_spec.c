/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_spec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 01:36:15 by student           #+#    #+#             */
/*   Updated: 2019/04/17 01:37:49 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conversion.h"

size_t	length_of_str_to_next_spec_char_or_null(const char *str)
{
	size_t	len;
	char	*tmp;

	tmp = ft_strchr(str, SPEC_CHR);
	if (tmp == NULL)
		len = ft_strlen(str);
	else
		len = tmp - str;
	return (len);
}
