#include "ft_printf.h"

int main()
{
	printf("%s\n%s\n", "foo");
	ft_printf("%s\n%s\n", "foo");
	ft_printf("d", 51);
	ft_printf("c", 23);
	return (0);
}



/*
**	va_arg is function-like macro that takes a type as an argument.
here's a possible implementation:

typedef unsigned char *va_list;
#define va_start(list, param) (list = (((va_list)&param) + sizeof(param)))
#define va_arg(list, type)    (*(type *)((list += sizeof(type)) - sizeof(type)))
*/


#warning "Foo!"

/*
** should be able to do some preprocessor checks on the contents of the string

I'm really curious where:
test.c:5:2: note: include the header <stdio.h> or explicitly provide a declaration for 'printf'
test.c:5:15: warning: more '%' conversions than data arguments [-Wformat]
        printf("%s\n%s\n", "foo");

comes from.

So I'm compiling gcc from source using the instructions here:
https://solarianprogrammer.com/2017/05/21/compiling-gcc-macos/

I should be able to search the gcc source for "conversions than data arguments"
(can't find that exact string..., need to finish compiling gcc to see what warning it gives)
in any case, I'm starting to think that this behavior is implemented within the compiler
*/
