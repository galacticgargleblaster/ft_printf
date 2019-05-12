/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:41:05 by student           #+#    #+#             */
/*   Updated: 2019/05/11 21:55:19 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conversion.h"
#include "assert.h"
#include <liblist.h>

/*
**	returns the conversion function corresponding to the provided
**	character
*/

void	*func_for_conv(char	conv)
{
	if (conv == 'c')
		return (&char_conversion);
	else if (conv == 's')
		return (&str_conversion);
	else if (conv == 'd')
		return (&int_conversion);
	else if (conv == 'u')
		return (&uint_conversion);
	else
		ASSERT(0);
	return (NULL);
}

void			store_flag(const char flag, t_conversion *conv)
{
	if (flag == '#')
		conv->flags |= FLAG_ALTERNATE_FORM;
	else if (flag == '0')
		conv->flags |= FLAG_ZERO_PADDING;
	else if (flag == '-')
		conv->flags |= FLAG_NEGATIVE_FIELD_WIDTH;
	else if (flag == ' ')
		conv->flags |= FLAG_SPACE_BEFORE;
	else if (flag == '+')
		conv->flags |= FLAG_ALWAYS_INCLUDE_SIGN;
	else
		ASSERT(IS_FLAG_CHR(flag));
}

size_t			store_digits(const char *ascii, int *location)
{
	size_t	len;
	char	*tmp;

	*location = ft_atoi(ascii);
	tmp = ft_itoa(*location);
	len = ft_strlen(tmp);
	free(tmp);
	return (len);
}

size_t			store_length_modifier(const char *format, t_conversion *conv)
{
	if (format[0] == 'h')
	{
		if (format[1] == 'h')
		{
			conv->length_modifier |= LENGTH_MODIFIER_hh;
			return (2);
		}
		else
		{
			conv->length_modifier |= LENGTH_MODIFIER_h;
			return (1);
		}
	}
	else if (format[0] == 'l')
	{
		if (format[1] == 'l')
		{
			conv->length_modifier |= LENGTH_MODIFIER_ll;
			return (2);
		}
		else
		{
			conv->length_modifier |= LENGTH_MODIFIER_l;
			return (1);
		}
	}
	return (0);
}

size_t			parse_conversion(const char *format, t_conversion *conv)
{
	size_t	len;

	len = 0;
	ASSERT(format[len++] == '%')
	while (IS_FLAG_CHR(format[len]))
		store_flag(format[len++], conv);
	if (IS_DIGIT(format[len]))
		len += store_digits(format + len, &conv->min_field_width);
	if (format[len] == '.' && (IS_DIGIT(format[++len])))
		len += store_digits(format + len, &conv->precision);
	len += store_length_modifier(&format[len], conv);
	conv->func = func_for_conv(format[len++]);
	conv->spec = ft_strndup(format, len);
	return len;
}

t_conversion	*new_conversion(const char *format)
{
	t_conversion	*conv;

	conv = malloc(sizeof(t_conversion));
	parse_conversion(format, conv);
	return (conv);
}

void	delete_conversion(t_conversion *conv)
{
	free (conv->spec);
	free (conv);
}
