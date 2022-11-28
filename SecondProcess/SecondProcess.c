#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <malloc.h>

#define BUFFER_SIZE 12

void decisionCompleteEquation(float*, struct structAnswer);
void decisionIncompleteEquation(float*, struct structAnswer);
void writeResultToFile(struct structAnswer);

struct structAnswer
{
	char* text;
	float discriminant;
	int countCorners;
	float x1;
	float x2;
};

HANDLE hRead, hWrite;

int main(int argc, char** argv)
{
	printf("����������\n");

	hRead = (HANDLE)atoi(argv[0]);
	hWrite = (HANDLE)atoi(argv[1]);

	char* buffer = calloc(120, sizeof(char));
	int countSymbols = 0;
	ReadFile(hRead, buffer, 120, countSymbols, NULL);
	CloseHandle(hRead);

	char* forSplit;
	float* argumentsForCalculation = calloc(3, sizeof(float));
	forSplit = strtok(buffer, " ");

	for (int i = 0; forSplit != NULL; i++)
	{
		argumentsForCalculation[i] = atof(forSplit);
		forSplit = strtok(NULL, " ");
	}

	free(buffer);
	free(forSplit);

	struct structAnswer answer = {
	answer.text = "",
		answer.discriminant = 0,
		answer.countCorners = 0,
		answer.x1 = 0,
		answer.x2 = 0
	};

	if (argumentsForCalculation[0] == 0)
	{
		answer.text = "��������� �� �������� ����������";
		answer.discriminant = 0;
		answer.countCorners = 0;
		answer.x1 = 0;
		answer.x2 = 0;
		writeResultToFile(answer);
	}
	else if (argumentsForCalculation[1] != 0 && argumentsForCalculation[2] != 0) decisionCompleteEquation(argumentsForCalculation, answer);
	else decisionIncompleteEquation(argumentsForCalculation, answer);


	Sleep(5000);
	return 0;
}

void decisionCompleteEquation(float* forCoefficients, struct structAnswer forAnswer) //���������� ��� ������ ���������� ���������
{
	float discriminant;
	float x1, x2;

	discriminant = pow(forCoefficients[1], 2) - 4 * forCoefficients[0] * forCoefficients[2];

	if (discriminant > 0)
	{
		x1 = (-forCoefficients[1] + sqrt(discriminant)) / (2 * forCoefficients[0]);
		x2 = (-forCoefficients[1] - sqrt(discriminant)) / (2 * forCoefficients[0]);

		forAnswer.text = "������ ���������� ���������. ������������ > 0";
		forAnswer.discriminant = discriminant;
		forAnswer.countCorners = 2;
		forAnswer.x1 = x1;
		forAnswer.x2 = x2;
	}
	else if (discriminant == 0)
	{
		x1 = (-forCoefficients[1] + sqrt(discriminant)) / (2 * forCoefficients[0]);

		forAnswer.text = "������ ���������� ���������. ������������ = 0";
		forAnswer.discriminant = discriminant;
		forAnswer.countCorners = 1;
		forAnswer.x1 = x1;
		forAnswer.x2 = 0;
	}
	else
	{

		forAnswer.text = "������ ���������� ���������. ������������ < 0, ��� ������";
		forAnswer.discriminant = 0;
		forAnswer.countCorners = 0;
		forAnswer.x1 = 0;
		forAnswer.x2 = 0;
	}
	writeResultToFile(forAnswer);
}

void decisionIncompleteEquation(float* forCoefficients, struct structAnswer forAnswer) //���������� ��� �������� ���������� ���������
{
	float x1, x2;

	if (forCoefficients[1] == 0 && forCoefficients[2] != 0)
	{
		if (-(forCoefficients[2] / forCoefficients[0]) >= 0)
		{
			x1 = sqrt(-(forCoefficients[2] / forCoefficients[0]));
			x2 = -x1;

			forAnswer.text = "�������� ���������� ���������. b = 0!";
			forAnswer.discriminant = 0;
			forAnswer.countCorners = 2;
			forAnswer.x1 = x1;
			forAnswer.x2 = x2;
		}
		else
		{
			forAnswer.text = "�������� ���������� ���������. ��� ������, �.�. -(c/a) < 0";
			forAnswer.discriminant = 0;
			forAnswer.countCorners = 0;
			forAnswer.x1 = 0;
			forAnswer.x2 = 0;
		}
	}
	else if (forCoefficients[2] == 0 && forCoefficients[1] != 0)
	{
		x1 = 0;
		x2 = -(forCoefficients[1] / forCoefficients[0]);

		forAnswer.text = "�������� ���������� ���������. c = 0!";
		forAnswer.discriminant = 0;
		forAnswer.countCorners = 2;
		forAnswer.x1 = x1;
		forAnswer.x2 = x2;
	}
	else
	{
		x1 = 0;

		forAnswer.text = "�������� ���������� ���������. b = 0, c = 0!";
		forAnswer.discriminant = 0;
		forAnswer.countCorners = 1;
		forAnswer.x1 = x1;
		forAnswer.x2 = 0;
	}
	writeResultToFile(forAnswer);
}

void writeResultToFile(struct structAnswer forAnswer) //������ ������ � ����
{
	DWORD countFileSymbols;
	char* addressStruct = calloc(BUFFER_SIZE, sizeof(char));
	sprintf(addressStruct, "%d", &forAnswer);
	printf("%s awd\n", addressStruct);
	WriteFile(hWrite, addressStruct, BUFFER_SIZE, &countFileSymbols, NULL);
	CloseHandle(hWrite);

}