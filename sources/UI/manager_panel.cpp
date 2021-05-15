#include "../../headers/UI/manager_panel.h"

namespace managerPanelNS
{
	void accountRequests(Bank& bank);
	void loanApplications(Bank& bank);
	void allAccounts(Bank& bank);
	void allLoans(Bank& bank);
}

void managerPanel(User& authenticatedUser)
{
	using namespace managerPanelNS;
	while (true)
	{
		Bank workingBank = Bank::getBankStruct(authenticatedUser.bankId);
		system("cls");
		std::cout << std::endl << bright << yellow << "             Welcome " << authenticatedUser.name << reset << std::endl;
		std::cout << std::endl << cyan << "  Manager of " + workingBank.name + " :" << reset << std::endl << std::endl;
		std::cout << "    1.Account Requests" << std::endl;
		std::cout << "    2.Loan Applications" << std::endl;
		std::cout << "    3.All Accounts" << std::endl;
		std::cout << "    4.All Loans" << std::endl;
		std::cout << "    5.Edit Profile" << std::endl;
		std::cout << "    6.Exit" << std::endl;

		int input = getMenuInput(6);
		switch (input)
		{
		case 1:
			accountRequests(workingBank);
			break;
		case 2:
			loanApplications(workingBank);
			break;
		case 3:
			allAccounts(workingBank);
			break;
		case 4:
			allLoans(workingBank);
			break;
		case 5:
			editProfileNS::editProfile(authenticatedUser);
			break;
		case -1:
			return;
		case 6:
			exit(0);
		}
	}
}

namespace managerPanelNS
{
	void accountRequests(Bank& bank)
	{
		while (true)
		{
			system("cls");
			std::cout << std::endl << cyan << "  Account Requests :" << reset << std::endl << std::endl;
			for (int i = 0; i < bank.accounts.size(); i++)
			{
				BankAccount account = BankAccount::getAccountStruct(bank.accounts[i]);
				if (account.status == 0)
				{
					std::cout << "    " << std::to_string(i + 1) << "." << std::endl;
					std::cout << bright << cyan << "    ==========================================" << reset << std::endl;
					std::cout << bright << green << "      AccountId: " << account.id << reset << std::endl;
					std::cout << bright << yellow << "      User: " << account.fUsername << reset << std::endl;
					std::cout << "      Account Balance: " << account.balance << std::endl;

					std::string accountType = "";
					switch (account.type)
					{
					case 1:
						accountType = yellow + "Short-Term" + reset;
						break;
					case 2:
						accountType = green + "Long-Term" + reset;
						break;
					case 3:
						accountType = blue + "Special" + reset;
						break;
					}
					std::cout << "      Account Type: " << accountType << std::endl;

					std::cout << "      Requisition Date: " << getDateTime(account.createDate, true) << std::endl;
					std::cout << bright << cyan << "    ==========================================" << reset << std::endl << std::endl;
				}
			}
			std::cout << std::endl << cyan << "  Verify Account :" << reset << std::endl << std::endl;
			int objId = getIntInput("AccountId(-1:back)");
			if (objId == -1) return;
			BankAccount tmp;
			while (!BankAccount::exists(objId) || (tmp = BankAccount::getAccountStruct(objId)).fBankId != bank.id || tmp.status != 0)
			{
				std::cout << red << "    AccountId is invalid!" << reset << std::endl;
				objId = getIntInput("AccountId(-1:back)");
				if (objId == -1) return;
			}
			int verificationStatus = getIntInput("Accept(1:accept, 2:reject)");
			if (verificationStatus == -1) return;
			while (verificationStatus != 1 && verificationStatus != 2)
			{
				std::cout << red << "    invalid input!" << reset << std::endl;
				verificationStatus = getIntInput("Accept(1:accept, 2:reject)");
				if (verificationStatus == -1) return;
			}

			if (verificationStatus == 1) tmp.status = 1;
			else tmp.status = -1;
			tmp.lastInterestDate = time(0);
			BankAccount::addOrUpdateAccount(tmp);
			std::cout << std::endl << green << bright << "Done!" << reset << std::endl;
		}
	}

