#include "ft_printf.h"
#include <stdio.h>

#define ASSERT_STR_EQUAL(a, b) (ASSERT(ft_strcmp(a, b) == 0))

#define BUF_SIZE 1000

#define COMPARE(...)\
{\
	char *str_a = malloc(BUF_SIZE);\
	char *str_b = malloc(BUF_SIZE);\
	ft_snprintf(str_a, BUF_SIZE, __VA_ARGS__);\
	snprintf(str_b, BUF_SIZE, __VA_ARGS__);\
	if (ft_strcmp(str_a, str_b))\
	{\
		ft_putstr("FAIL:\n");\
		ft_xxd(str_a, ft_strlen(str_a));\
		ft_xxd(str_b, ft_strlen(str_b));\
	}\
	else\
		ft_putstr("OK\n");\
	ft_putstr("\n");\
	free(str_a);\
	free(str_b);\
}

int main()
{
	int foo = 50;
	COMPARE("foo %d, %d, %d", foo, 200, -10);
}
