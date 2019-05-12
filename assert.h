/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 16:03:06 by student           #+#    #+#             */
/*   Updated: 2019/05/11 16:03:53 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSERT_H
# define ASSERT_H

void	print_assertion_fail(char *cond, char *fname, int lineno);
# define _P_FAIL_MSG(cond) { print_assertion_fail(#cond, __FILE__, __LINE__); }
# define ASSERT(cond) { if (!(cond)) { _P_FAIL_MSG(cond); exit(-1); } }

#endif
