#define _CRT_SECURE_NO_WARNINGS
#include "Authorization.h"
#include "User.h"
#include <typeinfo>
#include "Panels.h"
using userPanel::AdminPanel;
using userPanel::UserPanel;

void GetData(char* login, char* password)
{
    CharInput(login, "a login");
    cout << "Enter a password:" << endl;
    strcpy(password, PasswordInput());
}

void SignUp()
{
    bool whileTemp = true;
    char login[50];
    char password[50] = { '\0' };
    char salt[50];
    ofstream fout;
    Role role;
    float intedRole;

    GetData(login, password);

    cout << "\nWhich role do you want?\n1.Admin\n2.Client" << endl;
    Input(&intedRole, "", InputType(Answer), 2);
    role = (enum Role)(intedRole - 1);

    strcpy(salt, login);
    User user(login, password, role, salt);

    fout.open("userDataBase_expected.txt", ofstream::app | ofstream::binary);
    fout.write((char*)&user, sizeof(User));
    fout.close();
    system("cls");
}

void LogIn()
{
    ifstream fin;
    User user;
    unsigned int loginSize = 0;
    char login[50] = { '\0' };
    char password[50] = { '\0' };
    char salt[50] = { '\0' };
    char hash[50] = { '\0' };
    bool failed = false;

    GetData(login, password);



    fin.open("userDataBase.txt", ifstream::app | ifstream::binary);
    while (fin.read((char*)&user, sizeof(User)) && fin.is_open())
    {
        failed = false;
        strcpy(salt, user.GetSalt());
        hashIt(hash, password, salt);
        if (strcmp(user.GetLogin(), login) != 0 || strcmp(user.GetHash(), hash) != 0 || user.GetAccess() == Access::Denied) //Ïðîâåðêà íà ñîâïàäåíèÿ
        {
            failed = true;
        }
        else if (strcmp(user.GetLogin(), login) == 0 && strcmp(user.GetHash(), hash) == 0 && user.GetAccess() != Access::Denied)
        {
            if (user.GetExpected() == Role::Admin)
            {
                AdminPanel aPanel;
                aPanel.SetAdmin(user);
                aPanel.ShowPanel();
                fin.close();
            }
            else
            {
                UserPanel uPanel;
                uPanel.SetClient(user);
                uPanel.ShowPanel();
                fin.close();
            }
        }
    }

    if (failed) 
        cout << "You was banned, or your login or password uncorrect! Try again" << endl;
    fin.close();
    Sleep(3000);
    system("cls");
}

void Authorizate()
{
    float answer;
    cout << "================ Choose an option ================" << endl;
    cout << "1.Log in" << endl;
    cout << "2.Sign up" << endl;
    cout << "3.Sign up an admin (Debug)" << endl;
    cout << "==================================================" << endl;
    Input(&answer, " answer", InputType::Answer, 3);
    switch ((int)answer)
    {
    case 1:
        LogIn();
        break;
    case 2:
        SignUp();
        break;
    case 3:
        Admin::SignUp();
        break;
    }
}