	void loanApplications(Bank& bank)
	{
		while (true)
		{
			system("cls");
			std::cout << std::endl << cyan << "  Loan Applications :" << reset << std::endl << std::endl;
			for (int i = 0; i < bank.loans.size(); i++)
			{
				Loan loan = Loan::getLoanStruct(bank.loans[i]);
				if (loan.status == 0)
				{
					BankAccount reqAcc = BankAccount::getAccountStruct(loan.fRequestAccount);
					std::cout << "    " << std::to_string(i + 1) << "." << std::endl;
					std::cout << bright << cyan << "    ==========================================" << reset << std::endl;
					std::cout << bright << green << "      LoanId: " << loan.id << reset << std::endl;
					std::cout << bright << yellow << "      User: " << reqAcc.fUsername << reset << std::endl;
					std::cout << bright << yellow << "      Amount: " << loan.amount << reset << std::endl;
					std::cout << "      Payments Count: " << loan.countOfPayments << std::endl;
					std::cout << "      Requisition Date: " << getDateTime(loan.requisitionDate, true) << std::endl;
					std::cout << bright << cyan << "    ==========================================" << reset << std::endl << std::endl;
				}
			}
			std::cout << std::endl << cyan << "  Verify Loan :" << reset << std::endl << std::endl;
			int objId = getIntInput("LoanId(-1:back)");
			if (objId == -1) return;
			Loan tmp;
			while (!Loan::exists(objId) || (tmp = Loan::getLoanStruct(objId)).fBankId != bank.id || tmp.status != 0)
			{
				std::cout << red << "    LoanId is invalid!" << reset << std::endl;
				objId = getIntInput("LoanId(-1:back)");
				if (objId == -1) return;
			}

			int verificationStatus = getIntInput("Accept(1:accept, 2:reject)");
			if (verificationStatus == -1) return;
			while (verificationStatus != 1 && verificationStatus != 2)
			{
				std::cout << red << "    invalid input!" << reset << std::endl;
				verificationStatus = getIntInput("Accept(1:accept, 2:reject)");
				if (verificationStatus == -1) return;
			}

			if (verificationStatus == 1) {
				tmp.status = 1;
				BankAccount reqAcc = BankAccount::getAccountStruct(tmp.fRequestAccount);
				reqAcc.balance += tmp.amount;
				BankAccount::addOrUpdateAccount(reqAcc);
			}
			else tmp.status = -1;
			
			tmp.lastTimePayed = time(0);
			Loan::addOrUpdateLoan(tmp);
			std::cout << std::endl << green << bright << "Done!" << reset << std::endl;
			_sleep(1200);
		}
	}

	void allAccounts(Bank& bank)
	{
		system("cls");
		std::cout << std::endl << cyan << "  All Accounts :" << reset << std::endl << std::endl;
		for (int i = 0; i < bank.accounts.size(); i++)
		{
			BankAccount account = BankAccount::getAccountStruct(bank.accounts[i]);
			std::cout << "    " << std::to_string(i + 1) << "." << std::endl;
			std::cout << bright << cyan << "    ==========================================" << reset << std::endl;
			std::cout << bright << green << "      AccountId: " << account.id << reset << std::endl;
			std::cout << bright << yellow << "      User: " << account.fUsername << reset << std::endl;
			std::cout << "      Account Balance: " << account.balance << std::endl;

			std::string accountType = "";
			switch (account.type)
			{
			case 1:
				accountType = yellow + "Short-Term" + reset;
				break;
			case 2:
				accountType = green + "Long-Term" + reset;
				break;
			case 3:
				accountType = blue + "Special" + reset;
				break;
			}
			std::cout << "      Account Type: " << accountType << std::endl;

			std::string accountStatus = "";
			switch (account.status)
			{
			case -2:
				accountStatus = red + "Blocked" + reset;
				break;
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

			std::cout << "      Requisition Date: " << getDateTime(account.createDate, true) << std::endl;
			std::cout << bright << cyan << "    ==========================================" << reset << std::endl << std::endl;
		}
		std::string tmp;
		std::getline(std::cin, tmp);
	}

	void allLoans(Bank& bank)
	{
		system("cls");
		std::cout << std::endl << cyan << "  All Loans :" << reset << std::endl << std::endl;
		for (int i = 0; i < bank.loans.size(); i++)
		{
			Loan loan = Loan::getLoanStruct(bank.loans[i]);
			BankAccount reqAcc = BankAccount::getAccountStruct(loan.fRequestAccount);
			std::cout << "    " << std::to_string(i + 1) << "." << std::endl;
			std::cout << bright << cyan << "    ==========================================" << reset << std::endl;
			std::cout << bright << green << "      LoanId: " << loan.id << reset << std::endl;
			std::cout << bright << yellow << "      User: " << reqAcc.fUsername << reset << std::endl;
			std::cout << bright << yellow << "      Amount: " << loan.amount << reset << std::endl;

			std::string loanStatus = "";
			switch (loan.status)
			{
			case -2:
				loanStatus = red + "Blocked" + reset;
				break;
			case -1:
				loanStatus = red + "Rejected" + reset;
				break;
			case 0:
				loanStatus = yellow + "Pending" + reset;
				break;
			case 1:
				loanStatus = green + "Accepted" + reset;
				break;
			case 2:
				loanStatus = blue + "Finished" + reset;
				break;
			}
			std::cout << "      Loan status: " << loanStatus << std::endl;

			std::cout << "      Payments Count: " << loan.countOfPayments << std::endl;
			std::cout << "      Payed count: " << loan.countOfPaid << std::endl;
			if (loan.countOfPaid)
				std::cout << "      Last payment date: " << getDateTime(loan.lastTimePayed) << std::endl;
			std::cout << "      Requisition Date: " << getDateTime(loan.requisitionDate, true) << std::endl;
			std::cout << bright << cyan << "    ==========================================" << reset << std::endl << std::endl;
		}
		std::string tmp;
		std::getline(std::cin, tmp);
	}
}