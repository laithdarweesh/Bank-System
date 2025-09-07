#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

enum enMainMenueOptions { eShowListClient = 1, eAddClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eTransactions = 6, eManageUsers = 7, eLogout = 8 };

enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eMainMenue = 4 };

enum enManageUserMenueOption { eListUsers = 1, eAddUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, MainMenue = 6 };

enum enMainMenuePermission { eAll = -1, PListClient = 1, PAddNewClient = 2, PDeleteClient = 4, PUpdateClient = 8, PFindClient = 16, PTransactions = 32, PManageUsers = 64 };

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double Balance;
    bool MarkForDelete = false;
};

struct stUser
{
    string UserName;
    string Password;
    short Permission;
    bool MarkForDelete = false;
};

stUser CurrentUser;

const string ClientFileName = "Clients_Data.txt";
const string UserFileName = "Users.txt";

void ShowMainMenueScreen();
void ShowTransactionMenueScreen();
void PerfromTransactionsMenueOption(enTransactionsMenueOptions Option);
short ReadTransactionsMenueOption();
void Login();
bool CheckAccessPermission(enMainMenuePermission Permission);
void ShowManageUsersMenueScreen();
void ShowAccessDeniedMessage();

void ReturnToMainMenuScreen()
{
    cout << "\n\n\npress any key to go back to main menu...";
    system("pause > 0");
    ShowMainMenueScreen();
}

void ReturnToTransactionMenueScreen()
{
    cout << "\n\n\npress any key to go back to transaction menue screen...";
    system("pause > 0");
    ShowTransactionMenueScreen();
}

void ReturnToManageUserMenueScreen()
{
    cout << "\n\n\npress any key to go back to manage user menue screen...";
    system("pause > 0");
    ShowManageUsersMenueScreen();
}

void PrintTab(short Num)
{
    for (short i = 0; i < Num; i++)
    {
        cout << '\t';
    }
}

void PrintHorizantalSeperator(short Num)
{
    for (short i = 0; i < Num; i++)
    {
        cout << "_";
    }
}

void ShowAddClientScreen()
{
    cout << "\n------------------------------------\n";
    cout << "\tAdd New Clients Screen\n";
    cout << "------------------------------------\n";
    cout << "Adding New Client:\n";
}

void ShowDeleteClientScreen()
{
    cout << "\n------------------------------------\n";
    cout << "\tDelete Client Screen\n";
    cout << "------------------------------------\n";
}

void ShowUpdateClientInfoScreen()
{
    cout << "\n------------------------------------\n";
    cout << "\tUpdate Client Info Screen\n";
    cout << "------------------------------------\n";
}

void ShowFindClientScreen()
{
    cout << "\n------------------------------------\n";
    cout << "\tFind Client Screen\n";
    cout << "------------------------------------\n";
}

void ShowTransactionMenueScreen()
{
    if (!CheckAccessPermission(enMainMenuePermission::PTransactions))
    {
        ShowAccessDeniedMessage();
        ReturnToMainMenuScreen();
        return;
    }

    system("cls");
    cout << "===========================================\n";
    cout << "\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";

    PerfromTransactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}

void ShowDepositScreen()
{
    cout << "\n------------------------------------\n";
    cout << "\tDeposit Screen\n";
    cout << "------------------------------------\n";
}

void ShowWithdrawScreen()
{
    cout << "\n------------------------------------\n";
    cout << "\tWithdraw Screen\n";
    cout << "------------------------------------\n";
}

void ShowEndProgramScreen()
{
    cout << "------------------------------------\n";
    cout << "\tProgram Ends :-)\n";
    cout << "------------------------------------\n";
}

void ShowLoginScreen()
{
    cout << "\n------------------------------------\n";
    cout << "\tLogin Screen\n";
    cout << "------------------------------------\n";
}

void ShowAccessDeniedMessage()
{
    system("cls");

    cout << "\n------------------------------------\n";
    cout << "Access Denied, \nYou dont Have Permission To Do this,\nPlease Conact Your Admin.";
    cout << "\n------------------------------------\n";
}

void ShowAddUserScreen()
{
    cout << "\n------------------------------------\n";
    cout << "\tAdd New User Screen\n";
    cout << "------------------------------------\n";
    cout << "Adding New User:\n";
}

void ShowDeleteUserScreen()
{
    cout << "\n------------------------------------\n";
    cout << "\tDelete User Screen\n";
    cout << "------------------------------------\n";
}

