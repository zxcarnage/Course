#pragma once
#include<iostream>
#include <map>
#include <fstream>
#include <Algorithm>
#include "Input.h"
#include "User.h"
#include "TablePrinter.h"
using std::map;
using std::sort;
using std::ifstream;
using std::ofstream;

namespace InheritanceClasses
{
	class Document
	{
	protected:
		char _signDate[12];
	public:
		void virtual Prepare(char* clientName) = 0;
		void virtual Show() = 0;
		void virtual Write() = 0;
		void static  Read() {};
	};
}
enum class InsuranceObject
{
	Life = 500,
	Car = 150,
	House = 350,
	Nothing = 0
};

class Insurance : public InheritanceClasses::Document
{	
	InsuranceObject _objectsToInsure[10];
	char _clientName[50];
	int _summary;
	string EnumToString(InsuranceObject objectToInsure);
public:
	Insurance();
	~Insurance();
	void Prepare(char* clientName) override;
	void Show() override;
	void Write() override;
	void Read();
	void Edit();
	int GetYear();
	int GetSummary();
	char* GetName();
};

