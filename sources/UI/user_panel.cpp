#include "../../headers/UI/user_panel.h"


namespace userPanelNS
{
	void accountsList(User user);
	void loansList(User user);
	void banksList();
	void transferMoney(User user);
	void createAccount(User user);
	void applyLoan(User user);
}

void userPanel(User authenticatedUser)
{
	using namespace userPanelNS;
	while (true)
	{
		system("cls");
		std::cout << std::endl << bright << yellow << "             Welcome " << authenticatedUser.name << reset << std::endl;
		std::cout << std::endl << cyan << "  User Panel :" << reset << std::endl << std::endl;
		std::cout << "    1.Accounts List" << std::endl;
		std::cout << "    2.Loans List" << std::endl;
		std::cout << "    3.Banks List" << std::endl;
		std::cout << "    4.Transfer Money" << std::endl;
		std::cout << "    5.Create Bank Account" << std::endl;
		std::cout << "    6.Apply for a loan" << std::endl;
		std::cout << "    7.Change Profile" << std::endl;
		std::cout << "    8.Exit" << std::endl;

		int input = getMenuInput(6);
		switch (input)
		{
		case 1:
			accountsList(authenticatedUser);
			break;
		case 2:
			loansList(authenticatedUser);
			break;
		case 3:
			banksList();
			break;
		case 4:
			transferMoney(authenticatedUser);
			break;
		case 5:
			createAccount(authenticatedUser);
			break;
		case 6:
			applyLoan(authenticatedUser);
			break;
		case -1:
			return;
		case 8:
			exit(0);
		}
	}
}

namespace userPanelNS
{
	void accountsList(User user)
	{
		system("cls");
		std::cout << std::endl << cyan << "  Accounts :" << reset << std::endl << std::endl;
		for (int i = 0; i < user.accounts.size(); i++)
		{
			BankAccount acc = BankAccount::getAccountStruct(user.accounts[i]);
			Bank bank = Bank::getBankStruct(acc.fBankId);
			std::cout << "    " << std::to_string(i + 1) << "." << std::endl;
			std::cout << bright << cyan << "    ==========================================" << reset << std::endl;
			std::cout << bright << yellow << "      AccountId: " << acc.id << reset << std::endl << std::endl;
			std::cout << bright << green << "      Account Balance: " << acc.balance << reset << std::endl << std::endl;

			std::string accountType = "";
			switch (acc.type)
			{
			case 1:
				accountType = "Short-Term";
				break;
			case 2:
				accountType = "Long-Term";
				break;
			case 3:
				accountType = "Special";
				break;
			}
			std::cout << "      Account Type: " << accountType << std::endl << std::endl;

			std::cout << "      BankId: " << bank.id << "      Bank name: " << bank.name << std::endl << std::endl;

			std::string accountStatus = "";
			switch (acc.status)
			{
			case -1:
				accountStatus = red + "Rejected" + reset;
				break;
			case 0:
				accountStatus = yellow + "Pending" + reset;
				break;
			case 1:
				accountStatus = green + "Accepted" + reset;
				break;
			}
			std::cout << "      Account status: " << accountStatus << std::endl ;
			std::cout << bright << cyan << "    ==========================================" << reset << std::endl << std::endl;
		}
		std::string tmp;
		std::getline(std::cin, tmp);
	}

	void loansList(User user)
	{
		system("cls");
		std::cout << std::endl << cyan << "  Loans :" << reset << std::endl << std::endl;
		for (int i = 0; i < user.accounts.size(); i++)
		{
			Loan loan = Loan::getLoanStruct(user.loans[i]);
			Bank bank = Bank::getBankStruct(loan.fBankId);
			BankAccount payAcc = BankAccount::getAccountStruct(loan.fPaymentAccount);

			std::cout << "    " << std::to_string(i + 1) << "." << std::endl;
			std::cout << bright << cyan << "    ==========================================" << reset << std::endl;
			std::cout << bright << green << "      LoanId: " << loan.id << reset << std::endl;
			std::cout << bright << yellow << "      Loan amount: " << loan.amount << reset << std::endl;
			
			std::cout << "      Request account: " << loan.fRequestAccount << std::endl;
			std::cout << "      Payment account: " << payAcc.id << "      Balance: " << payAcc.balance << std::endl;
			
			std::cout << "      BankId: " << bank.id << "      Bank name: " << bank.name << std::endl;

			std::string accountStatus = "";
			switch (loan.status)
			{
			case -1:
				accountStatus = red + "Rejected" + reset;
				break;
			case 0:
				accountStatus = yellow + "Pending" + reset;
				break;
			case 1:
				accountStatus = green + "Accepted" + reset;
				break;
			}
			std::cout << "      Account status: " << accountStatus << std::endl;
			
			std::cout << "      Payments count: " << loan.countOfPayments << std::endl;
			if(loan.countOfPayments)
				std::cout << "      Last payment date: " << getDateTime(loan.lastTimePayed) << std::endl;
			std::cout << "      Requisition Date: " << getDateTime(loan.requisitionDate) << std::endl;
			std::cout << bright << cyan << "    ==========================================" << reset << std::endl << std::endl;
		}
		std::string tmp;
		std::getline(std::cin, tmp);
	}

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
			std::cout << "      Foundation Date: " << getDateTime(allBanks[i].foundationDate) << std::endl;
			std::cout << bright << cyan << "    ==========================================" << reset << std::endl << std::endl;
		}
		std::string tmp;
		std::getline(std::cin, tmp);
	}

	void transferMoney(User user)
	{

	}

	void createAccount(User user)
	{
		system("cls");
		std::cout << std::endl;
		int bankId = getIntInput("BankId");
		if (bankId == -1) return;
		while (!Bank::exists(bankId))
		{
			std::cout << red << "    invalid BankId!" << reset << std::endl;
			bankId = getIntInput("BankId");
			if (bankId == -1) return;
		}

		int type = getIntInput("Type(1: short-term, 2: long-term, 3: special)");
		if (type == -1) return;
		while (type < 1 || type > 3)
		{
			std::cout << red << "    invalid Account-Type!" << reset << std::endl;
			type = getIntInput("Type(1: short-term, 2: long-term, 3: special)");
			if (type == -1) return;
		}

		int balance = getIntInput("Balance");
		if (balance == -1) return;
		while (balance < 0 || balance > 50000)
		{
			if (balance < 0)
				std::cout << red << "    invalid Balance!" << reset << std::endl;
			else if (balance > 50000)
				std::cout << red << "    its too much :)!" << reset << std::endl;

			balance = getIntInput("Balance");
			if (balance == -1) return;
		}

		BankAccount acc = newBankAccount(user.username, bankId, type, balance);
		user.accounts.push_back(acc.id);
		User::addOrUpdateUser(user);

		std::cout << std::endl << green << bright << "Requisition has been sent to bank!" << reset << std::endl;
		_sleep(1200);
	}

	void applyLoan(User user)
	{

	}
}