void ShowUpdateUserInfoScreen()
{
    cout << "\n------------------------------------\n";
    cout << "\tUpdate User Info Screen\n";
    cout << "------------------------------------\n";
}

void ShowFindUserScreen()
{
    cout << "\n------------------------------------\n";
    cout << "\tFind User Screen\n";
    cout << "------------------------------------\n";
}

vector<string> SpliteString(string Str, string Delim)
{
    vector<string> VString;
    short Pos = 0;
    string Word = "";

    while ((Pos = Str.find(Delim)) != std::string::npos)
    {
        Word = Str.substr(0, Pos);

        if (Word != "")
        {
            VString.push_back(Word);
        }

        Str.erase(0, Pos + Delim.length());
    }

    if (Str != "")
    {
        VString.push_back(Str);
    }

    return VString;
}

stClient ConvertLineDataToRecord(string Line)
{
    vector<string> VString = SpliteString(Line, "#//#");
    stClient ClientRecord;

    ClientRecord.AccountNumber = VString[0];
    ClientRecord.PinCode = VString[1];
    ClientRecord.Name = VString[2];
    ClientRecord.Phone = VString[3];
    ClientRecord.Balance = stod(VString[4]);

    return ClientRecord;

}

string ConvertRecordToLineData(stClient ClientRecord, string Seperator = "#//#")
{
    string ClientLineData = "";

    ClientLineData += ClientRecord.AccountNumber + Seperator;
    ClientLineData += ClientRecord.PinCode + Seperator;
    ClientLineData += ClientRecord.Name + Seperator;
    ClientLineData += ClientRecord.Phone + Seperator;
    ClientLineData += to_string(ClientRecord.Balance) + Seperator;

    return ClientLineData.substr(0, ClientLineData.length() - Seperator.length());
}

string ConvertUserRecordToLineData(stUser User, string Seperator = "#//#")
{
    string UserLineData = "";

    UserLineData += User.UserName + Seperator;
    UserLineData += User.Password + Seperator;
    UserLineData += to_string(User.Permission) + Seperator;

    return UserLineData.substr(0, UserLineData.length() - Seperator.length());
}

stUser ConvertUserLineDataToRecord(string LineData)
{
    vector<string> VUser;
    stUser User;
    VUser = SpliteString(LineData, "#//#");

    User.UserName = VUser[0];
    User.Password = VUser[1];
    User.Permission = stoi(VUser[2]);

    return User;
}

void AddDataLineToFile(string FileName, string DataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << DataLine << endl;
        MyFile.close();
    }
}

vector<stClient> LoadClientDataFromFile(string FileName)
{
    vector<stClient> VClientData;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string LineData;
        stClient Client;

        while (getline(MyFile, LineData))
        {
            Client = ConvertLineDataToRecord(LineData);
            VClientData.push_back(Client);
        }

        MyFile.close();
    }

    return VClientData;
}

vector<stUser> LoadUserDataFromFile(string FileName)
{
    vector<stUser> VUser;

    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string LineData;
        stUser User;

        while (getline(MyFile, LineData))
        {
            User = ConvertUserLineDataToRecord(LineData);
            VUser.push_back(User);
        }

        MyFile.close();
    }

    return VUser;
}

bool ClientExistsByAccountNumber(string FileName, string AccountNumber)
{
    vector<stClient> VCLient;

    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineDataToRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }

            VCLient.push_back(Client);
        }

        MyFile.close();
    }

    return false;
}

bool UserExistsByUserName(string FileName, string UserName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string LineData;
        stUser User;

        while (getline(MyFile, LineData))
        {
            User = ConvertUserLineDataToRecord(LineData);

            if (User.UserName == UserName)
            {
                MyFile.close();
                return true;
            }
        }

        MyFile.close();
    }

    return false;
}

stClient ReadClient()
{
    stClient Client;

    cout << "\nEnter Account Number ? ";
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(ClientFileName, Client.AccountNumber))
    {
        cout << "\nClient with Account Number (" << Client.AccountNumber << ") already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "\nEnter Pin Code? ";
    getline(cin, Client.PinCode);

    cout << "\nEnter Name? ";
    getline(cin, Client.Name);

    cout << "\nEnter Phone? ";
    getline(cin, Client.Phone);

    cout << "\nEnter Account Balance? ";
    cin >> Client.Balance;

    return Client;
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nEnter Account Number? ";
    cin >> AccountNumber;

    return AccountNumber;
}

