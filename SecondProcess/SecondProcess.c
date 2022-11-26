#include <stdio.h>
#include <Windows.h>

int main(int argc, char** argv)
{

	//printf("%s\n", argv[0]);
	//printf("%s\n", argv[1]);
	//printf("%s\n", argv[2]);

	PHANDLE hWrite;

	hWrite = (HANDLE)atoi(argv[1]);

	printf("%d", hWrite);

	printf("Подключено\n");
	
	system("pause");

	return 0;
}