/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:41:05 by student           #+#    #+#             */
/*   Updated: 2019/04/14 00:40:11 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define ALL_CONVERSION_CHRS "cspdiouxX"

#include "conversion.h"
#include <liblist.h>

/*
**	returns the conversion function corresponding to the provided
**	character
*/

void	*func_for_conv(char	flag)
{
	if (flag == 'c')
		return (&char_conversion);
	else if (flag == 's')
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