int ReadPermissionToSet()
{
    stUser User;
    int Permissions = 0;
    char Answer = 'n';

    cout << "\nDo you want to give full access? y/n?";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        return -1;

    cout << "\nDo you want to give access to:\n";

    cout << "\nShow Client List? y/n? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permissions += enMainMenuePermission::PListClient;

    cout << "\nAdd New Client? y/n? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permissions += enMainMenuePermission::PAddNewClient;

    cout << "\nDelete Client? y/n? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permissions += enMainMenuePermission::PDeleteClient;

    cout << "\nUpdate client? y/n? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permissions += enMainMenuePermission::PUpdateClient;

    cout << "\nFind client? y/n? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permissions += enMainMenuePermission::PFindClient;

    cout << "\nTransactions? y/n? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permissions += enMainMenuePermission::PTransactions;

    cout << "\nManage Users? y/n? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
        Permissions += enMainMenuePermission::PManageUsers;

    return Permissions;
}

stUser ReadNewUser()
{
    stUser User;

    cout << "\nEnter UserName? ";
    getline(cin >> ws, User.UserName);

    while (UserExistsByUserName(UserFileName, User.UserName))
    {
        cout << "\nUser with (" << User.UserName << ") already exists, Enter another UserName? ";
        getline(cin >> ws, User.UserName);
    }

    cout << "\nEnter Password? ";
    getline(cin, User.Password);

    User.Permission = ReadPermissionToSet();

    return User;
}

string ReadUserName()
{
    string UserName = "";
    cout << "\nEnter UserName? ";
    cin >> UserName;

    return UserName;
}

void PrintCLientRecord(stClient Client)
{
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(10) << Client.PinCode;
    cout << "| " << left << setw(40) << Client.Name;
    cout << "| " << left << setw(12) << Client.Phone;
    cout << "| " << left << setw(12) << Client.Balance;
}

void PrintUserRecord(stUser User)
{
    cout << "| " << left << setw(15) << User.UserName;
    cout << "| " << left << setw(10) << User.Password;
    cout << "| " << left << setw(7) << User.Permission;
}

void ShowClientList()
{
    if (!CheckAccessPermission(enMainMenuePermission::PListClient))
    {
        ShowAccessDeniedMessage();
        ReturnToMainMenuScreen();
        return;
    }

    vector<stClient> VClientList = LoadClientDataFromFile(ClientFileName);

    cout << endl;
    PrintTab(5);
    cout << "Client List (" << VClientList.size() << ") Client(s)\n\n";
    PrintHorizantalSeperator(96);
    cout << endl << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Client Phone";
    cout << "| " << left << setw(12) << "Balance";

    cout << endl;
    PrintHorizantalSeperator(96);
    cout << endl << endl;

    if (VClientList.size() == 0)
    {
        cout << "\nNo Clients Available in System.\n";
    }
    else
    {
        for (stClient C : VClientList)
        {
            PrintCLientRecord(C);
            cout << endl;
        }
    }

    cout << endl << endl;
    PrintHorizantalSeperator(96);
    cout << endl << endl << endl;
}

void ShowUserList()
{
    vector<stUser> VUser = LoadUserDataFromFile(UserFileName);

    cout << endl;
    PrintTab(5);
    cout << "User List (" << VUser.size() << ") User(s).\n\n";
    PrintHorizantalSeperator(96);

    cout << endl << endl;

    cout << "| " << left << setw(15) << "UserName";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(7) << "Permission";

    cout << endl;
    PrintHorizantalSeperator(96);
    cout << endl << endl;

    if (VUser.size() == 0)
    {
        cout << "\nNo Users Available in System.\n";
    }
    else
    {
        for (stUser User : VUser)
        {
            PrintUserRecord(User);
            cout << endl;
        }
    }

    cout << endl;
    PrintHorizantalSeperator(96);
    cout << endl << endl << endl;
}

void AddNewClient()
{
    stClient Client;
    Client = ReadClient();
    AddDataLineToFile(ClientFileName, ConvertRecordToLineData(Client));
}

