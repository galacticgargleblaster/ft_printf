/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 02:00:07 by student           #+#    #+#             */
/*   Updated: 2019/05/11 21:53:17 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CONVERSION_H
# define CONVERSION_H

# include <stdarg.h>
# include <liblist.h>
# include <libft.h>

# define SPEC_CHR '%'

# define ALL_CONVERSION_CHRS "cspdiouxX"
# define ALL_FLAG_CHRS "#0- +"
# define FLAG_ALTERNATE_FORM		(1 << 0)
# define FLAG_ZERO_PADDING			(1 << 1)
# define FLAG_NEGATIVE_FIELD_WIDTH	(1 << 2)
# define FLAG_SPACE_BEFORE			(1 << 3)
# define FLAG_ALWAYS_INCLUDE_SIGN	(1 << 4)

# define ALL_LENGTH_MODIFIER_CHRS "hl"
# define LENGTH_MODIFIER_hh			(1 << 0)
# define LENGTH_MODIFIER_h			(1 << 1)
# define LENGTH_MODIFIER_l			(1 << 2)
# define LENGTH_MODIFIER_ll			(1 << 3)

# define IS_FLAG_CHR(c) (ft_memchr(ALL_FLAG_CHRS, c, ft_strlen(ALL_FLAG_CHRS)) != NULL)
# define IS_CONVERSION_TYPE_CHR(c) (ft_memchr(ALL_CONVERSION_CHRS, c, ft_strlen(ALL_CONVERSION_CHRS)) != NULL)

# define _ISLMC(c) (ft_memchr(ALL_LENGTH_MODIFIER_CHRS, c, ft_strlen(ALL_LENGTH_MODIFIER_CHRS)) != NULL)
# define IS_LENGTH_MODIFIER_CHR(c) _ISLMC(c)


/*
**	spec - print format specifier string (e.g. "%d")
**	functions - list of functions that when applied in order, transform
**		a chunk of va_args memory into a string of the specified format
*/

typedef struct	s_conversion
{
	char					*spec;
	char					*(*func)();
	int						arg_number;
	int						min_field_width;
	int						precision;
	int						flags;
	int						length_modifier;
}				t_conversion;

void	*func_for_conv(char	conv);
void	*func_for_flag(char	flag);
void	*char_conversion(va_list ap);
void	*str_conversion(va_list ap);
void	*int_conversion(va_list ap);
void	*uint_conversion(va_list ap);

t_conversion	*new_conversion(const char *format);
void			delete_conversion(t_conversion *conv);
size_t			length_of_str_to_next_spec_char_or_null(const char *str);

#endif
