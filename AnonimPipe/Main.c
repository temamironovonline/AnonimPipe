#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <malloc.h>

#define BUFFER_SIZE 120
#define PROCESS_PATH "C:\\Users\\сергеичевад\\Source\\Repos\\AnonimPipe\\x64\\Debug\\SecondProcess.exe"

struct structAnswer
{
	char* text;
	float discriminant;
	int countCorners;
	float x1;
	float x2;
};

int main()
{
	system("chcp 1251>n");

	HANDLE hRead, hWrite;
	SECURITY_ATTRIBUTES securityAttributes;
	securityAttributes.bInheritHandle = TRUE;
	securityAttributes.lpSecurityDescriptor = NULL;
	securityAttributes.nLength = 120;

	BOOL pipe;
	pipe = CreatePipe(&hRead, &hWrite, &securityAttributes, BUFFER_SIZE);


	int countOfSymbols = 0;
	WriteFile(hWrite, "2 12 1", 7, countOfSymbols, NULL);
	char* forWrite = calloc(12, sizeof(char));
	sprintf(forWrite, "%d", hWrite);

	char* forRead = calloc(12, sizeof(char));
	sprintf(forRead, "%d", hRead);

	char* forAll = calloc(26, sizeof(char));
	snprintf(forAll, 26, "%s %s", forRead, forWrite);

	char* buffer = calloc(120, sizeof(char));

	printf("%d %d %s\n", hRead, hWrite, buffer);
	STARTUPINFO startInfo;
	PROCESS_INFORMATION processInformation;

	startInfo.hStdInput = hRead;
	startInfo.hStdOutput = hWrite;

	ZeroMemory(&startInfo, sizeof(STARTUPINFO));
	ZeroMemory(&processInformation, sizeof(PROCESS_INFORMATION));

	struct structAnswer* forAnswer = calloc(1, sizeof(struct structAnswer));
	struct structAnswer forAnswer2;
	LPSTR a;
	BOOL process;
	if (!CreateProcessA(PROCESS_PATH, forAll, &securityAttributes, &securityAttributes, TRUE, 0, NULL, NULL, &startInfo, &processInformation))
	{
		printf("Ошибка создания процесса %d\n", GetLastError());
	}

	Sleep(1000);

	ReadFile(hRead, buffer, 120, countOfSymbols, NULL);
	CloseHandle(hRead);
	forAnswer = (struct structAnswer*)atoi(buffer);
	printf("%d %s", forAnswer, buffer);
	//forAnswer2 = *forAnswer;

	WaitForSingleObject(processInformation.hProcess, INFINITE);
	
	//system("pause");
	CloseHandle(processInformation.hThread);
	CloseHandle(processInformation.hProcess);


}