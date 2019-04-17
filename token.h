/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 01:28:45 by student           #+#    #+#             */
/*   Updated: 2019/04/17 01:39:21 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <liblist.h>
# include "conversion.h"

/*
**	A token may be either a string literal or a conversion specification,
**	but not both.
**	If it's a string literal, then 'conv' is NULL
**	As soon as the conversion is done, 'conv' is freed and set to NULL.
*/

typedef struct	s_token
{
	char			*str;
	t_conversion	*conv;

}				t_token;

t_token					*new_token(void);
void					delete_token(void *token_ptr);
char					*join_token_strings(t_doubly_linked_list *token_list);
t_doubly_linked_list	*tokenize(const char *format);
t_token					*get_next_conversion(t_element_container *container);

#endif
