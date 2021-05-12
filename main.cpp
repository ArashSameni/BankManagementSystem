#include <iostream>
#include <QCoreApplication>
#include <QDir>
#include "headers/structs/User.h"
#include "headers/structs/Bank.h"
#include "headers/structs/BankAccount.h"
#include "headers/structs/Address.h"
#include "headers/structs/Loan.h"
#include "headers/structs/Transition.h"
#include "headers/file.h"
#include "headers/UI/main_menu.h"

void createFile(QString path);
void InitializeProject();

int main(int argc, char* argv[])
{
	InitializeProject();
	return 0;
}

void InitializeProject()
{
	QDir dir(".");
	dir.mkdir("data");

	// Add admin user
	if (!fileExists(User::fileName))
		User admin = newUser("admin", "admin", "arash", 3);

	createFileIfNotExist(Bank::fileName);
	createFileIfNotExist(Address::fileName);
	createFileIfNotExist(Loan::fileName);
	createFileIfNotExist(Transition::fileName);
	createFileIfNotExist(BankAccount::fileName);

	User::usersCount = countOfObjects(User::fileName);
	Bank::banksCount = countOfObjects(Bank::fileName);
	Address::addressesCount = countOfObjects(Address::fileName);
	Loan::loansCount = countOfObjects(Loan::fileName);
	Transition::transitionsCount = countOfObjects(Transition::fileName);
	BankAccount::accountsCount = countOfObjects(BankAccount::fileName);
}