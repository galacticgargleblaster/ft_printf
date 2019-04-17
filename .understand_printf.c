#include <stdio.h>

int main()
{
	printf("%1$d, %1$c\n", 35);
	printf("%#x\n", 35);
	printf("%x\n", 35);
	
	printf("%#x\n", -35);
	printf("%x\n", -35);

	printf("%#x\n", -1);
	printf("%x\n", -1);

	printf("%-s\n", "foo");
	printf("%-d\n", 40);
	printf("% d\n", -40);
	printf("% d\n", 40);
	
	printf("%+d\n", -40);
	printf("%+d\n", 40);
	
	printf("%#--++ #x\n", 35);
	printf("%#x\n", 35);
	printf("%x\n", 35);

	printf("%cc\n", 39);
	printf("%llu\n", 39);

	printf("%3.2f\n", 1234.1234);
	printf("%3s", "foobar\n");
	// printf("%3.2s", "foobar\n");
	printf("%#a\n", 1);
	printf("aaa%\n");

	return (0);
}
