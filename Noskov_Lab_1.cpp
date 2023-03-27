#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <algorithm>

#define buffersize 100

using namespace std;


ofstream fout;
ifstream fin;

const char* filename = "data.txt";
int dbSize = 5;

struct Database {
	char* fam;
	int type;
	double weight;
	int quant;
	double cost;
};


void MainMenuInterface() {
	printf("1) ��������� ��������\n");
	printf("2) �������� ����� �������\n");
	printf("3) ������� ���������� � ������� � ��������� ����\n");
	printf("4) ������� ���������� � ���� �������� � ��������� ����\n");
	printf("5) ����� ������� �� ��������\n");
	printf("6) ����� ������� �� ����\n");
	printf("7) ������������� ������� �� ����\n");
}


// String Workarounds
void clearBuffer(void) {
	fseek(stdin, 0, SEEK_END);
}


void InputString(char* dest) {
	clearBuffer();
	char buffer[buffersize] = { };
	fgets(buffer, buffersize, stdin);
	strcpy_s(dest, sizeof(buffer), buffer);
}


// Errors Block
void FileError() {
	system("cls");
	printf("\033[1;31m������ � �������� �����, ������ ����������\033[0m\n\n");
	exit(EXIT_FAILURE);
}

void DataError() {
	system("cls");
	printf("\033[1;31m������ � ������ �����, ������ ����������\033[0m\n\n");
	exit(EXIT_FAILURE);
}

void WeightError(char* dest) {
	system("cls");
	printf("\033[1;31m����� ������� �� ����� ���� ����� ����!\033[0m");
	printf("\n\n������ �����, ��������� �������: ");
	InputString(dest);
}

void CostError(char* dest) {
	system("cls");
	printf("\033[1;31m��������� ������� �� ����� ���� ����� ����!\033[0m");
	printf("\n\n������ �����, ��������� �������: ");
	InputString(dest);
}


//File Workarounds
void FileDataOpen() {
	fout.open(filename, ios::app);
	if (!fout.is_open()) {
		system("cls");
		printf("\x1B[31m���� �� ��������! ��������� ������ � ������������� ���������!\033[0m");
		FileError();
	}
}

void FileDataClose() {
	fout.close();
}

int ReadData(Database* data, int nop) {
	char* str = new char[buffersize];
	fin.open(filename);
	if (fin.is_open()) {
		fin.clear();
		fin.seekg(0);
		while (!fin.eof()) {
			for (int i = 0; i < 5; i++) {
				fin.getline(str, buffersize);
				if (fin.eof()) {
					if (i == 4) { data[nop].cost = atof(str); }
					break;
				}
				if (i == 0) { data[nop].fam = new char[strlen(str) + 2]; strcpy_s(data[nop].fam, strlen(str) + 2, str); strcat(data[nop].fam, "\n"); }
				if (i == 1) { data[nop].type = atoi(str); }
				if (i == 2) { data[nop].quant = atoi(str); }
				if (i == 3) { data[nop].weight = atof(str); }
				if (i == 4) { data[nop].cost = atof(str); }
			}
			nop++;
		}
	}
	fin.close();
	return nop;
}


// Outputs Block
void FirstOutput(Database* data, int i) {
	printf("������� �����:       | %d\n", i);
	printf("�������� �������:    | %s", data[i - 1].fam);
	printf("��� �������:         | %d\n", data[i - 1].type);
	printf("��� �������:         | %.2lf\n", data[i - 1].weight);
	printf("���������� �������:  | %d\n", data[i - 1].quant);
	printf("���� �������:        | %.2lf\n\n", data[i - 1].cost);
}

void SecondOutput(Database* data, int i) {
	for (int j = 0; j < i; j++) {
		printf("������� �����:       | %d\n", j + 1);
		printf("�������� �������:    | %s", data[j].fam);
		printf("��� �������:         | %d\n", data[j].type);
		printf("��� �������:         | %.2lf\n", data[i - 1].weight);
		printf("���������� �������:  | %d\n", data[j].quant);
		printf("���� �������:        | %.2lf\n\n", data[j].cost);
	}
}