void AddNewClients()
{
    if (!CheckAccessPermission(enMainMenuePermission::PAddNewClient))
    {
        ShowAccessDeniedMessage();
        ReturnToMainMenuScreen();
        return;
    }

    char AddMore = 'n';

    do
    {
        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more Clients? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

void AddNewUser()
{
    stUser User;
    User = ReadNewUser();
    AddDataLineToFile(UserFileName, ConvertUserRecordToLineData(User));
}

void AddNewUsers()
{
    char AddMore = 'n';

    do
    {
        AddNewUser();
        cout << "\nUser Added Successfully, do you want to add more Users? y/n?";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

void PrintClientCard(stClient Client)
{
    cout << "\nThe folowing are the Client details:";
    cout << "\n-----------------------------------";

    cout << "\nAccount Number: " << Client.AccountNumber;
    cout << "\nPin Code: " << Client.PinCode;
    cout << "\nName: " << Client.Name;
    cout << "\nPhone: " << Client.Phone;
    cout << "\nAccount Balance: " << Client.Balance;

    cout << "\n-----------------------------------";
}

void PrintUserCard(stUser User)
{
    cout << "\nThe folowing are the User details:";
    cout << "\n-----------------------------------";

    cout << "\nUserName: " << User.UserName;
    cout << "\nPassword: " << User.Password;
    cout << "\nPermission: " << User.Permission;

    cout << "\n-----------------------------------";
}

void SaveClientDataToFile(string FileName, vector<stClient> VClient)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        string Line;

        for (stClient Client : VClient)
        {
            if (Client.MarkForDelete == false)
            {
                Line = ConvertRecordToLineData(Client);
                MyFile << Line << endl;
            }
        }

        MyFile.close();
    }
}

void SaveUserDataToFile(string FileName, vector<stUser> VUser)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    string Line;

    if (MyFile.is_open())
    {
        for (stUser User : VUser)
        {
            if (User.MarkForDelete == false)
            {
                Line = ConvertUserRecordToLineData(User);
                MyFile << Line << endl;
            }
        }

        MyFile.close();
    }
}

bool MarkClientForDelete(vector<stClient>& VClient, string AccountNumber)
{
    for (stClient& C : VClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }

    return false;
}

bool MarkUserForDelete(vector<stUser>& VUser, string UserName)
{
    for (stUser& Usr : VUser)
    {
        if (Usr.UserName == UserName)
        {
            Usr.MarkForDelete = true;
            return true;
        }
    }

    return false;
}

bool FindClientByAccountNumber(vector<stClient> VCLientData, stClient& Client, string AccountNumber)
{
    for (stClient C : VCLientData)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }

    return false;
}

bool FindUserByUserName(vector<stUser> VUser, stUser& User, string UserName)
{
    for (stUser Usr : VUser)
    {
        if (Usr.UserName == UserName)
        {
            User = Usr;
            return true;
        }
    }

    return false;
}

bool DeleteClientByAccountNumber()
{
    if (!CheckAccessPermission(enMainMenuePermission::PDeleteClient))
    {
        ShowAccessDeniedMessage();
        ReturnToMainMenuScreen();
        return false;
    }

    vector<stClient> VClientData = LoadClientDataFromFile(ClientFileName);
    stClient Client;
    string AccountNumber = "";
    char ConfirmDeletion = 'n', Answer = 'n';

    do
    {
        AccountNumber = ReadClientAccountNumber();
        if (FindClientByAccountNumber(VClientData, Client, AccountNumber))
        {
            PrintClientCard(Client);
            cout << "\n\nAre you sure you want to delete this Client y/n ";
            cin >> ConfirmDeletion;

            if (toupper(ConfirmDeletion) == 'Y')
            {
                MarkClientForDelete(VClientData, AccountNumber);
                SaveClientDataToFile(ClientFileName, VClientData);
                VClientData = LoadClientDataFromFile(ClientFileName);

                cout << "\nClient Deleted Successfully.\n";
            }

            return true;
        }
        else
        {
            cout << "\nClient with Account Number (" << AccountNumber << ") is not found!\n";
            cout << "\ndo you want to Enter another Account Number? if Yes pleaes Enter (y) \n";
            cin >> Answer;

            if (toupper(Answer) != 'Y')
            {
                ReturnToMainMenuScreen();
            }
        }

    } while (toupper(Answer) == 'Y');

    return false;
}

