#include <iostream>
#include "../../headers/UI/main_menu.h"

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
	//_sleep(2500);
	system("cls");
}

void mainMenu()
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



void loginMenu()
{
	std::cout << std::endl << cyan << " Login Menu" << reset << std::endl << std::endl;
}

void signUpMenu()
{
	system("cls");
	std::cout << std::endl << cyan << " SignUp Menu" << reset << std::endl << std::endl;
	std::string name = getStringInput("Full Name", true, true);
	if(name == "-1") mainMenu();
	
	std::string username = getStringInput("Username");
	if (username == "-1") mainMenu();
	
	std::string password = getStringInput("Password");
	if (password == "-1") mainMenu();
	
	std::string PhoneNO = getStringInput("Phone Number");
	if (PhoneNO == "-1") mainMenu();
	while(!is_digits(PhoneNO) || PhoneNO.size() != 11)
	{
		std::cout << red << "    invalid Phone Number!" << reset << std::endl;
		PhoneNO = getStringInput("Phone Number");
	}
	
	std::string city = getStringInput("City");
	if (city == "-1") mainMenu();

	Address tempAddress = newAddress(city);
	User tempUser = newUser(username, password, name, 1, PhoneNO, tempAddress.id);
	
	std::cout << std::endl << green << bright << "Your account has been successfully created!" << reset << std::endl;
	_sleep(1000);
	loginMenu();
}

void forgotPasswordMenu()
{

}