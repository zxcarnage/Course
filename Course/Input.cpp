#include "Input.h"
#include <conio.h>

void AgeInput(float tempData, string dataName)
{
	if (tempData < 0 || tempData > 120)
		throw InputException("Incorrect age amount", tempData);
}

void NumberInput(float tempData, string dataName)
{
	if (tempData < 0 || tempData > INT_MAX)
		throw InputException("Incorrect data", tempData);
}

void AnswerInput(float tempData, string dataName, int ceilNum = 0)
{
	if ((int)tempData != tempData || (int)tempData > ceilNum)
		throw InputException("Incorrect type of answer, try int num", tempData);
}

void DateCheck(char date[])
{
	int day;
	int month;
	int year;
	try
	{
		day = (date[0] - 48) * 10 + (date[1] - 48);
		month = (date[3] - 48) * 10 + (date[4] - 48);
		year = (date[6] - 48) * 1000 + (date[7] - 48) * 100 + (date[8] - 48) * 10 + (date[9] - 48);
	}
	catch (...)
	{
		throw exception("Wrong date view, try DD.MM.YYYY");
	}
	if (date[2] != '.' || date[5] != '.')
		throw exception("Wrong date view, try DD.MM.YYYY");
	if (day > 31 || day < 1)
		throw exception("Wrong date view, try DD.MM.YYYY");
	if (month < 1 || month > 12)
		throw exception("Wrong date view, try DD.MM.YYYY");
	if (year < 1980 || year > 2023)
		throw exception("Wrong date view, try DD.MM.YYYY");
	if(date[0] == '\r')
		throw exception("Wrong date view, try DD.MM.YYYY");
}

void DateInput(char date[], string dataName)
{
	bool isRunning = true;
	while (isRunning)
	{
		try
		{
			char tempData[20];
			cout << "Enter " << dataName << endl;
			memset(tempData, 0, sizeof tempData);
			memset(date, 0, sizeof date);
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cin.getline(tempData, 20);
			DateCheck(tempData);
			strcpy(date, tempData);
			isRunning = false;

		}
		catch (InputException& iEx)
		{
			cout << iEx.what() << endl;
			cout << "Error data: " << iEx.GetErrorData() << endl;
		}
		catch (const exception& ex)
		{
			cout << ex.what() << endl;
		}
	}
}

char* PasswordInput()
{
	char symbol;
	int i = 0;
	char password[50] = { '\0' };
	while (true && i < 50)
	{
		symbol = _getch();
		switch (symbol)
		{
		default:
			cout << '*';
			password[i] = (char)symbol;
			i++;
			break;
		case 13:
			cout << endl;
			return password;
			break;
		case 27:
			exit(0);
			break;
		case 8:
			cout << '\b' << " " << '\b';
			i--;
			break;
		}
	}
	cout << endl;
}


void CharInput(char data[], string dataName)
{
	char tempData[20];
	cout << "Enter " << dataName << endl;
	memset(tempData, 0, sizeof tempData);
	memset(data, 0, sizeof data);
	cin.get();
	cin.getline(tempData, 20);
	strcpy(data,tempData);
}

void StringInput(string* data, string dataName)
{
	string tempData;
	cout << "Enter " << dataName << endl;
	cin >> tempData;
	*data = tempData;
}

float InputException::GetErrorData()
{
	return _errorData;
}

void InputMenu(float* data, string dataName, InputType inputType, int ceilNum)
{
	float tempData;
	cout << "Enter " << dataName << endl;
	cin >> tempData;
	if (!cin)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		throw exception("Incorrect data type input!");
	}
	switch (inputType)
	{
	case Number:
		NumberInput(tempData, dataName);
		*data = tempData;
		break;
	case Age:
		AgeInput(tempData, dataName);
		*data = tempData;
		break;
	case Answer:
		AnswerInput(tempData, dataName, ceilNum);
		*data = tempData;
		break;
	default:
		throw exception("Incorrect InputType!!!");
		break;
	}
}

void Input(float* data, string dataName, InputType inputType, int ceilNum)
{
	
	bool isRunning = true;
	while (isRunning)
	{
		try
		{
			InputMenu(data, dataName, inputType, ceilNum);
			isRunning = false;

		}
		catch (InputException& iEx)
		{
			cout << iEx.what() << endl;
			cout << "Error data: " << iEx.GetErrorData() << endl;
		}
		catch (const exception& ex)
		{
			cout << ex.what() << endl;
		}
	}
}
