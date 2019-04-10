/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 13:59:48 by student           #+#    #+#             */
/*   Updated: 2019/04/09 23:03:04 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	A quick implementation of the type of thing you'll find in <assert.h>
*/

void	print_assertion_fail(char *cond, char *fname, int lineno)
{
	char	*lineno_str;
	char	*tmp_a;
	char	*tmp_b;

	tmp_a = ft_strjoin("assertion failed: \"", cond);
	tmp_b = ft_strjoin(tmp_a, "\" ");
	free(tmp_a);
	tmp_a = ft_strjoin(tmp_b, fname);
	free(tmp_b);
	tmp_b = ft_strjoin(tmp_a, ":");
	free(tmp_a);
	lineno_str = ft_itoa(lineno);
	tmp_a = ft_strjoin(tmp_b, lineno_str);
	free(lineno_str);
	free(tmp_b);
	tmp_b = ft_strjoin(tmp_a, "\n");
	free(tmp_a);
	ft_putstr_fd(tmp_b, 2);
	free(tmp_b);
}
