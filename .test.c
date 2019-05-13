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
	COMPARE("%%u 0000042 == |%u|\n", 0000042);
	int n = 50;
	COMPARE("foo %d, %d, %d", n, 200, -10);
	COMPARE("%u\n", 2000);
	COMPARE("%s\t%s", "before", "after");
	COMPARE("Hello, %s.", "ftpf")
	COMPARE("%c", 37);
	COMPARE("%32s", "abc");
}
