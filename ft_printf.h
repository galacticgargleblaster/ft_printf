/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 01:12:42 by student           #+#    #+#             */
/*   Updated: 2019/04/17 03:06:53 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <libft.h>
# include <liblist.h>
# include "conversion.h"
# include "token.h"

/*
**				WHY MAKE YOUR OWN PRINTF?
**
**	- It's a good way to dig into implementation details of:
**		- gcc/clang
**		- x86_64 va_arg
**			- https://www.stackoverflow.com/q/4958384/
**	- gain deeper appreciation for Python's fstrings
**	- It's an OK way to practice organizing a larger C program
**
**				WHY NOT MAKE YOUR OWN PRINTF?
**
**	- clang and gcc both implement the -Wformat flag.  When this flag is set,
**		the compiler warns about formatting issues specific to a set of C
**		standard library functions (printf, scanf, ...).  This behavior isn't
**		extensible without modifying the C compiler.
**		(more: https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html)
**		example:
**	test.c:5:15: warning: more '%' conversions than data arguments [-Wformat]
**		printf("%s\n%s\n", "foo");
**
**	- you could be doing something more creative, like trying to write a
**		program that uses every syscall shown by `man syscall` to print a
**		nyancat.
*/


void	print_assertion_fail(char *cond, char *fname, int lineno);
# define _P_FAIL_MSG(cond) { print_assertion_fail(#cond, __FILE__, __LINE__); }
# define ASSERT(cond) { if (!(cond)) { _P_FAIL_MSG(cond); exit(-1); } }


/*
**	printf("SPEC text text SPEC")
**	where SPEC takes the form:
**		%(FLAG)*(FIELD_WIDTH)*(PRECISION)*CONVERSION_SPECIFIER
*/

int	ft_printf(const char *format, ...);
int	ft_fprintf(int fd, const char *format, ...);
int	ft_snprintf(char *str, size_t size, const char *format, ...);

#endif