bool DeleteUserByUserName()
{
    vector<stUser> VUser = LoadUserDataFromFile(UserFileName);
    stUser User;
    string UserName;
    char ConfirmDeletion = 'n', Answer = 'n';

    do
    {
        UserName = ReadUserName();

        if (UserName == "Admin")
        {
            cout << "\n\nYou cannot Delete This User.";
            return false;
        }

        if (FindUserByUserName(VUser, User, UserName))
        {
            PrintUserCard(User);
            cout << "\n\nAre you sure you want to delete this User y/n ";
            cin >> ConfirmDeletion;

            if (toupper(ConfirmDeletion) == 'Y')
            {
                MarkUserForDelete(VUser, UserName);
                SaveUserDataToFile(UserFileName, VUser);
                VUser = LoadUserDataFromFile(UserFileName);

                cout << "\nUser Deleted Successfully.\n";
            }

            return true;
        }
        else
        {
            cout << "\nUser with (" << UserName << ") is not found!\n";
            cout << "do you want to Enter another UserName? if Yes pleaes Enter (y)";
            cin >> Answer;

            if (toupper(Answer) != 'Y')
            {
                return false;
            }
        }

    } while (toupper(Answer) == 'Y');

    return false;
}

stClient UpdateClientInfo(string AccountNumber)
{
    stClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\nEnter Pin Code? ";
    getline(cin >> ws, Client.PinCode);

    cout << "\nEnter Name? ";
    getline(cin, Client.Name);

    cout << "\nEnter Phone? ";
    getline(cin, Client.Phone);

    cout << "\nEnter Account Balance? ";
    cin >> Client.Balance;

    return Client;
}

stUser UpdateUserInfo(string UserName)
{
    stUser User;

    User.UserName = UserName;

    cout << "\nEnter Password? ";
    getline(cin >> ws, User.Password);

    User.Permission = ReadPermissionToSet();

    return User;
}

bool UpdateClientInfoByAccountNumber()
{
    if (!CheckAccessPermission(enMainMenuePermission::PUpdateClient))
    {
        ShowAccessDeniedMessage();
        ReturnToMainMenuScreen();
        return false;
    }

    vector<stClient> VClientData = LoadClientDataFromFile(ClientFileName);
    stClient Client;
    string AccountNumber = ReadClientAccountNumber();
    char ConfirmUpdate = 'n';

    if (FindClientByAccountNumber(VClientData, Client, AccountNumber))
    {
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want to Update this Client? y/n? ";
        cin >> ConfirmUpdate;

        if (toupper(ConfirmUpdate) == 'Y')
        {
            for (stClient& C : VClientData)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = UpdateClientInfo(AccountNumber);
                    break;
                }
            }

            SaveClientDataToFile(ClientFileName, VClientData);
            VClientData = LoadClientDataFromFile(ClientFileName);
            cout << "\nClient Updated Successfully.\n";

            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is not found!\n";
    }

    return false;
}

bool UpdateUserInfoByUserName()
{
    vector<stUser> VUSer = LoadUserDataFromFile(UserFileName);
    stUser User;
    string UserName = ReadUserName();
    char ConfirmUpdate = 'n';

    if (FindUserByUserName(VUSer, User, UserName))
    {
        PrintUserCard(User);
        cout << "\n\nAre you sure you want to Update this User? y/n? ";
        cin >> ConfirmUpdate;

        if (toupper(ConfirmUpdate) == 'Y')
        {
            for (stUser& User : VUSer)
            {
                if (User.UserName == UserName)
                {
                    User = UpdateUserInfo(UserName);
                    break;
                }
            }

            SaveUserDataToFile(UserFileName, VUSer);
            VUSer = LoadUserDataFromFile(UserFileName);
            cout << "\nUser Updated Successfully.\n";

            return true;
        }
    }
    else
    {
        cout << "\nUser with (" << UserName << ") is not found!\n";
    }

    return false;
}

bool FindClient()
{
    if (!CheckAccessPermission(enMainMenuePermission::PFindClient))
    {
        ShowAccessDeniedMessage();
        ReturnToMainMenuScreen();
        return false;
    }

    vector<stClient> VClientData = LoadClientDataFromFile(ClientFileName);
    stClient Client;
    string AccountNumber = ReadClientAccountNumber();

    if (FindClientByAccountNumber(VClientData, Client, AccountNumber))
    {
        PrintClientCard(Client);
        return true;
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is not found!\n";
        return false;
    }
}

bool FindUser()
{
    vector<stUser> VUser = LoadUserDataFromFile(UserFileName);
    stUser User;
    string UserName = ReadUserName();

    if (FindUserByUserName(VUser, User, UserName))
    {
        PrintUserCard(User);
        return true;
    }
    else
    {
        cout << "\nUser with (" << UserName << ") is not found!\n";
        return false;
    }
}

