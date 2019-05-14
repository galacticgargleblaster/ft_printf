/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:41:05 by student           #+#    #+#             */
/*   Updated: 2019/05/13 21:45:50 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conversion.h"
#include "assert.h"
#include <liblist.h>

/*
**	returns the conversion function corresponding to the provided
**	character and modifier characters
*/

void	*function_for_conversion(const t_conversion *c, const char conv)
{
	if (conv == 'c')
		return (&char_conversion);
	else if (conv == 's')
		return (&str_conversion);
	else if (conv == 'd' || conv == 'i')
	{
		if (c->length_modifier == LENGTH_MODIFIER_l)
			return (&long_conversion);
		else if (c->length_modifier == LENGTH_MODIFIER_ll)
			return (&long_conversion);
		else if (c->length_modifier == LENGTH_MODIFIER_h)
			return (&short_conversion);
		else if (c->length_modifier == LENGTH_MODIFIER_hh)
			return (&signed_char_conversion);
		else
			return (&int_conversion);
	}
	else if (conv == 'o' || conv == 'u')
	{
		if (c->length_modifier == LENGTH_MODIFIER_l)
			return (&ulong_conversion);
		else if (c->length_modifier == LENGTH_MODIFIER_ll)
			return (&ulong_conversion);
		else if (c->length_modifier == LENGTH_MODIFIER_h)
			return (&ushort_conversion);
		else if (c->length_modifier == LENGTH_MODIFIER_hh)
			return (&unsigned_char_conversion);
		else
			return (&uint_conversion);
	}
	else if (conv == 'x' || conv == 'X')
		return (&hex_conversion);
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
	if (format[len] == '.')
	{
		if  (IS_DIGIT(format[len + 1]))
			len += 1 + store_digits(format + len + 1, &conv->precision);
		else
		{
			conv->precision = 0;
			len++;
		}
	}
	len += store_length_modifier(&format[len], conv);
	conv->func = function_for_conversion(conv, format[len++]);
	conv->spec = ft_strndup(format, len);
	return len;
}

t_conversion	*new_conversion(const char *format)
{
	t_conversion	*conv;

	conv = malloc(sizeof(t_conversion));
	conv->spec = NULL;
	conv->func = NULL;
	conv->arg_number = 0;
	conv->min_field_width = -1;
	conv->precision = -1;
	conv->flags = 0;
	conv->length_modifier = 0;
	parse_conversion(format, conv);
	return (conv);
}

void	delete_conversion(t_conversion *conv)
{
	free (conv->spec);
	free (conv);
}