void ThirdOutput(Database* data, int i) {
	printf("������� �����:       | %d\n", i + 1);
	printf("�������� �������:    | %s", data[i].fam);
	printf("��� �������:         | %d\n", data[i].type);
	printf("��� �������:         | %.2lf\n", data[i - 1].weight);
	printf("���������� �������:  | %d\n", data[i].quant);
	printf("���� �������:        | %.2lf\n\n", data[i].cost);
}


// String Parsing
int StreamingStringEntryIntMainMenu(int number) {
	char* dest = new char[buffersize];
	InputString(dest);
	bool check = 0;
	while (check == 0) {
		for (int i = 0; i < strlen(dest) - 1; i++) {
			if (dest[i] < 48 || dest[i] > 55) {
				system("cls");
				printf("\x1B[31m������ �����!\033[0m\n\n");
				MainMenuInterface();
				printf("������ �����, ��������� �������: ");
				InputString(dest);
			}
			else {
				check = 1; // ��� else
			}
		}
	}
	number = atoi(dest);
	delete[] dest;
	return number;
}


int ProductsOutputWindow(int number) {
	char* dest = new char[buffersize];
	InputString(dest);
	bool check = 0;
	while (check == 0) {
		for (int i = 0; i < strlen(dest) - 1; i++) {
			if (dest[i] < 48 || dest[i] > 57) {
				system("cls");
				printf("\x1B[31m��� �������: 1 - �������, 2 - �������, 3 - ��������\033[0m");
				printf("\n\n������ �����, ��������� �������: ");
				InputString(dest);
			}
			else {
				check = 1;
			}
		}
	}
	number = atoi(dest);
	delete[] dest;
	return number;
}


void CharacterOutputWindow(Database* data, char* dest) {
	InputString(dest);
	bool check = 0;
	while (check == 0) {
		if (dest[0] < 65 || dest[0] > 90) {
			clearBuffer();
			system("cls");
			printf("\x1B[31m�������� ������� ������ ���������� � ��������� ����� � ����� ������������� ��������� �����!\033[0m");
			printf("\n\n������ �����(������ ����� ������ ���� ���������), ��������� �������: ");
			InputString(dest);
		}
		if (strlen(dest) == 2) {
			check = 1;
		}
		else {
			for (int i = 1; i < strlen(dest) - 1; i++) {
				if (dest[i] < 97 || dest[i] > 122) {
					clearBuffer();
					system("cls");
					printf("\x1B[31m�������� ������� ������ ���������� � ��������� ����� � ����� ������������� ��������� �����!\033[0m");
					printf("\n\n������ �����, ��������� �������: ");
					InputString(dest);
				}
				else {
					check = 1;
				}
			}

		}
	}
}


int QuantityOutputWindow(int number) {
	char* dest = new char[buffersize];
	InputString(dest);
	bool check = 0;
	while (check == 0) {
		while (dest[0] == 48) {
			system("cls");
			printf("\x1B[31m���������� ������� �� ����� ���� ����� ����! ������������ ���������� ������� 100000!\033[0m");
			printf("\n\n���������� ������ �� ����� ���������� � ���� ��� ���� ������ ����, ��������� �������: ");
			InputString(dest);
		}
		for (int i = 0; i < strlen(dest) - 1; i++) {
			if (dest[i] < 48 || dest[i] > 57) {
				system("cls");
				printf("\x1B[31m���������� ������� �� ����� ���� ����� ����! ������������ ���������� ������� 100000!\033[0m");
				printf("\n\n������ �����, ��������� �������: ");
				InputString(dest);
			}
			else {
				check = 1;
			}
		}
	}
	number = atoi(dest);
	delete[] dest;
	return number;
}