double ReadDepositAmount()
{
    double DepositAmount;
    cout << "\n\nPlease enter deposit amount? ";
    cin >> DepositAmount;

    return DepositAmount;
}

double ReadWithdrawAmount()
{
    double WithdrawAmount;
    cout << "\n\nPlease enter withdraw amount? ";
    cin >> WithdrawAmount;

    return WithdrawAmount;
}

bool PerformDepositTransaction(vector<stClient>& VClient, double Amount, string AccountNumber, bool IsForWithdrawAmount = false)
{
    stClient Client;
    char Answer = 'n';

    cout << "\nAre you sure you want perform this transaction? y/n? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
    {
        for (stClient& C : VClient)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.Balance += Amount;
                Client = C;
                break;
            }
        }

        if (!IsForWithdrawAmount)
        {
            cout << "\nDeposit Amount done Successfully, new balance is: " << Client.Balance << endl;
        }

        SaveClientDataToFile(ClientFileName, VClient);
        return true;
    }

    return false;
}

void Deposit()
{
    vector<stClient> VClient = LoadClientDataFromFile(ClientFileName);
    stClient Client;
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(VClient, Client, AccountNumber))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);
    double DepositAmount = ReadDepositAmount();
    PerformDepositTransaction(VClient, DepositAmount, AccountNumber);
}

bool Withdraw()
{
    vector<stClient> VClient = LoadClientDataFromFile(ClientFileName);
    stClient Client;
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(VClient, Client, AccountNumber))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double WithdrawAmount = ReadWithdrawAmount();

    while (WithdrawAmount > Client.Balance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.Balance << endl;
        cout << "\nPlease Enter another amount? ";
        cin >> WithdrawAmount;
    }

    if (PerformDepositTransaction(VClient, WithdrawAmount * -1, AccountNumber, true))
    {
        cout << "\nWithdraw Amount done Successfully, new balance is: " << Client.Balance - WithdrawAmount << endl;
        return true;
    }

    return false;
}

int CountTotalBalances(vector<stClient> VClient)
{
    int TotalBalance = 0;

    for (stClient C : VClient)
    {
        TotalBalance += C.Balance;
    }

    return TotalBalance;
}

void PrintTotalBalances(stClient Client)
{
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(40) << Client.Name;
    cout << "| " << left << setw(12) << Client.Balance;
}

void ShowTotalBalancesScreen()
{
    vector<stClient> VClientList = LoadClientDataFromFile(ClientFileName);

    cout << endl;
    PrintTab(5);
    cout << "Balances List (" << VClientList.size() << ") Client(s)\n\n";
    PrintHorizantalSeperator(96);
    cout << endl << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";

    cout << endl;
    PrintHorizantalSeperator(96);
    cout << endl << endl;

    if (VClientList.size() == 0)
    {
        cout << "\nNo Clients Available in System.\n";
    }
    else
    {
        for (stClient C : VClientList)
        {
            PrintTotalBalances(C);
            cout << endl;
        }
    }

    cout << endl << endl;
    PrintHorizantalSeperator(96);
    cout << endl << endl << endl;
    PrintTab(5);
    cout << "Total Balances = " << CountTotalBalances(VClientList);
}

bool CheckAccessPermission(enMainMenuePermission Permission)
{
    if (CurrentUser.Permission == enMainMenuePermission::eAll)
        return true;

    if ((CurrentUser.Permission & Permission) == Permission)
        return true;
    else
        return false;
}

short ReadMainMenueOption()
{
    short Choice = 0;
    cout << "Choose what do you want to do [1 to 8]? ";
    cin >> Choice;

    return Choice;
}

short ReadTransactionsMenueOption()
{
    short Choice = 0;
    cout << "Choose what do you want to do [1 to 4]? ";
    cin >> Choice;

    return Choice;
}

short ReadManageUserMenueOption()
{
    short Choice = 0;
    cout << "Choose what do you want to do [1 to 6]? ";
    cin >> Choice;

    return Choice;
}

