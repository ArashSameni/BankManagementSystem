#include "../../headers/UI/user_panel.h"

namespace userPanelNS
{
	void accountsList(User& user);
	void transitionsList(User& user);
	void loansList(User& user);
	void banksList();
	void transferMoney(User& user);
	void createAccount(User& user);
	void applyLoan(User& user);

	void payLoans(User& user);
	void getInterests(User& user);
	void blockUser(User& user, int bankId);

	bool gotLoanFromBank(User& user, int bankId);
}

void userPanel(User authenticatedUser)
{
	using namespace userPanelNS;
	initialUser(authenticatedUser);
	while (true)
	{
		system("cls");
		std::cout << std::endl << bright << yellow << "             Welcome " << authenticatedUser.name << reset << std::endl;
		std::cout << std::endl << cyan << "  User Panel :" << reset << std::endl << std::endl;
		std::cout << "    1.Accounts List" << std::endl;
		std::cout << "    2.Transitions List" << std::endl;
		std::cout << "    3.Loans List" << std::endl;
		std::cout << "    4.Banks List" << std::endl;
		std::cout << "    5.Transfer Money" << std::endl;
		std::cout << "    6.Create Bank Account" << std::endl;
		std::cout << "    7.Apply for a loan" << std::endl;
		std::cout << "    8.Edit Profile" << std::endl;
		std::cout << "    9.Exit" << std::endl;

		int input = getMenuInput(9);
		switch (input)
		{
		case 1:
			accountsList(authenticatedUser);
			break;
		case 2:
			transitionsList(authenticatedUser);
			break;
		case 3:
			loansList(authenticatedUser);
			break;
		case 4:
			banksList();
			break;
		case 5:
			transferMoney(authenticatedUser);
			break;
		case 6:
			createAccount(authenticatedUser);
			break;
		case 7:
			applyLoan(authenticatedUser);
			break;
		case 8:
			editProfileNS::editProfile(authenticatedUser);
			break;
		case -1:
			return;
		case 9:
			exit(0);
		}
	}
}

void initialUser(User& User)
{
	userPanelNS::payLoans(User);
	userPanelNS::getInterests(User);
}

namespace userPanelNS
{
	void accountsList(User& user)
	{
		system("cls");
		std::cout << std::endl << cyan << "  Accounts :" << reset << std::endl << std::endl;
		for (int i = 0; i < user.accounts.size(); i++)
		{
			BankAccount acc = BankAccount::getAccountStruct(user.accounts[i]);
			Bank bank = Bank::getBankStruct(acc.fBankId);
			std::cout << "    " << std::to_string(i + 1) << "." << std::endl;
			std::cout << bright << cyan << "    ==========================================" << reset << std::endl;
			std::cout << bright << green << "      AccountId: " << acc.id << reset << std::endl << std::endl;
			std::cout << bright << yellow << "      Account Balance: " << acc.balance << reset << std::endl << std::endl;

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
			std::cout << bright << cyan << "    ==========================================" << reset << std::endl << std::endl;
		}
		std::string tmp;
		std::getline(std::cin, tmp);
	}

	void transitionsList(User& user)
	{
		system("cls");
		std::vector<Transition> allTransitions = Transition::getAllTransitions();
		std::cout << std::endl << cyan << "  Transitions :" << reset << std::endl << std::endl;
		for (int i = 0; i < allTransitions.size(); i++)
		{
			std::vector<int>& v = user.accounts;
			Transition& tran = allTransitions[i];

			bool userIsSender = false;
			bool userIsReceiver = false;
			if (std::find(v.begin(), v.end(), tran.sender) != v.end())
				userIsSender = true;
			else if (std::find(v.begin(), v.end(), tran.receiver) != v.end())
				userIsReceiver = true;

			if (userIsSender || userIsReceiver)
			{
				std::cout << "    " << std::to_string(i + 1) << "." << std::endl;
				std::cout << bright << cyan << "    ==========================================" << reset << std::endl;
				std::cout << bright << green << "      TransitionId: " << tran.id << reset << std::endl;
				std::cout << "      Sender: " << tran.sender << (userIsSender ? green + " (Your account)" + reset : "") << std::endl;
				std::cout << "      Receiver: " << tran.receiver << (userIsReceiver ? green + " (Your account)" + reset : "") << std::endl;
				std::cout << "      Amount: " << tran.amount << std::endl;
				std::cout << "      Transition Date: " << getDateTime(tran.transitionDate, true) << std::endl;
				std::cout << bright << cyan << "    ==========================================" << reset << std::endl << std::endl;
			}
		}
		std::string tmp;
		std::getline(std::cin, tmp);
	}