void InputQuant(Database* data, int nop) {
	int number = 0;
	system("cls");
	printf("\x1B[32m���������� ������� �� ����� ���� ����� ����! ������������ ���������� ������� 100000!\033[0m");
	printf("\n\n������� ���������� �������: ");
	number = QuantityOutputWindow(number);
	while (number < 1 || number > 100000) {
		system("cls");
		printf("\x1B[31m���������� ������� �� ����� ���� ����� ����! ������������ ���������� ������� 100000!\033[0m");
		printf("\n\n������ �����, ��������� �������: ");
		number = QuantityOutputWindow(number);
	}
	data[nop].quant = number;
	fout << data[nop].quant << endl;
}


void DoubleWeightOutput(Database* data, int nop) {
	int counter = 0;
	int counter1 = 0;
	char* dest = new char[buffersize];
	InputString(dest);
	bool check = 0;
	while (check == 0) {
		while (dest[strlen(dest) - 2] == 44) {
			CostError(dest);
		}
		for (int i = 0; i < strlen(dest) - 1; i++) {
			if (dest[i] < 44 || dest[i] == 45 || dest[i] == 46 || dest[i] == 47 || dest[i] > 57) {
				CostError(dest);
			}
			else {
				check = 1;
			}
			if (dest[i] == 44) {
				counter++;
			}
			if (counter > 1) {
				CostError(dest);
			}
			if (dest[i] == 48) {
				counter1++;
			}
		}
		if (counter1 == strlen(dest - 1) && counter == 0) {
			check = 0;
		}
		else if (counter1 == strlen(dest - 1) && counter == 1) {
			check = 1;
		}
	}
	double number = 0;
	number = atof(dest);
	data[nop].weight = number;
	fout << data[nop].weight << endl;
	delete[] dest;
}


void DoubleCostOutput(Database* data, int nop) {
	int counter = 0;
	int counter1 = 0;
	char* dest = new char[buffersize];
	InputString(dest);
	bool check = 0;
	while (check == 0) {
		while (dest[strlen(dest) - 2] == 44) {
			CostError(dest);
		}
		for (int i = 0; i < strlen(dest) - 1; i++) {
			if (dest[i] < 44 || dest[i] == 45 || dest[i] == 46 || dest[i] == 47 || dest[i] > 57) {
				CostError(dest);
			}
			else {
				check = 1;
			}
			if (dest[i] == 44) {
				counter++;
			}
			if (counter > 1) {
				CostError(dest);
			}
			if (dest[i] == 48) {
				counter1++;
			}
		}
		if (counter1 == strlen(dest - 1) && counter == 0) {
			check = 0;
		}
		else if (counter1 == strlen(dest - 1) && counter == 1) {
			check = 1;
		}
	}
	double number = 0;
	number = atof(dest);
	data[nop].cost = number;
	fout << data[nop].cost;
	delete[] dest;
}


int StreamingStringEntryIntNumber(int number) {
	char* dest = new char[buffersize];
	InputString(dest);
	bool check = 0;
	while (check == 0) {
		for (int i = 0; i < strlen(dest) - 1; i++) {
			if (dest[i] < 48 || dest[i] > 57) {
				system("cls");
				printf("\x1B[31m����� ������� ����� ���� ������ ����� ������!\033[0m");
				printf("\n\n������ �����, ��������� �������: ");
				InputString(dest);
			}
			else {
				check = 1;
			}
		}
	}
	number = atoi(dest);
	delete[] dest;
	return number;
}


// Inputs Block
void InputType(Database* data, int check, int nop) {
	system("cls");
	printf("\x1B[32m��� �������: 1 - �������, 2 - �������, 3 - ��������\033[0m");
	printf("\n\n������� ��� �������(1,2,3): ");
	check = ProductsOutputWindow(check);
	while (check < 1 || check > 3) {
		system("cls");
		printf("\x1B[31m��� �������: 1 - �������, 2 - �������, 3 - ��������\033[0m");
		printf("\n\n������ �����, ��������� �������: ");
		check = ProductsOutputWindow(check);
	}
	data[nop].type = check;
	fout << data[nop].type << endl;
}