void PerfromTransactionsMenueOption(enTransactionsMenueOptions Option)
{
    switch (Option)
    {
    case enTransactionsMenueOptions::eDeposit:
        system("cls");
        ShowDepositScreen();
        Deposit();
        ReturnToTransactionMenueScreen();
        break;
    case enTransactionsMenueOptions::eWithdraw:
        system("cls");
        ShowWithdrawScreen();
        Withdraw();
        ReturnToTransactionMenueScreen();
        break;
    case enTransactionsMenueOptions::eTotalBalances:
        system("cls");
        ShowTotalBalancesScreen();
        ReturnToTransactionMenueScreen();
        break;
    case enTransactionsMenueOptions::eMainMenue:
        ShowMainMenueScreen();
    }
}

void PerfromMainMenueOption(enMainMenueOptions Option)
{
    switch (Option)
    {
    case enMainMenueOptions::eShowListClient:
        system("cls");
        ShowClientList();
        ReturnToMainMenuScreen();
        break;
    case enMainMenueOptions::eAddClient:
        system("cls");
        ShowAddClientScreen();
        AddNewClients();
        ReturnToMainMenuScreen();
        break;
    case enMainMenueOptions::eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        DeleteClientByAccountNumber();
        ReturnToMainMenuScreen();
        break;
    case enMainMenueOptions::eUpdateClient:
        system("cls");
        ShowUpdateClientInfoScreen();
        UpdateClientInfoByAccountNumber();
        ReturnToMainMenuScreen();
        break;
    case enMainMenueOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        FindClient();
        ReturnToMainMenuScreen();
        break;
    case enMainMenueOptions::eTransactions:
        system("cls");
        ShowTransactionMenueScreen();
        break;
    case enMainMenueOptions::eManageUsers:
        ShowManageUsersMenueScreen();
        break;
    case enMainMenueOptions::eLogout:
        system("cls");
        Login();
        break;
    }
}

void PerfromManageUserMenueOption(enManageUserMenueOption Option)
{
    switch (Option)
    {
    case enManageUserMenueOption::eListUsers:
        system("cls");
        ShowUserList();
        ReturnToManageUserMenueScreen();
        break;
    case enManageUserMenueOption::eAddUser:
        system("cls");
        ShowAddUserScreen();
        AddNewUsers();
        ReturnToManageUserMenueScreen();
        break;
    case enManageUserMenueOption::eDeleteUser:
        system("cls");
        ShowDeleteUserScreen();
        DeleteUserByUserName();
        ReturnToManageUserMenueScreen();
        break;
    case enManageUserMenueOption::eUpdateUser:
        system("cls");
        ShowUpdateUserInfoScreen();
        UpdateUserInfoByUserName();
        ReturnToManageUserMenueScreen();
        break;
    case enManageUserMenueOption::eFindUser:
        system("cls");
        ShowFindUserScreen();
        FindUser();
        ReturnToManageUserMenueScreen();
        break;
    case enManageUserMenueOption::MainMenue:
        system("cls");
        ShowMainMenueScreen();
        break;
    }
}

void ShowManageUsersMenueScreen()
{
    if (!CheckAccessPermission(enMainMenuePermission::PManageUsers))
    {
        ShowAccessDeniedMessage();
        ReturnToMainMenuScreen();
        return;
    }

    system("cls");
    cout << "===========================================\n";
    cout << "\tManage Users Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue.\n";
    cout << "===========================================\n";

    PerfromManageUserMenueOption((enManageUserMenueOption)ReadManageUserMenueOption());
}

void ShowMainMenueScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "===========================================\n";

    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

bool FindUserByUserNameAndPassword(string UserName, string Password, stUser& User)
{
    vector<stUser> VUSer = LoadUserDataFromFile(UserFileName);

    for (stUser U : VUSer)
    {
        if (U.UserName == UserName && U.Password == Password)
        {
            CurrentUser = U;
            return true;
        }
    }

    return false;
}

bool LoadUserInfo(string UserName, string Password)
{
    if (FindUserByUserNameAndPassword(UserName, Password, CurrentUser))
        return true;
    else
        return false;
}

void Login()
{
    string UserName, Password;
    bool LoginFaild = false;
    ShowLoginScreen();

    do
    {
        if (LoginFaild)
        {
            cout << "\nInvalid UserName / Password!\n";
        }

        cout << "\nEnter UserName? ";
        cin >> UserName;

        cout << "\nEnter Password? ";
        cin >> Password;

        LoginFaild = !LoadUserInfo(UserName, Password);

    } while (LoginFaild);

    ShowMainMenueScreen();
}

int main()
{
    Login();
    system("pause > 0");
    return 0;
}