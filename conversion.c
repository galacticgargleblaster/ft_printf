/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:41:05 by student           #+#    #+#             */
/*   Updated: 2019/04/17 01:40:10 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conversion.h"
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

	return (NULL);
}

/*
**	Given a spec, return a list of functions, that when applied in the order
**	they appear in the list, return a string in the specified format
*/

t_doubly_linked_list	*assemble_conversion_functions_for(char *spec)
{
	t_doubly_linked_list	*funcs;

	funcs = new_doubly_linked_list();
	while (IS_FLAG_CHR(*spec))
	{
		list_push_head(funcs, func_for_flag(*spec));
		spec++;
	}
	while (IS_CONVERSION_TYPE_CHR(*spec))
	{
		list_push_head(funcs, func_for_conv(*spec));
		spec++;
	}
	while (IS_LENGTH_MODIFIER_CHR(*spec))
		spec++;
	return (funcs);
}

t_conversion	*new_conversion(char *spec)
{
	t_conversion	*conv;

	conv = malloc(sizeof(t_conversion));
	conv->spec = spec;
	conv->functions = assemble_conversion_functions_for(spec);
	return (conv);
}

void	delete_conversion(t_conversion *conv)
{
	free (conv);
}

/*
**	Given a spec (a string beginning with single '%'),
**	return the length in characters of the entire conversion spec
*/

size_t		conversion_spec_length(const char *str)
{
	size_t	len;

	len = 1;
	while (IS_FLAG_CHR(str[len]))
		len++;
	while (IS_DIGIT(str[len]))
		len++;
	while (str[len] == '.')
		len++;
	while (IS_DIGIT(str[len]))
		len++;
	while (IS_LENGTH_MODIFIER_CHR(str[len]))
		len++;
	while (IS_CONVERSION_TYPE_CHR(str[len]))
		len++;
	return (len);
}