int InputName(Database* data, int nop) {
	printf("\x1B[32m�������� ������� ������ ���������� � ��������� ����� � ����� ������������� ��������� �����!\033[0m");
	printf("\n\n������� �������� �������: ");
	char* dest = new char[buffersize];
	CharacterOutputWindow(data, dest);
	data[nop].fam = new char[strlen(dest) + 1];
	strcpy_s(data[nop].fam, strlen(dest) + 1, dest);
	delete[] dest;
	if (nop != 0) {
		fout << endl;
	}
	fout << data[nop].fam;
	return nop;
}


void InputWeight(Database* data, int nop) {
	system("cls");
	printf("\x1B[32m����� ������� �� ����� ���� ����� ����!\033[0m");
	printf("\n\n������� ����� �������: ");
	DoubleWeightOutput(data, nop);
}


void InputCost(Database* data, int nop) {
	system("cls");
	printf("\x1B[32m��������� ������� �� ����� ���� ����� ����!\033[0m");
	printf("\n\n������� ��������� �������: ");
	DoubleCostOutput(data, nop);
}


int InputNumber(int check, int nop) {
	system("cls");
	printf("\x1B[32m����� ������� ����� ���� ������ ����� ������!\033[0m");
	printf("\n\n������� ����� �������: ");
	check = StreamingStringEntryIntNumber(check);
	while (check < 1 || check > nop) {
		system("cls");
		printf("\x1B[31m�� ����� �� ����� ���������, �������� �������: %d\033[0m", nop);
		printf("\n\n������ �����, ��������� �������: ");
		check = StreamingStringEntryIntNumber(check);
	}
	system("cls");
	return check;
}


// Adding Function
int AddingNewProduct(Database* data, int nop) {
	int check = 0;
	system("cls");
	FileDataOpen();
	InputName(data, nop);
	InputType(data, check, nop);
	InputQuant(data, nop);
	InputWeight(data, nop);
	InputCost(data, nop);
	FileDataClose();
	nop++;
	return nop;
}


// Main Menu Interface Funtion
int MainMenu(int check) {
	MainMenuInterface();
	printf("������� ����� ��������: ");
	check = StreamingStringEntryIntMainMenu(check);
	while (check < 1 || check > 9) {
		system("cls");
		printf("\x1B[31m������ �����!\033[0m\n\n");
		MainMenuInterface();
		printf("������ �����, ��������� �������: ");
		check = StreamingStringEntryIntMainMenu(check);
	}
	return check;
}


// Tab Output Block
void TabForm(Database* data, int nop) {
	int check = 0;
	if (nop == 0) {
		system("cls");
		printf("\x1B[31m������� ��� �� ���������!\033[0m\n\n");
	}
	else {
		check = InputNumber(check, nop);
		while (check < 1 || check > nop) {
			system("cls");
			printf("\x1B[31m�� ����� �� ����� ���������, �������� �������: %d\033[0m", nop);
			printf("\n\n������ �����, ��������� �������: ");
			check = StreamingStringEntryIntNumber(check);
		}
		FirstOutput(data, check);
	}
}


void OtherTabForm(Database* data, int nop) {
	int check = 0;
	if (nop == 0) {
		system("cls");
		printf("\x1B[31m������� ��� �� ���������!\033[0m\n\n");
	}
	else {
		SecondOutput(data, nop);
	}
}


// Search Funtions 
void OtherCharOutputWindow(Database* data, char*& ot_dest) {
	char* dest = new char[buffersize];
	InputString(dest);
	bool check = 0;
	while (check == 0) {
		for (int i = 1; i < strlen(dest) - 1; i++) {
			if (dest[0] < 65 || dest[0] > 90) {
				clearBuffer();
				system("cls");
				printf("\x1B[31m�������� ������� ������ ���������� � ��������� ����� � ����� ������������� ��������� �����!\033[0m");
				printf("\n\n������ �����(������ ����� ������ ���� ���������), ��������� �������: ");
				InputString(dest);

			}
			else if (dest[i] < 97 || dest[i] > 122) {
				clearBuffer();
				system("cls");
				printf("\x1B[31m�������� ������� ������ ���������� � ��������� ����� � ����� ������������� ��������� �����!\033[0m");
				printf("\n\n������ �����, ��������� �������: ");
				InputString(dest);
			}
			else {
				check = 1;
			}
		}
	}
	strcpy_s(ot_dest, strlen(dest) + 1, dest);
	delete[] dest;
}


