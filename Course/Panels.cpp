#include "Panels.h"
using namespace userPanel;

void UserPanel::Order()
{
	_client.OrderInsurance();
}

void Panel::ShowInsurances()
{
	Insurance insurance;
	insurance.Read();
}

void UserPanel::ShowPrice()
{
	cout << "Price of life: " << (int)InsuranceObject::Life << endl;
	cout << "Price of car: " << (int)InsuranceObject::Car << endl;
	cout << "Price of house: " << (int)InsuranceObject::House << endl;
}

void userPanel::UserPanel::SetClient(Client client)
{
	_client = client;
}

void UserPanel::CallUserMethod(int answer)
{
	switch (answer)
	{
	case 1:
		Order();
		break;
	case 2:
		ShowInsurances();
		break;
	case 3:
		ShowPrice();
		break;
	}
}


void UserPanel::ShowPanel()
{
	system("cls");
	float answer;
	bool going = true;
	while (going)
	{
		cout << "================ Choose an option ================" << endl;
		cout << "1.Order an insurance" << endl;
		cout << "2.Show all insurances" << endl;
		cout << "3.Show price-list" << endl;
		cout << "4.Exit button" << endl;
		cout << "==================================================" << endl;
		Input(&answer, " answer", InputType::Answer, 4);
		if (going = (int)answer != 4)
			CallUserMethod((int)answer);
	}
}

void FilterByPrice()
{
	float floorSummary;
	float ceilSummary;
	bool going = true;
	Insurance insurance;
	ifstream fin;
	fin.open("insuranceDataBase.txt", ifstream::binary);
	while (going)
	{
		Input(&floorSummary, " a floor summary", InputType::Number);
		Input(&ceilSummary, " a ceil summary", InputType::Number);
		if ((int)ceilSummary < (int)floorSummary)
			cout << "Enter first value lower then second" << endl;
		else
			going = false;
	}
	while (fin.read((char*)&insurance, sizeof(Insurance)))
	{
		if (insurance.GetSummary() > (int)floorSummary && insurance.GetSummary() < (int)ceilSummary)
		{
			insurance.Show();
		}
	}
}

void FilterByYear()
{
	float floorYear;
	float ceilYear;
	bool going = true;
	Insurance insurance;
	ifstream fin;
	fin.open("insuranceDataBase.txt", ifstream::binary);
	while (going)
	{
		Input(&floorYear, " a floor year", InputType::Number);
		Input(&ceilYear, " a ceil year", InputType::Number);
		if (((int)ceilYear < (int)floorYear) || ((int)floorYear < 1980 || (int)ceilYear > 2023))
			cout << "Enter first value lower then second or correct year" << endl;
		else
			going = false;
	}
	while (fin.read((char*)&insurance, sizeof(Insurance)))
	{
		if (insurance.GetYear() > (int)floorYear && insurance.GetSummary() < (int)ceilYear)
		{
			insurance.Show();
		}
	}
}

void CallCurrentFilter(int answer)
{
	switch (answer)
	{
	case 1:
		FilterByPrice();
		break;
	case 2:
		FilterByYear();
		break;
	}
}

void FilterBy()
{
	float answer;
	bool going = true;
	while (going)
	{
		cout << "================ Choose an option ================" << endl;
		cout << "1.Filter by price" << endl;
		cout << "2.Filter by year of filling" << endl;
		cout << "3.Exit button" << endl;
		cout << "==================================================" << endl;
		Input(&answer, " answer", InputType::Answer, 3);
		if (going = (int)answer != 3)
			CallCurrentFilter((int)answer);
	}
}

void AdminPanel::InsuranceWork(int answer)
{
	switch (answer)
	{
	case 1:
		_admin.AddInsurance();
		break;
	case 2:
		_admin.DeleteInsurance();
		break;
	case 3:
		_admin.EditInsurance();
		break;
	case 4:
		_admin.SearchInsurance();
		break;
	case 5:
		_admin.SortInsurances();
		break;
	case 6:
		_admin.ReviewInsurances();
		break;
	case 7:
		ShowInsurances();
		break;
	case 8:
		_admin.AddInsuranceTransactions();
		break;
	case 9:
		FilterBy();
	}
}

void AdminPanel::UserWork(int answer)
{
	switch (answer)
	{
	case 1:
		_admin.AddUser();
		break;
	case 2:
		_admin.DeleteUser();
		break;
	case 3:
		_admin.ReviewUsers();
		break;
	case 4:
		_admin.ShowUsers();
		break;
	}
}

void AdminPanel::ShowInsurancePanel()
{
	system("cls");
	float answer;
	cout << "================ Choose an option ================" << endl;
	cout << "1.Add an insurance" << endl;
	cout << "2.Delete an insurance" << endl;
	cout << "3.Edit an insurance" << endl;
	cout << "4.Search an insurance" << endl;
	cout << "5.Sort an insurances" << endl;
	cout << "6.Review all insurances" << endl;
	cout << "7.Show all insurances" << endl;
	cout << "8.Add an insurance with transactions" << endl;
	cout << "9.Show filtred insurances" << endl;
	cout << "==================================================" << endl;
	Input(&answer, " answer", InputType::Answer, 9);
	InsuranceWork((int)answer);
	
}

void AdminPanel::ShowUserPanel()
{
	system("cls");
	float answer;
	cout << "================ Choose an option ================" << endl;
	cout << "1.Add an User" << endl;
	cout << "2.Delete an User" << endl;
	cout << "3.Review an Users" << endl;
	cout << "4.Show all Users" << endl;
	cout << "==================================================" << endl;
	Input(&answer, " answer", InputType::Answer, 4);
	UserWork((int)answer);
}

void AdminPanel::ShowAdditionalPanels(int answer)
{
	switch (answer)
	{
	case 1:
		ShowInsurancePanel();
		break;
	case 2:
		ShowUserPanel();
		break;
	}
}

void AdminPanel::ShowPanel()
{
	system("cls");
	float answer;
	bool going = true;
	while (going)
	{
		cout << "================ Choose an option ================" << endl;
		cout << "1.Insurances work" << endl;
		cout << "2.User work" << endl;
		cout << "3.Exit button" << endl;
		cout << "==================================================" << endl;
		Input(&answer, " answer", InputType::Answer, 3);
		if (going = (int)answer != 3)
			ShowAdditionalPanels((int)answer);
	}
}

void AdminPanel::SetAdmin(Admin admin)
{
	_admin = admin;
}
