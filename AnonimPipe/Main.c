#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <malloc.h>

#define BUFFER_SIZE 120
#define PROCESS_PATH L"C:\\Users\\сергеичевад\\source\\repos\\AnonimPipe\\Debug\\SecondProcess.exe"

int main()
{
	system("chcp 1251>n");

	HANDLE hRead, hWrite;
	SECURITY_ATTRIBUTES securityAttributes;
	securityAttributes.bInheritHandle = TRUE;
	securityAttributes.lpSecurityDescriptor = NULL;
	securityAttributes.nLength = 0;

	BOOL pipe;
	pipe = CreatePipe(&hRead, &hWrite, &securityAttributes, BUFFER_SIZE);

	char** forWrite = calloc(4, sizeof(char*));
	
	forWrite[0] = calloc(10, sizeof(char));
	sprintf(forWrite[0], "%d", &hWrite);

	forWrite[1] = calloc(10, sizeof(char));
	forWrite[2] = calloc(10, sizeof(char));
	forWrite[3] = calloc(10, sizeof(char));
	
	forWrite[1] = "2";
	forWrite[2] = "8";
	forWrite[3] = "1";

	printf("%d %s\n", &hWrite, forWrite[0]);

	STARTUPINFO startInfo;
	PROCESS_INFORMATION processInformation;
	
	ZeroMemory(&startInfo, sizeof(STARTUPINFO));
	ZeroMemory(&processInformation, sizeof(PROCESS_INFORMATION));

	BOOL process;
	if (!CreateProcessA("C:\\Users\\сергеичевад\\source\\repos\\AnonimPipe\\Debug\\SecondProcess.exe", forWrite, NULL, &securityAttributes, TRUE, 0, NULL, NULL, &startInfo, &processInformation))
	{
		printf("Ошибка создания процесса %d\n", GetLastError());
	}
	WaitForSingleObject(processInformation.hProcess, INFINITE);
	CloseHandle(processInformation.hThread);
	CloseHandle(processInformation.hProcess);

	
}