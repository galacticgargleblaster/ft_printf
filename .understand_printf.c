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
	return (0);
}
