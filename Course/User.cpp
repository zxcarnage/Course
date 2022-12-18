#include "User.h"

void GetUserData(char* login, char* password)
{
	CharInput(login, "a login");
	cout << "Enter a password:" << endl;
	strcpy(password, PasswordInput());
}

//USER
User::User()
{
	memset(_login, 0, 50);
	memset(_password, 0, 50);
	memset(_hashPass, 0, 50);
	memset(_salt, 0, 50);
}

User::User(char login[], char password[], Role expectedRole, char salt[], Access access)
{
	strcpy(_login, login);
	strcpy(_password, password);
	_expectedRole = expectedRole;
	strcpy(_salt, salt);
	_access = access;
	hashIt(_hashPass, password, salt);
}

User::User(const User& user)
{
	strcpy(_login, user._login);
	strcpy(_password, user._password);
	strcpy(_hashPass, user._hashPass);
	strcpy(_salt, user._salt);
	_expectedRole = user._expectedRole;
	_access = user._access;
}

char* User::GetSalt()
{
	return _salt;
}

char* User::GetPassword()
{
	return _password;
}

char* User::GetLogin()
{
	return _login;
}

char* User::GetHash()
{
	return _hashPass;
}

Access User::GetAccess()
{
	return _access;
}

Role User::GetExpected()
{
	return _expectedRole;
}

string User::GetStringedRole()
{
	switch (_expectedRole)
	{
	case Role::Admin:
		return "Admin";
		break;
	case Role::Client:
		return "Client";
		break;
	}
	return "Error";
}

//======================================================
//CLIENT

Client::Client() : User()
{
	_balance = 0;
}

Client::Client(char login[], char password[], Role expectedRole, char salt[], Access access) : User(login, password, expectedRole,salt,access)
{
	_access = access;
	_balance = 0;
}

Client::Client(User& user) : User(user)
{
	_balance = 0;
}

void Client::OrderInsurance()
{
	Insurance insurance;
	ofstream fout;
	char name[50];
	CharInput(name, " a name of insuranced person");
	insurance.Prepare(name);
	fout.flush();
	fout.open("insuranceDataBase_expected.txt", ofstream::app | ofstream::binary);
	fout.write((char*)&insurance, sizeof(Insurance));
	fout.close();

}

bool NamePredicate(Insurance first, Insurance second)
{
	return first.GetName() < second.GetName();
}

bool SumPredicate(Insurance first, Insurance second)
{
	return first.GetSummary() < second.GetSummary();
}

void SortName(vector<Insurance>& insurances)
{
	sort(insurances.begin(), insurances.end(), NamePredicate);
}

void SortSum(vector<Insurance>& insurances)
{
	sort(insurances.begin(), insurances.end(), SumPredicate);
}

void Client::ShowSortedInsurances()
{
	float answer;
	Input(&answer, "\n 1.If you want to sort by name of client\n2.If you want to sort by summary", InputType::Answer, 2);
	ifstream fin;
	ofstream fout;
	Insurance insurance;
	fin.open("insuranceDataBase.txt", ifstream::binary);
	fout.open("insuranceDataBase.txt", ofstream::binary | ofstream::app);
	vector<Insurance> insurances;
	while (fin.read((char*)&insurance, sizeof(Insurance)))
	{
		insurances.push_back(insurance);
	}
	switch ((int)answer)
	{
	case 1:
		SortName(insurances);
		break;
	case 2:
		SortSum(insurances);
		break;
	}
	for (unsigned int i = 0; i < insurances.size(); i++)
	{
		insurances.at(i).Show();
	}
}

//======================================================
//ADMIN

void Admin::SignUp()
{
	ofstream fout;
	char login[50] = "admin";
	char password[50] = "1235";
	Admin admin(login, password);
	fout.open("userDataBase.txt", ofstream::app | ofstream::binary);
	fout.write((char*)&admin, sizeof(User));
	fout.close();
}

