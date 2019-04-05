#include "ft_printf.h"

int main()
{
	printf("%s\n%s\n", "foo");
	ft_printf("%s\n%s\n", "foo");
	ft_printf("d", 51);
	ft_printf("c", 23);
	return (0);
}