void OtherNameInput(Database* data, char* ot_dest) {
	printf("\x1B[32m�������� ������� ������ ���������� � ��������� ����� � ����� ������������� ��������� �����!\033[0m");
	printf("\n\n������� �������� �������: ");
	OtherCharOutputWindow(data, ot_dest);
	printf("\n");
}


int WorkingWithSearchName(Database* data, int nop, char* ot_dest, int i) {
	int counter = 0;
	int check = 0;
	if (nop == 0) {
		printf("\x1B[31m������� ��� �� ���������!\033[0m\n\n");
	}
	else {
		if (strcmp(ot_dest, data[i].fam) == 0) {
			check = 1;
			counter++;
		}
	}
	if (counter == 0) {
		system("cls");
		printf("\x1B[31m������� �� �������!\033[0m\n\n");
	}
	return check;
}


int OtherInputType(Database* data, int check, int nop) {
	system("cls");
	printf("\x1B[32m��� �������: 1 - �������, 2 - �������, 3 - ��������\033[0m");
	printf("\n\n������� ��� �������(1,2,3): ");
	check = ProductsOutputWindow(check);
	printf("\n");
	while (check < 1 || check > 3) {
		system("cls");
		printf("\x1B[31m��� �������: 1 - �������, 2 - �������, 3 - ��������\033[0m");
		printf("\n\n������ �����, ��������� �������: ");
		check = ProductsOutputWindow(check);
	}
	return check;
}


void WorkingWithSearchType(Database* data, int nop) {
	int counter = 0;
	int check = 0;
	check = OtherInputType(data, check, nop);
	if (nop == 0) {
		system("cls");
		printf("\x1B[31m������� ��� �� ���������!\033[0m\n\n");
	}
	else {
		for (int i = 0; i < nop; i++) {
			if (data[i].type == check) {
				ThirdOutput(data, i);
			}
			else {
				counter++;
			}
		}
	}
	if (counter == nop) {
		system("cls");
		printf("\x1B[31m������� ������� ���� �� ����������!\033[0m\n\n");
	}
}