Admin::Admin(char* login, char* password)
{
	strcpy(_login, login);
	hashIt(_hashPass, password, login);
	strcpy(_salt, login);
	_expectedRole = Role::Admin;
	_access = Access::Allowed;
}

Admin::Admin(const User& user) : User(user){ }

void Admin::AddUser()
{
	bool whileTemp = true;
	char login[50];
	char password[50] = { '\0' };
	char salt[50];
	ofstream fout;
	Role role;
	float intedRole;

	GetUserData(login, password);

	cout << "\nWhich user you want?\n1.Admin\n2.Client" << endl;
	Input(&intedRole, "", InputType(Answer), 2);
	role = (enum Role)(intedRole - 1);

	strcpy(salt, login);
	Client client(login, password, role, salt, Access::Allowed);

	fout.open("userDataBase.txt", ofstream::app | ofstream::binary);
	fout.write((char*)&client, sizeof(User));
	fout.close();
	system("cls");
}

void Admin::DeleteUser()
{
	ifstream fin;
	ofstream fout;
	User user;
	vector<User> users;
	char username[50];
	CharInput(username, "a username of user, which you want to delete");
	fin.open("userDataBase.txt", ifstream::app | ifstream::binary);
	while (fin.read((char*)&user, sizeof(User)))
	{
		if (user.GetExpected() == Role::Admin && strcmp(username, user.GetLogin()) == 0)
		{
			cout << "You cannot delete an admin account!" << endl;
			fin.close();
			fout.close();
			return;
		}
		if (strcmp(user.GetLogin(), username) != 0)
			users.push_back(user);
	}
	ofstream("userDataBase.txt");
	fout.open("userDataBase.txt", ofstream::app | ofstream::binary);
	for (unsigned int i = 0; i < users.size(); i++)
	{
		fout.write((char*)&users.at(i), sizeof(User));
	}
	fout.close();
	fin.close();
}

void Admin::ReviewUsers()
{
	ifstream fin;
	ofstream fout;
	TablePrinter tp(&cout);
	User user;
	bool success = false;
	int counter = 0;
	fin.open("userDataBase_expected.txt", ifstream::app | ifstream::binary);
	fout.open("userDataBase.txt", ofstream::app | ofstream::binary);
	tp.AddColumn("Number", 7);
	tp.AddColumn("Login", 10);
	tp.AddColumn("Expected Role", 20);
	if(fin.eof())
		tp.PrintHeader();
	while (fin.read((char*)&user, sizeof(User)))
	{
		float answer = 0;
		counter++;
		tp << counter << user.GetLogin() << user.GetStringedRole();
		cout << "Do you want to give an access to this account, or deny?" << endl;
		cout << "1.Give Access" << endl;
		cout << "2.Deny" << endl;
		Input(&answer, "Answer", InputType(Answer), 2);
		if (answer == 1)
			fout.write((char*)&user, sizeof(User));
		success = true;
	}
	if (!success)
		cout << "There is no new waited users" << endl;
	ofstream("userDataBase_expected.txt", ofstream::trunc);
	fin.close();
	fout.close();
}

void Admin::ShowUsers()
{
	system("cls");
	ifstream fin;
	User user;
	TablePrinter tp(&cout);
	int counter = 0;
	fin.open("userDataBase.txt", ifstream::app);
	tp.AddColumn("Number", 7);
	tp.AddColumn("Login", 10);
	tp.AddColumn("Role", 10);
	tp.PrintHeader();
	while (fin.read((char*)&user, sizeof(User)))
	{
		counter++;
		tp << counter << user.GetLogin() << user.GetStringedRole();
	}
	tp.PrintFooter();
	fin.close();
}

void Admin::AddInsurance()
{
	Insurance insurance;
	char name[50];
	memset(name, 0, '\n');
	strcpy(name, "admin");
	insurance.Prepare(name);
	insurance.Write();
}

