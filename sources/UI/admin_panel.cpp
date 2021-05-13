#include "../../headers/UI/admin_panel.h"

namespace adminPanelNS
{
	void banksList();
	void usersList();
	void addBank();
	void promoteUser();
	void demoteUser();
}


void adminPanel(User authenticatedUser)
{
	using namespace adminPanelNS;
	while (true)
	{
		system("cls");
		std::cout << std::endl << bright << yellow << "             Welcome " << authenticatedUser.name << reset << std::endl;
		std::cout << std::endl << cyan << "  Admin Panel :" << reset << std::endl << std::endl;
		std::cout << "    1.Banks List" << std::endl;
		std::cout << "    2.Users List" << std::endl;
		std::cout << "    3.Add Bank" << std::endl;
		std::cout << "    4.Promote user to manager" << std::endl;
		std::cout << "    5.Demote user" << std::endl;
		std::cout << "    6.Exit" << std::endl;

		int input = getMenuInput(6);
		switch (input)
		{
		case 1:
			banksList();
			break;
		case 2:
			usersList();
			break;
		case 3:
			addBank();
			break;
		case 4:
			promoteUser();
			break;
		case 5:
			demoteUser();
			break;
		case -1:
			return;
		case 6:
			exit(0);
		}
	}
}

namespace adminPanelNS
{
	void banksList()
	{
		system("cls");
		std::cout << std::endl << cyan << "  Banks :" << reset << std::endl << std::endl;
		std::vector<Bank> allBanks = Bank::getAllBanks();
		for (int i = 0; i < allBanks.size(); i++)
		{
			std::cout << "    " << std::to_string(i + 1) << "." << std::endl;
			std::cout << bright << cyan << "    ==========================================" << reset << std::endl;
			std::cout << bright << green << "      BankId: " << allBanks[i].id << reset << std::endl << std::endl;
			std::cout << bright << yellow << "      Bank name: " << allBanks[i].name << reset << std::endl << std::endl;
			std::cout << "      Total Balance: " << allBanks[i].totalBalance << std::endl << std::endl;

			std::cout << bright << magenta << "      Managers: " << std::endl;
			for (int j = 0; j < allBanks[i].managers.size(); j++)
				std::cout << "        " << allBanks[i].managers[j] << std::endl;
			std::cout << reset << std::endl;

			std::cout << "      Foundation Date: " << getDateTime(allBanks[i].foundationDate) << std::endl;
			std::cout << bright << cyan << "    ==========================================" << reset << std::endl << std::endl;
		}
		std::string tmp;
		std::getline(std::cin, tmp);
	}

	void usersList()
	{
		system("cls");
		std::cout << std::endl << cyan << "  Users :" << reset << std::endl << std::endl;
		std::vector<User> allUsers = User::getAllUsers();
		for (int i = 0; i < allUsers.size(); i++)
		{
			std::cout << "    " << std::to_string(i + 1) << "." << std::endl;
			std::cout << bright << cyan << "    ==========================================" << reset << std::endl;

			std::cout << "      Username: " << allUsers[i].username << std::endl;

			std::string userType = "";
			switch (allUsers[i].type)
			{
			case 1:
				userType = "Normal user";
				break;
			case 2:
				userType = "Bank manager";
				break;
			case 3:
				userType = "Full admin";
				break;
			}
			std::cout << "      User type: " << userType << std::endl;
			std::cout << "      Full name: " << allUsers[i].name << std::endl;
			std::cout << "      Phone number: " << allUsers[i].phoneNO << std::endl;
			if (allUsers[i].isBlocked)
				std::cout << bright << red << "      Is blocked: True" << reset << std::endl;
			else
				std::cout << bright << green << "      Is blocked: False" << reset << std::endl;

			std::cout << bright << cyan << "    ==========================================" << reset << std::endl << std::endl;
		}
		std::string tmp;
		std::getline(std::cin, tmp);
	}

	void addBank()
	{
		std::cout << std::endl << cyan << " Add Bank" << reset << std::endl << std::endl;

		std::string bankName = getStringInput("Bank Name", true, true);
		if (bankName == "-1") return;

		int balance = getIntInput("Total Balance");
		if (balance == -1) return;

		newBank(bankName, balance);

		std::cout << std::endl << green << bright << "Bank has been added successfully!" << reset << std::endl;
		_sleep(1200);
		system("cls");
	}

	void promoteUser()
	{
		std::cout << std::endl << cyan << " Promote User" << reset << std::endl << std::endl;

		std::string username = getStringInput("Username");
		if (username == "-1") return;
		while (!User::exists(username))
		{
			std::cout << red << "    Username doesn't exist!" << reset << std::endl;
			username = getStringInput("Username");
			if (username == "-1") return;
		}

		User manager = User::getUserStruct(username);
		if (manager.type == 1)
		{
			int bankId = getIntInput("BankId");
			if (bankId == -1) return;
			while (!Bank::exists(bankId))
			{
				std::cout << red << "    invalid BankId!" << reset << std::endl;
				bankId = getIntInput("BankId");
				if (bankId == -1) return;
			}

			manager.type = 2;
			manager.bankId = bankId;
			User::addOrUpdateUser(manager);

			Bank bank = Bank::getBankStruct(bankId);
			bank.managers.push_back(manager.username);
			Bank::addOrUpdateBank(bank);
			std::cout << std::endl << green << bright << "Manager has been successfully added to bank!" << reset << std::endl;
		}
		else
			std::cout << red << "    User is already a bank manager!" << reset << std::endl;

		_sleep(1200);
		system("cls");
	}

	void demoteUser()
	{
		std::cout << std::endl << cyan << " Demote User" << reset << std::endl << std::endl;

		std::string username = getStringInput("Username");
		if (username == "-1") return;
		while (!User::exists(username))
		{
			std::cout << red << "    Username doesn't exist!" << reset << std::endl;
			username = getStringInput("Username");
			if (username == "-1") return;
		}


		User manager = User::getUserStruct(username);
		manager.type = 1;

		Bank bank = Bank::getBankStruct(manager.bankId);
		bank.managers.erase(std::remove(bank.managers.begin(), bank.managers.end(), manager.username), bank.managers.end());
		Bank::addOrUpdateBank(bank);

		manager.bankId = 0;
		User::addOrUpdateUser(manager);

		std::cout << std::endl << green << bright << "Manager has been successfully removed from bank!" << reset << std::endl;
		_sleep(1200);
		system("cls");
	}
}