	void loansList(User& user)
	{
		system("cls");
		std::cout << std::endl << cyan << "  Loans :" << reset << std::endl << std::endl;
		for (int i = 0; i < user.loans.size(); i++)
		{
			Loan loan = Loan::getLoanStruct(user.loans[i]);
			Bank bank = Bank::getBankStruct(loan.fBankId);
			BankAccount payAcc = BankAccount::getAccountStruct(loan.fPaymentAccount);

			std::cout << "    " << std::to_string(i + 1) << "." << std::endl;
			std::cout << bright << cyan << "    ==========================================" << reset << std::endl;
			std::cout << bright << green << "      LoanId: " << loan.id << reset << std::endl;
			std::cout << bright << yellow << "      Amount: " << loan.amount << reset << std::endl;

			std::cout << "      Request account: " << loan.fRequestAccount << std::endl;
			std::cout << "      Payment account: " << payAcc.id << "      Balance: " << payAcc.balance << std::endl;

			std::cout << "      BankId: " << bank.id << "      Bank name: " << bank.name << std::endl;

			std::string loanStatus = "";
			switch (loan.status)
			{
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

			std::cout << "      Payments count: " << loan.countOfPayments << std::endl;
			std::cout << "      Payed count: " << loan.countOfPaid << std::endl;
			if (loan.countOfPaid)
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

	void transferMoney(User& user)
	{
		std::cout << std::endl << cyan << " Transfer Money" << reset << std::endl << std::endl;

		std::vector<int>& v = user.accounts;

		int senderAccId = getIntInput("Your Account Id");
		if (senderAccId == -1) return;
		while (std::find(v.begin(), v.end(), senderAccId) == v.end())
		{
			std::cout << red << "    it's not your account!" << reset << std::endl;
			senderAccId = getIntInput("Your Account Id");
			if (senderAccId == -1) return;
		}

		BankAccount sender = BankAccount::getAccountStruct(senderAccId);
		if (sender.status == 1)
		{
			int receiverAccId = getIntInput("Receiver Account Id");
			if (receiverAccId == -1) return;
			while (!BankAccount::exists(receiverAccId))
			{
				std::cout << red << "    Account doesn't exist!" << reset << std::endl;
				receiverAccId = getIntInput("Receiver Account Id");
				if (receiverAccId == -1) return;
			}
			if (senderAccId != receiverAccId)
			{
				BankAccount receiver = BankAccount::getAccountStruct(receiverAccId);
				if (receiver.status == 1)
				{
					int amount = getIntInput("Amount");
					if (amount == -1) return;
					while (amount <= 0)
					{
						std::cout << red << "    Amount isn't valid!" << reset << std::endl;
						amount = getIntInput("Amount");
						if (amount == -1) return;
					}
					if (sender.balance >= amount)
					{
						newTransition(senderAccId, receiverAccId, amount);
						std::cout << std::endl << green << bright << "Transaction Successful!" << reset << std::endl;
					}
					else
						std::cout << red << "    Account doesn't have enough money!" << reset << std::endl;
				}
				else
					std::cout << red << "    Receiver account is disabled!" << reset << std::endl;
			}
			else
				std::cout << std::endl << red << "        ◉_◉" << reset << std::endl;
		}
		else
			std::cout << red << "    Your account has not been accepted yet!" << reset << std::endl;

		_sleep(1200);
		system("cls");
	}

	void createAccount(User& user)
	{
		std::cout << std::endl << cyan << " Create Bank Account" << reset << std::endl << std::endl;

		if (!user.isBlocked)
		{
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
			while (balance < 0)
			{
				std::cout << red << "    invalid Balance!" << reset << std::endl;
				balance = getIntInput("Balance");
				if (balance == -1) return;
			}

			Bank bank = Bank::getBankStruct(bankId);
			BankAccount acc = newBankAccount(user.username, bankId, type, balance);
			bank.accounts.push_back(acc.id);
			user.accounts.push_back(acc.id);
			User::addOrUpdateUser(user);
			Bank::addOrUpdateBank(bank);
			std::cout << std::endl << green << bright << "Requisition has been sent to bank!" << reset << std::endl;
		}
		else
			std::cout << red << "    You are blocked!" << reset << std::endl;

		_sleep(1200);
	}

	void applyLoan(User& user)
	{
		std::cout << std::endl << cyan << " Apply For Loan" << reset << std::endl << std::endl;

		if (!user.isBlocked)
		{
			int amount = getIntInput("Amount");
			if (amount == -1) return;
			while (amount < 0 || amount > 3000000)
			{
				if (amount < 0)
					std::cout << red << "    invalid Amount!" << reset << std::endl;
				else if (amount > 3000000)
					std::cout << red << "    its too much :)!" << reset << std::endl;

				amount = getIntInput("Amount");
				if (amount == -1) return;
			}

			std::vector<int>& v = user.accounts;
			int receiverId = getIntInput("Loan Receiver");
			if (receiverId == -1) return;
			while (std::find(v.begin(), v.end(), receiverId) == v.end())
			{
				std::cout << red << "    it's not your account!" << reset << std::endl;
				receiverId = getIntInput("Loan Receiver");
				if (receiverId == -1) return;
			}
			
			BankAccount receiver = BankAccount::getAccountStruct(receiverId);
			if (!gotLoanFromBank(user, receiver.fBankId))
			{
				if (receiver.status == 1)
				{
					int payerId = getIntInput("Loan Payer", false);
					if (payerId == -1) return;
					else if (payerId != 0)
						while (std::find(v.begin(), v.end(), payerId) == v.end())
						{
							std::cout << red << "    it's not your account!" << reset << std::endl;
							payerId = getIntInput("Loan Payer");
							if (payerId == -1) return;
						}
					else payerId = receiverId;

					BankAccount payer = BankAccount::getAccountStruct(payerId);
					if (payer.status == 1)
					{
						int countOfPays = getIntInput("Payments Count");
						if (countOfPays == -1) return;
						while (countOfPays < 5 || countOfPays > 48)
						{
							std::cout << red << "    You can choose between (5-48) months!" << reset << std::endl;
							countOfPays = getIntInput("Payments Count");
							if (countOfPays == -1) return;
						}
						int bankId = BankAccount::getAccountStruct(receiverId).fBankId;
						Bank bank = Bank::getBankStruct(bankId);
						Loan loan = newLoan(receiverId, bankId, amount, countOfPays, payerId);
						bank.loans.push_back(loan.id);
						user.loans.push_back(loan.id);
						User::addOrUpdateUser(user);
						Bank::addOrUpdateBank(bank);

						std::cout << std::endl << green << bright << "Requisition has been sent to bank!" << reset << std::endl;
					}
					else
						std::cout << red << "    This account has not been accepted yet!" << reset << std::endl;
				}
				else
					std::cout << red << "    This account has not been accepted yet!" << reset << std::endl;
			}
			else
				std::cout << red << "    You've gotten loan from this bank!" << reset << std::endl;
		}
		else
			std::cout << red << "    You are blocked!" << reset << std::endl;

		_sleep(1200);
	}

	void payLoans(User& user)
	{
		for (int i = 0; i < user.loans.size(); i++)
		{
			Loan loan = Loan::getLoanStruct(user.loans[i]);
			if (loan.status == 1)
			{
				const int secondsPerMonth = 86400 * 30;
				const int monthsPassed = (time(0) - loan.lastTimePayed) / secondsPerMonth;
				if (monthsPassed >= 1)
				{
					const int paymentAmount = loan.amount / loan.countOfPayments;
					BankAccount acc = BankAccount::getAccountStruct(loan.fPaymentAccount);
					if (loan.countOfPayments - loan.countOfPaid >= monthsPassed)
					{
						if (acc.balance >= paymentAmount * monthsPassed)
						{
							acc.balance -= paymentAmount * monthsPassed;
							loan.countOfPaid += monthsPassed;
							BankAccount::addOrUpdateAccount(acc);
						}
						else
						{
							blockUser(user, loan.fBankId);
							loan.status = -2;
						}
					}
					else
					{
						const int countOfPays = loan.countOfPayments - loan.countOfPaid;
						if (acc.balance >= paymentAmount * countOfPays)
						{
							acc.balance -= paymentAmount * countOfPays;
							loan.countOfPaid += countOfPays;
							BankAccount::addOrUpdateAccount(acc);
						}
						else 
						{
							blockUser(user, loan.fBankId);
							loan.status = -2;
						}
					}
					loan.lastTimePayed = time(0);
					Loan::addOrUpdateLoan(loan);
					if (loan.countOfPaid == loan.countOfPayments)
						loan.status = 2;
				}
			}
		}
	}

	void getInterests(User& user)
	{
		for (int i = 0; i < user.accounts.size(); i++)
		{
			BankAccount acc = BankAccount::getAccountStruct(user.accounts[i]);
			if (acc.status == 1)
			{
				const int secondsPerDay = 86400;
				const int daysPassed = (time(0) - acc.lastInterestDate) / secondsPerDay;
				if (daysPassed >= 1)
				{
					for (int i = 0; i < daysPassed; i++)
						acc.balance *= acc.interestRate;
					acc.lastInterestDate = time(0);
					BankAccount::addOrUpdateAccount(acc);
				}
			}
		}
	}

	void blockUser(User& user, int bankId)
	{
		user.isBlocked = true;
		User::addOrUpdateUser(user);
		for (int i = 0; i < user.accounts.size(); i++)
		{
			BankAccount acc = BankAccount::getAccountStruct(user.accounts[i]);
			if (acc.fBankId == bankId)
			{
				acc.status = -2;
				BankAccount::addOrUpdateAccount(acc);
			}
		}
	}
	
	bool gotLoanFromBank(User& user, int bankId)
	{
		for (int i = 0; i < user.loans.size(); i++)
		{
			Loan loan = Loan::getLoanStruct(user.loans[i]);
			if (loan.fBankId == bankId && loan.status == 1)
				return true;
		}
		
		return false;
	}
}