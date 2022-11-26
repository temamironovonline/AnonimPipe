#include <stdio.h>
#include <Windows.h>

int main(int argc, char** argv)
{

	printf("%d\n", argc);

	PHANDLE hWrite;

	hWrite = (HANDLE)atoi(argv[1]);

	printf("%d", hWrite);

	printf("Подключено\n");
	
	system("pause");

	return 0;
}