void Admin::AddInsuranceTransactions()
{
	Insurance insurance;
	float answer;
	char name[50];
	ofstream fout;
	bool going = true;
	fout.open("insuranceDataBase.txt", ofstream::app | ofstream::binary);
	memset(name, 0, '\n');
	strcpy(name, "admin");
	Transaction<Insurance> transaction;
	while (going)
	{
		insurance.Prepare(name);
		transaction.Begin(insurance);
		transaction.Show();
		cout << "Commit changes?" << endl;
		Input(&answer, "\n1.Yes\n2.No", InputType::Answer, 2);
		switch ((int)answer)
		{
		case 1:
			transaction.Commit();
			insurance = *transaction.GetObj();
			fout.write((char*)&insurance, sizeof(Insurance));
			going = false;
			break;
		case 2:
			transaction.Undo();
			break;
		}
	}
}

void EditName(vector<Insurance>& insurances)
{
	char name[50];
	CharInput(name, " a editing name");
	for (unsigned int i = 0; i < insurances.size(); i++)
	{
		if (strcmp(name, insurances.at(i).GetName()))
			insurances.at(i).Edit();
	}
}

void EditSum(vector<Insurance>& insurances)
{
	float summary;
	Input(&summary, " a sum", InputType::Number);
	for (unsigned int i = 0; i < insurances.size(); i++)
	{
		if ((int)summary == insurances.at(i).GetSummary())
			insurances.at(i).Edit();
	}
}

void Admin::EditInsurance()
{
	float answer;
	Input(&answer, "\n1.If you want to edit by name of client\n2.If you want to edit by summary", InputType::Answer, 2);
	ifstream fin;
	ofstream fout;
	Insurance insurance;
	fin.open("insuranceDataBase.txt", ifstream::binary);
	fout.open("insuranceDataBase.txt", ofstream::binary | ofstream::app);
	vector<Insurance> insurances;
	while (fin.read((char*)&insurance, sizeof(Insurance)))
	{
		insurances.push_back(insurance);
	}
	switch ((int)answer)
	{
	case 1:
		EditName(insurances);
		break;
	case 2:
		EditSum(insurances);
		break;
	}
	ofstream("insuranceDataBase.txt");
	for (unsigned int i = 0; i < insurances.size(); i++)
	{
		fout.write((char*)&insurances.at(i), sizeof(Insurance));
	}
	fin.close();
	fout.close();
}

void DeleteWithSummary()
{
	float summary;
	Input(&summary, " a summary", InputType::Number);
	ofstream fout;
	ifstream fin;
	Insurance insurance;
	vector<Insurance> insurances;
	fin.open("insuranceDataBase.txt", ifstream::app | ifstream::binary);
	while (fin.read((char*)&insurance, sizeof(Insurance)))
	{
		if (insurance.GetSummary() != (int)summary)
		{
			insurances.push_back(insurance);
		}
	}
	ofstream("insuranceDataBase.txt");
	fout.open("insuranceDataBase.txt", ofstream::app |ofstream::binary);
	for (unsigned int i = 0; i < insurances.size(); i++)
	{
		fout.write((char*)&insurances.at(i), sizeof(Insurance));
	}
	fin.close();
	fout.close();
}

void DeleteWithName()
{
	char name[50];
	CharInput(name, " a name");
	ofstream fout;
	ifstream fin;
	Insurance insurance;
	vector<Insurance> insurances;
	fin.open("insuranceDataBase.txt", ifstream::app | ifstream::binary);
	while (fin.read((char*)&insurance, sizeof(Insurance)))
	{
		if (insurance.GetName() != name)
		{
			insurances.push_back(insurance);
		}
	}
	ofstream("insuranceDataBase.txt");
	fout.open("insuranceDataBase.txt", ofstream::app | ofstream::binary);
	for (unsigned int i = 0; i < insurances.size(); i++)
	{
		fout.write((char*)&insurances.at(i), sizeof(Insurance));
	}
	fin.close();
	fout.close();
}

