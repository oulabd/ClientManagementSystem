﻿#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>

using namespace std;
const string ClientsFileName = "Client.txt";

void ShowMainMenue();
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

vector<string> SplitString(string S1, string Delim)
{
	vector<string> vString;
	short pos = 0;
	string sWord;
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + Delim.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1);
	}
	return vString;
}
sClient ConvertLineToRecord(string Line, string Seperator = "#//#")
{
	sClient Client;
	vector<string> vClientData;
	vClientData = SplitString(Line, Seperator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;

}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
	vector<sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return false;
}
sClient ReadNewClient()
{
	sClient Client;
	cout << "Enter Account Number?";
	getline(cin >> ws, Client.AccountNumber);
	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		cout << "\nClient with ( " << Client.AccountNumber << " ) already exists, enter another Account Number?";
		getline(cin >> ws, Client.AccountNumber);
	}
	cout << "Enter PinCode?";
	getline(cin, Client.PinCode);

	cout << "Enter Name?";
	getline(cin, Client.Name);

	cout << "Enter Phone?";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance?";
	cin >> Client.AccountBalance;

	return Client;

}

vector<sClient> LoadClientsDataFromFile(string FileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();

	}
	return vClients;

}

void PrintClientRecordLine(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsScreen()
{
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
		cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	if (vClients.size() == 0)
		cout << "\t\t\t\tNo clients avaiable in the system!";
	else
		for (sClient client : vClients)
		{
			PrintClientRecordLine(client);
			cout << endl;
		}
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void PrintClientCard(sClient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "-----------------------------------";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code : " << Client.PinCode;
	cout << "\nName : " << Client.Name;
	cout << "\nPhone : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << "\n-----------------------------------\n";
}
bool FindClientByAccountNumber(string AccountNumber, vector
	<sClient> vClients, sClient& Client)
{
	for (sClient C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;
	Client.AccountNumber = AccountNumber;
	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
vector <sClient> SaveCleintsDataToFile(string FileName, vector
	<sClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient C : vClients)
		{
			if (C.MarkForDelete == false)
			{
					DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}
void AddDataLineToFile(string FileName, string stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;
		MyFile.close();
	}
}
void AddNewClient()
{
	sClient Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));

}
void AddNewClients()
{
	char AddMore = 'Y';
	do
	{
		cout << "Adding new clients\n\n";
		AddNewClient();
		cout << "\nclient added successfully, dod you want to add a new clients? Y/N?";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}
bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients,Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want delete this client? y/n? ";
			cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveCleintsDataToFile(ClientsFileName, vClients);
			vClients = LoadClientsDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		return false;
	}
}
bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want update this client? y/n? ";
			cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveCleintsDataToFile(ClientsFileName, vClients);
			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}
}
string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}

void ShowDeleteClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------\n";
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);
}
void ShowUpdateClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Client Info Screen";
	cout << "\n-----------------------------------\n";
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
}
void ShowAddNewClientsScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n-----------------------------------\n";
	AddNewClients();
}
void ShowFindClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------\n";
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	sClient Client;
	string AccountNumber = ReadClientAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClients,
		Client))
		PrintClientCard(Client);
	else
		cout << "\nClient with Account Number[" << AccountNumber
		<< "] is not found!";
}
void ShowEndScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tProgram Ends :-)";
	cout << "\n-----------------------------------\n";
}
enum enMainMenueOptions
{
	eListClients = 1, eAddNewClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5, eExit = 6
};

void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to main menue...";
	system("pause>0");
	ShowMainMenue();
}

short ReadMainMenueOption()
{
	cout << "choose what do you want to do? [1 to 6]?";
	short Choice = 0;
	cin >> Choice;
	
	return Choice;
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
	 switch(MainMenueOption)
	 {
	 case enMainMenueOptions::eListClients:
	 {
		 system("cls");
		 ShowAllClientsScreen();
		 GoBackToMainMenue();
		 break;
	 }
	 case enMainMenueOptions::eAddNewClient:
		 system("cls");
		 ShowAddNewClientsScreen();
		 GoBackToMainMenue();
		 break;
	 case enMainMenueOptions::eDeleteClient:
		 system("cls");
		 ShowDeleteClientScreen();
		 GoBackToMainMenue();
		 break;
	 case enMainMenueOptions::eUpdateClient:
		 system("cls");
		 ShowUpdateClientScreen();
		 GoBackToMainMenue();
		 break;
	 case enMainMenueOptions::eFindClient:
		 system("cls");
		 ShowFindClientScreen();
		 GoBackToMainMenue();
		 break;
	 case enMainMenueOptions::eExit:
		 system("cls");
		 ShowEndScreen();
		 break;
	 }
}

void ShowMainMenue()
{
	system("cls");
	cout << "==========================================\n";
	cout << "\t\tmain menue screen\n";
	cout << "==========================================\n";
	cout << "\t[1] Show client list.\n";
	cout << "\t[2] Add new client\n";
	cout << "\t[3] Delete client\n";
	cout << "\t[4] Update client info\n";
	cout << "\t[5] Find client\n";
	cout << "\t[6] Exit\n";
	cout << "==========================================\n";
	PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

int main()
{
	ShowMainMenue();
	system("pause>0");
	return 0;
}