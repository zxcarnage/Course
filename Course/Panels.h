#include <iostream>
#include "Input.h"
#include "User.h"
#include "SmartPointer.h"
#pragma once
using std::cout;
using std::endl;

class Panel
{
public:
	virtual void ShowPanel() = 0;
	virtual void ShowInsurances();
};
namespace userPanel
{
	class UserPanel : Panel
	{
		Client _client;
		void CallUserMethod(int answer);
	public:
		virtual void ShowPanel() override;
		void Order();
		void ShowPrice();
		void KillInsurance();
		void SetClient(Client client);
	};

	class AdminPanel : Panel
	{
		Admin _admin;
		void InsuranceWork(int answer);
		void ShowAdditionalPanels(int answer);
		void UserWork(int answer);
		void ShowUserPanel();
		void ShowInsurancePanel();
	public:
		virtual void ShowPanel() override;
		void SetAdmin(Admin admin);
	};
}