void Admin::DeleteInsurance()
{
	float answer;
	Input(&answer, "\n1.If you want to delete with summary\n2.If you want to delete all insurances witch name of client", InputType::Answer, 2);
	switch ((int)answer)
	{
	case 1:
		DeleteWithSummary();
		break;
	case 2:
		DeleteWithName();
		break;
	}
}

void Admin::ReviewInsurances()
{
	ifstream fin;
	ofstream fout;
	TablePrinter tp(&cout);
	Insurance insurance;
	bool success = false;
	int counter = 0;
	fin.open("insuranceDataBase_expected.txt", ifstream::app | ifstream::binary);
	fout.open("insuranceDataBase.txt", ofstream::app | ofstream::binary);
	tp.AddColumn("Number", 7);
	tp.AddColumn("Client name", 20);
	tp.AddColumn("Summary", 15);
	if (!fin.eof())
		tp.PrintHeader();
	while (fin.read((char*)&insurance, sizeof(Insurance)))
	{
		float answer = 0;
		counter++;
		tp << counter << insurance.GetName() << insurance.GetSummary();
		cout << "Do you want to approve this insurance, or deny?" << endl;
		cout << "1.Approve" << endl;
		cout << "2.Deny" << endl;
		Input(&answer, "Answer", InputType(Answer), 2);
		if (answer == 1)
			fout.write((char*)&insurance, sizeof(Insurance));
		success = true;
	}
	if (!success)
		cout << "There is no new insurances" << endl;
	ofstream("insuranceDataBase_expected.txt", ofstream::trunc);
	fin.close();
	fout.close();
}

void SearchName()
{
	ifstream fin;
	TablePrinter tp(&cout);
	Insurance insurance;
	char name[50];
	memset(name, 0, '\n');
	fin.open("insuranceDataBase.txt", ifstream::binary);
	CharInput(name, " a name of person");
	while (fin.read((char*)&insurance, sizeof(Insurance)))
	{
		if (strcmp(name, insurance.GetName()) == 0)
			insurance.Show();
	}
	fin.close();
}

void SearchSum()
{
	ifstream fin;
	TablePrinter tp(&cout);
	Insurance insurance;
	float summary;
	fin.open("insuranceDataBase.txt", ifstream::binary);
	Input(&summary, " a summary", InputType::Answer);
	while (fin.read((char*)&insurance, sizeof(Insurance)))
	{
		if ((int)summary == insurance.GetSummary())
			insurance.Show();
	}
	fin.close();
}

void Admin::SearchInsurance()
{
	float answer;
	Input(&answer, "\n1.If you want to search by name of client\n2.If you want to search by summary", InputType::Answer, 2);
	switch ((int)answer)
	{
	case 1:
		SearchName();
		break;
	case 2:
		SearchSum();
		break;
	}
}

void Admin::SortInsurances()
{
	float answer;
	Input(&answer, "\n 1.If you want to sort by name of client\n2.If you want to sort by summary", InputType::Answer, 2);
	ifstream fin;
	ofstream fout;
	Insurance insurance;
	fin.open("insuranceDataBase.txt", ifstream::binary);
	fout.open("insuranceDataBase.txt", ofstream::binary | ofstream::app);
	vector<Insurance> insurances;
	while (fin.read((char*)&insurance, sizeof(Insurance)))
	{
		insurances.push_back(insurance);
	}
	switch ((int)answer)
	{
	case 1:
		SortName(insurances);
		break;
	case 2:
		SortSum(insurances);
		break;
	}
	ofstream("insuranceDataBase.txt");
	for (unsigned int i = 0; i < insurances.size(); i++)
	{
		fout.write((char*)&insurances.at(i), sizeof(Insurance));
	}
	fin.close();
	fout.close();
}
//======================================================