#include "ft_printf.h"
#include <stdio.h>

#define ASSERT_STR_EQUAL(a, b) (ASSERT(ft_strcmp(a, b) == 0))

#define BUF_SIZE 1000

void compare_and_print_result(char *str_a, char *str_b)
{
	if (ft_strcmp(str_a, str_b))
	{
		ft_putstr("FAIL:\n");
		ft_xxd(str_a, ft_strlen(str_a));
		ft_xxd(str_b, ft_strlen(str_b));
	}
	else
	{
		ft_putstr("OK\t -- ");
		ft_putstr(str_a);
		ft_putstr("\n");
	}
}

#define COMPARE(...)\
{\
	char *str_a = malloc(BUF_SIZE);\
	char *str_b = malloc(BUF_SIZE);\
	ft_snprintf(str_a, BUF_SIZE, __VA_ARGS__);\
	snprintf(str_b, BUF_SIZE, __VA_ARGS__);\
	compare_and_print_result(str_a, str_b);\
	free(str_a);\
	free(str_b);\
}

int main()
{
	COMPARE("%07d", -54);
	COMPARE("%05d", 43);
	COMPARE("%.6d", -3);
	COMPARE("%.5d", 2);
	COMPARE("%-7d", 33);
	COMPARE("%4d", 94827);
	COMPARE("%7d", 33);
	COMPARE("%+d", 5);
	COMPARE("%%u 0000042 == |%u|", 0000042);
	COMPARE("%%u \t == |%u|", '\t');
	COMPARE("%%u Lydie == |%u|", 'L'+'y'+'d'+'i'+'e');
	int n = 50;
	COMPARE("foo %d, %d, %d", n, 200, -10);
	COMPARE("%u", 2000);
	COMPARE("%s\t%s", "before", "after");
	COMPARE("Hello, %s.", "ftpf")
	COMPARE("%c", 37);
	COMPARE("%32s", "abc");
}