void SortItems(Database* data, int nop) {
	double temp;
	double* arr = new double[nop];
	printf("\n\n");
	for (int i = 0; i < nop; i++) {
		arr[i] = data[i].cost;
	}
	for (int i = 0; i < nop; i++) {
		for (int j = 0; j < nop - 1; j++) {
			if (arr[j] < arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < nop; i++) {
		for (int j = 0; j < nop; j++) {
			if (arr[i] == data[j].cost) {
				ThirdOutput(data, j);
			}
		}
	}
	delete[] arr;
}


int Interface(Database* data, int nop, int dbSize) {
	int check = 0;
	while (check != 1) {
		check = MainMenu(check);
		switch (check) {
		case 2: {
			if (nop != dbSize) {
				nop = AddingNewProduct(data, nop);
				system("cls");
				printf("\x1B[32m������ ������� �������!\033[0m\n\n");
			}
			else {
				system("cls");
				printf("\x1B[31m��������� ���������� ���������� ������� �������: %d\033[0m\n\n", nop);
			}
			break;
		}
		case 3: {
			TabForm(data, nop);
			break;
		}
		case 4: {
			system("cls");
			OtherTabForm(data, nop);
			break;
		}
		case 5: {
			system("cls");
			if (nop == 0) {
				printf("\x1B[31m������� ��� �� ���������!\033[0m\n\n");
			}
			else {
				int counter = 0;
				char* ot_dest = new char[buffersize];
				OtherNameInput(data, ot_dest);
				for (int i = 0; i < nop; i++) {
					int check = WorkingWithSearchName(data, nop, ot_dest, i);
					if (check == 1) {
						ThirdOutput(data, i);
					}
				}
			}
			break;
		}
		case 6: {
			system("cls");
			if (nop == 0) {
				printf("\x1B[31m������� ��� �� ���������!\033[0m\n\n");
			}
			else {
				WorkingWithSearchType(data, nop);
			}
			break;
		}
		case 7: {
			system("cls");
			if (nop == 0) {
				printf("\x1B[31m������� ��� �� ���������!\033[0m\n\n");
			}
			else {
				printf("\x1B[32m����������� ����������!\033[0m");
				SortItems(data, nop);
			}
			break;
		}
		}
	}
	return nop;
}


int DataLoading(Database* data, int nop) {
	int count = 0;
	int count1 = 0;
	int count2 = 0;
	int counter = 0;
	bool check = 0;
	fin.open(filename);
	if (fin.is_open()) {
		if (fin.peek() == EOF) {
			printf("\x1B[32m���� ������!\033[0m\n\n");
		}
		else {
			char* str = new char[buffersize];
			while (!fin.eof()) {
				count1 = 0;
				count2 = 0;
				fin.getline(str, buffersize);
				counter++;
				if (fin.eof()) {
					break;
				}
				if (count == 0) {
					if (str[0] < 65 || str[0] > 90) {
						DataError();
					}
					for (int i = 1; i < strlen(str); i++) {
						if (str[i] < 97 || str[i] > 122) {
							DataError();
						}
					}
					count++;
				}
				if (count == 1) {
					fin.getline(str, buffersize);
					counter++;
					for (int i = 0; i < strlen(str); i++) {
						if (str[i] < 48 || str[i] > 57) {
							DataError();
						}
						if (str[i] < 49 || str[i] > 51) {
							DataError();
						}
					}
					count++;
				}
				if (count == 2) {
					fin.getline(str, buffersize);
					counter++;
					for (int i = 0; i < strlen(str); i++) {
						if (str[i] < 48 || str[i] > 57) {
							DataError();
						}
					}
					count++;
				}
				if (count == 3) {
					fin.getline(str, buffersize);
					counter++;
					for (int i = 0; i < strlen(str); i++) {
						if (str[i] < 48 || str[i] > 57) {
							if (str[i] != 44) {
								DataError();
							}
						}
						if (str[0] == 44) {
							DataError();
						}
						if (str[i] == 44) {
							count1++;
							if (count1 > 1) {
								DataError();
							}
						}
						if (str[i] == 48) {
							count2++;
							if (count2 == strlen(str) - 1) {
								DataError();
							}
						}
					}
					count++;
				}
				if (count == 4) {
					fin.getline(str, buffersize);
					counter++;
					for (int i = 0; i < strlen(str); i++) {
						if (str[i] < 48 || str[i] > 57) {
							if (str[i] != 44) {
								DataError();
							}
						}
						if (str[0] == 44) {
							DataError();
						}
						if (str[i] == 44) {
							count1++;
							if (count1 > 1) {
								DataError();
							}
						}
						if (str[i] == 48) {
							count2++;
							if (count2 == strlen(str) - 1) {
								DataError();
							}
						}
					}
					count++;
				}
				count -= 5;
			}
			if (counter > dbSize * 5) {
				DataError();
			}
			printf("\x1B[32m������ ������� �������!\033[0m\n\n");
			nop = ReadData(data, nop);
			fin.close();
		}
	}
	else {
		printf("\x1B[31m���� �����������!\033[0m\n\n");
	}
	fin.close();
	return nop;
}


// Main Function
int main() {
	setlocale(LC_ALL, "Russian");

	Database* data = new Database[dbSize];
	int product_counter = 0;
	product_counter = DataLoading(data, product_counter);
	product_counter = Interface(data, product_counter, dbSize);

	delete[] data;
	return 0;
}