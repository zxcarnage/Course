#define _CRT_SECURE_NO_WARNINGS
#include "InsuranceCompany.h"
//INSURANCE

InsuranceObject TakeInsuranceObject()
{
	float answer;
	cout << "What you want to insure?" << endl;
	cout << "1.Your life" << endl;
	cout << "2.Your car" << endl;
	cout << "3.Your house" << endl;
	cout << "4.To exit" << endl;
	Input(&answer, " answer", InputType::Answer, 4);
	switch ((int)answer)
	{
	case 1:
		return InsuranceObject::Life;
		break;
	case 2:
		return InsuranceObject::Car;
		break;
	case 3:
		return InsuranceObject::House;
		break;
	case 4:
		return InsuranceObject::Nothing;
		break;
	}
}

Insurance::Insurance()
{
	memset(_clientName, 0, 50);
	for (int i = 0; i < 10; i++)
	{
		_objectsToInsure[i] = InsuranceObject::Nothing;
	}

	_summary = 0;
	strcpy(_signDate, "01.01.1980");
}

void Insurance::Prepare(char* clientName)
{
	int counter = 0;
	int going = true;
	while (counter < 10 && going)
	{
		_objectsToInsure[counter] = TakeInsuranceObject();
		going = _objectsToInsure[counter] != InsuranceObject::Nothing;
		_summary += (int)_objectsToInsure[counter];
		counter++;
	}
	DateInput(_signDate, " sign date");
	strcpy(_clientName, clientName);
}

void Insurance::Show()
{
	int i = 0;
	TablePrinter tp(&cout);
	tp.AddColumn("INSURANCE OBJECT", 20);
	tp.PrintHeader();
	for (int i = 0; i < 10; i++)
	{
		if (_objectsToInsure[i] == InsuranceObject::Nothing)
			break;
		tp << EnumToString(_objectsToInsure[i]);
	}
	TablePrinter tp1(&cout);
	tp1.AddColumn("SUMMARY", 15);
	tp1.AddColumn("SIGN DATE", 15);
	tp1.AddColumn("NAME", 50);
	tp1.PrintHeader();
	tp1 << _summary << _signDate << _clientName;
	tp1.PrintFooter();
}

void Insurance::Write()
{
	ofstream fout;
	fout.open("insuranceDataBase.txt", ofstream::app | ofstream::binary);
	fout.write((char*)this, sizeof(Insurance));
	fout.close();
}

void Insurance::Read()
{
	ifstream fin;
	Insurance insurance;
	fin.open("insuranceDataBase.txt", ifstream::binary);
	while (fin.read((char*)&insurance, sizeof(Insurance)))
	{
		insurance.Show();
	}
	fin.close();
}

string Insurance::EnumToString(InsuranceObject objectToInsure)
{
	switch (objectToInsure)
	{
	case InsuranceObject::Life:
		return "Life";
	case InsuranceObject::Car:
		return "Car";
	case InsuranceObject::House:
		return "House";
	}
}

int Insurance::GetSummary()
{
	return _summary;
}

char* Insurance::GetName()
{
	return _clientName;
}

void Insurance::Edit()
{
	Prepare(_clientName);
}

Insurance::~Insurance() {}

int Insurance::GetYear()
{
	int year;
	year = (_signDate[6] - 48) * 1000 + (_signDate[7] - 48) * 100 + (_signDate[8] - 48) * 10 + (_signDate[9] - 48);
	return year;
}

char* Insurance::GetDate()
{
	return _signDate;
}

InsuranceObject* Insurance::GetInsureObjects()
{
	return _objectsToInsure;
}

void Insurance::CreateReport()
{
	int year;
	int totalSummary = 0;
	string name;
	Insurance insurance;
	ifstream fin;
	ofstream fout;
	vector<Insurance> insurances;
	vector<InsuranceObject> insuranceObjects;
	map<string, unsigned int> customers;
	map<unsigned int, unsigned int> yearSummary;
	map<InsuranceObject, unsigned int> insureObjects;
	fin.open("insuranceDataBase.txt", ifstream::binary);
	while (fin.read((char*)&insurance, sizeof(Insurance))) 
	{ 
		insurances.push_back(insurance);
	}
	ofstream("Report.txt");
	fout.open("Report.txt", ofstream :: app);
	for (int i = 0; i < insurances.size(); i++)
	{
		insurance = insurances.at(i);
		name = insurance.GetName();
		year = insurance.GetYear();
		totalSummary += insurance.GetSummary();
		int j = 0;
		while (insurance.GetInsureObjects()[j] != InsuranceObject::Nothing && j < 10)
		{
			insuranceObjects.push_back(insurance.GetInsureObjects()[j]);
			j++;
		}

		if (customers.count(name))
			customers.find(name)->second++;
		else
			customers.insert({ name, 1 });
		if (yearSummary.count(year))
			yearSummary.find(year)->second += insurance.GetSummary();
		else
			yearSummary.insert({ year,insurance.GetSummary() });
	}
	for (int i = 0; i < insuranceObjects.size(); i++)
	{
		InsuranceObject currentObject = insuranceObjects.at(i);
		if (insureObjects.count(currentObject))
			insureObjects.find(currentObject)->second++;
		else
			insureObjects.insert({ currentObject, 1 });
	}
	fout << "======================== REPORT ===========================\n";
	fout << "======== ALL CUSTOMERS AND THEIRS ORDER COUNTS=============\n";
	for (auto keyPair : customers)
	{
		fout << keyPair.first << ": " << keyPair.second << "\n";
	}
	fout << "========== ALL YEARS AND THEIRS TOTAL SUMMARY =============\n";
	for (auto keyPair : yearSummary)
	{
		fout << keyPair.first << ": " << keyPair.second << "\n";
	}
	fout << "============== MOST OFTEN INSURE OBJECTS  =================\n";
	for (auto keyPair : insureObjects)
	{
		fout << EnumToString(keyPair.first) << ": " << keyPair.second << "\n";
	}
	fout << "==================== TOTAL SUMMARY ========================\n";
	fout << "====================" << setw(10) << totalSummary << setw(30) << "========================\n";
	fout << "Report created on period from " << yearSummary.begin()->first << " - " << yearSummary.rbegin()->first;
	cout << "SUCCESS! CHECK \"Report.txt\" file" << endl;
	Sleep(3000);
	system("cls");
}
