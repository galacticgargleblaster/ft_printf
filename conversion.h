/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 02:00:07 by student           #+#    #+#             */
/*   Updated: 2019/04/14 00:36:04 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CONVERSION_H
# define CONVERSION_H

#include <stdarg.h>

/*
**	spec - print format specifier string (e.g. "%d")
**	functions - list of functions that when applied in order, transform
**		a chunk of va_args memory into a string of the specified format
*/

typedef struct	s_conversion
{
	char					*spec;
	t_doubly_linked_list	*functions;
}				t_conversion;

void	*func_for_conv(char	flag);
void	*char_conversion(va_list ap);
void	*str_conversion(va_list ap);

#endif
