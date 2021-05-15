#include <iostream>
#include "../../headers/UI/main_menu.h"

void loginMenu();
void signUpMenu();
void forgotPasswordMenu();

void showLogo()
{
	std::cout << std::endl << bright << red;
	std::cout << "   BBBBBBBBBBBBBBBBB        MMMMMMMM               MMMMMMMM        SSSSSSSSSSSSSSS " << std::endl;
	std::cout << "   B::::::::::::::::B       M:::::::M             M:::::::M      SS:::::::::::::::S" << std::endl;
	std::cout << "   B::::::BBBBBB:::::B      M::::::::M           M::::::::M     S:::::SSSSSS::::::S" << std::endl;
	std::cout << "   BB:::::B     B:::::B     M:::::::::M         M:::::::::M     S:::::S     SSSSSSS" << std::endl;
	std::cout << "     B::::B     B:::::B     M::::::::::M       M::::::::::M     S:::::S            " << std::endl;
	std::cout << "     B::::B     B:::::B     M:::::::::::M     M:::::::::::M     S:::::S            " << std::endl;
	std::cout << "     B::::BBBBBB:::::B      M:::::::M::::M   M::::M:::::::M      S::::SSSS         " << std::endl;
	std::cout << "     B:::::::::::::BB       M::::::M M::::M M::::M M::::::M       SS::::::SSSSS    " << std::endl;
	std::cout << "     B::::BBBBBB:::::B      M::::::M  M::::M::::M  M::::::M         SSS::::::::SS  " << std::endl;
	std::cout << "     B::::B     B:::::B     M::::::M   M:::::::M   M::::::M            SSSSSS::::S " << std::endl;
	std::cout << "     B::::B     B:::::B     M::::::M    M:::::M    M::::::M                 S:::::S" << std::endl;
	std::cout << "     B::::B     B:::::B     M::::::M     MMMMM     M::::::M                 S:::::S" << std::endl;
	std::cout << "   BB:::::BBBBBB::::::B     M::::::M               M::::::M     SSSSSSS     S:::::S" << std::endl;
	std::cout << "   B:::::::::::::::::B      M::::::M               M::::::M     S::::::SSSSSS:::::S" << std::endl;
	std::cout << "   B::::::::::::::::B       M::::::M               M::::::M     S:::::::::::::::SS " << std::endl;
	std::cout << "   BBBBBBBBBBBBBBBBB        MMMMMMMM               MMMMMMMM      SSSSSSSSSSSSSSS" << std::endl << std::endl;
	std::cout << reset << bright << green;
	std::cout << "   A simple :) Bank Management System" << std::endl << std::endl;
	std::cout << reset;
	std::cout << "   Github: " << cyan << "https://github.com/ArashSameni/BankManagementSystem" << reset << std::endl;
	_sleep(2500);
	system("cls");
}

void mainMenu()
{
	while(true)
	{
		system("cls");
		std::cout << std::endl << cyan << "  Main Menu :" << reset << std::endl << std::endl;
		std::cout << "    1.Login" << std::endl;
		std::cout << "    2.Sign Up" << std::endl;
		std::cout << "    3.Forgot Password" << std::endl;
		std::cout << "    4.Exit" << std::endl;

		int input = getMenuInput(4);
		switch (input)
		{
		case 1:
			loginMenu();
			break;
		case 2:
			signUpMenu();
			break;
		case 3:
			forgotPasswordMenu();
			break;
		default:          //-1 or 4
			exit(0);
		}
	}
}



void loginMenu()
{
	while (true)
	{
		system("cls");
		std::cout << std::endl << cyan << " Login Menu" << reset << std::endl << std::endl;

		std::string username = getStringInput("Username");
		if (username == "-1") return;

		std::string password = getStringInput("Password");
		if (password == "-1") return;

		if (User::authenticate(username, password))
		{
			User authenticatedUser = User::getUserStruct(username);
			switch (authenticatedUser.type)
			{
			case 1:
				userPanel(authenticatedUser);
				break;
			case 2:
				managerPanel(authenticatedUser);
				break;
			case 3:
				adminPanel(authenticatedUser);
				break;
			}
		}
		else
		{
			std::cout << red << "    Username or password is incorrect!" << reset << std::endl;
			_sleep(1200);
		}
	}
}

void signUpMenu()
{
	system("cls");
	std::cout << std::endl << cyan << " SignUp Menu" << reset << std::endl << std::endl;
	std::string name = getStringInput("Full Name", true, true);
	if(name == "-1") return;
	
	std::string username = getStringInput("Username");
	if (username == "-1") return;
	while(User::exists(username))
	{
		std::cout << red << "    Username already exists!" << reset << std::endl;
		username = getStringInput("Username");
		if (username == "-1") return;
	}
	
	std::string password = getStringInput("Password");
	if (password == "-1") return;
	
	std::string PhoneNO = getStringInput("Phone Number");
	if (PhoneNO == "-1") return;
	while(!is_digits(PhoneNO) || PhoneNO.size() != 11)
	{
		std::cout << red << "    invalid Phone Number!" << reset << std::endl;
		PhoneNO = getStringInput("Phone Number");
		if (PhoneNO == "-1") return;
	}
	
	std::string city = getStringInput("City", true, true);
	if (city == "-1") return;

	Address tempAddress = newAddress(city);
	newUser(username, password, name, 1, PhoneNO, tempAddress.id);
	
	std::cout << std::endl << green << bright << "Your account has been successfully created!" << reset << std::endl;
	_sleep(1200);
}

void forgotPasswordMenu()
{
	system("cls");
	std::cout << std::endl << cyan << " Forgot Password Menu" << reset << std::endl << std::endl;
	
	std::string username = getStringInput("Username");
	if (username == "-1") return;
	while (!User::exists(username))
	{
		std::cout << red << "    Username doesn't exist!" << reset << std::endl;
		username = getStringInput("Username");
		if (username == "-1") return;
	}
	User selectedUser = User::getUserStruct(username);
	
	std::string PhoneNO = getStringInput("Phone Number");
	if (PhoneNO == "-1") return;
	while (!is_digits(PhoneNO) || PhoneNO.size() != 11)
	{
		std::cout << red << "    invalid Phone Number!" << reset << std::endl;
		PhoneNO = getStringInput("Phone Number");
	}
	
	if (PhoneNO == selectedUser.phoneNO)
	{
		std::string password = getStringInput("New Password");
		if (password == "-1") return;
		selectedUser.password = password;
		User::addOrUpdateUser(selectedUser);
		std::cout << std::endl << green << bright << "Password successfully changed!" << reset << std::endl;
	}
	else
		std::cout << red << "    Phone Numbers doesn't match!" << reset << std::endl;

	_sleep(1200);
}