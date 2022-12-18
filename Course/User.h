#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <vector>
#include "InsuranceCompany.h"
#include "Input.h"
#include "Hash.h"
#include "TablePrinter.h"
#include "Transaction.h"
using std::memset;
using std::ifstream;
using std::ofstream;
using std::vector;
//������������ �������
enum class Access
{
	Allowed,
	OnReview,
	Denied
};

//������������ �����
enum class Role
{
	Admin,
	Client
};

class User
{
protected:
	char _login[50];
	char _password[50];
	char _hashPass[50];
	char _salt[50];
	Role _expectedRole;
	Access _access;
public:
	User();
	User(char login[], char password[], Role expectedRole, char salt[], Access access = Access::OnReview);
	User(const User& user);
	char* GetSalt();
	char* GetPassword();
	char* GetLogin();
	char* GetHash();
	Access GetAccess();
	Role GetExpected();
	string GetStringedRole();
	friend istream& operator>>(istream& stream, User& user);
	friend ostream& operator<<(ostream& stream, User& user);

};

class Client : User
{
public:
	Client();
	Client(char login[], char password[], Role expectedRole, char salt[], Access access = Access::OnReview);
	Client(User& user);
	void OrderInsurance();
	void ShowSortedInsurances();
};

class Admin : User
{
public:
	static void SignUp();
	Admin() : User() { };
	Admin(char* login, char* password);
	Admin(const User& user);
	void AddUser();
	void AddInsurance();
	void DeleteUser();
	void ReviewUsers();
	void ShowUsers();
	void EditInsurance();
	void DeleteInsurance();
	void ReviewInsurances();
	void SearchInsurance();
	void SortInsurances();
	void AddInsuranceTransactions();
};