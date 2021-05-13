#include "../../headers/UI/edit_profile.h"

namespace editProfileNS
{
	void changeName(User& user);
	void changePhoneNO(User& user);
	void changeAddress(User& user);
	void changePassword(User& user);

	void editProfile(User& user)
	{
		while (true)
		{
			Address add;
			system("cls");
			std::cout << std::endl << cyan << "  Edit Profile :" << reset << std::endl << std::endl;
			std::cout << "    1.Change Name (" << user.name << ")" << std::endl;
			std::cout << "    2.Phone Number (" << user.phoneNO << ")" << std::endl;
			std::cout << "    3.Address" << std::endl;
			std::cout << "    4.Change Password" << std::endl;
			std::cout << "    5.Go Back" << std::endl;

			int input = getMenuInput(5);
			switch (input)
			{
			case 1:
				changeName(user);
				break;
			case 2:
				changePhoneNO(user);
				break;
			case 3:
				changeAddress(user);
				break;
			case 4:
				changePassword(user);
				break;
			case 5:case -1:
				return;
			}
		}
	}

	void changeName(User& user)
	{
		std::cout << std::endl << cyan << " Change Name" << reset << std::endl << std::endl;

		std::string newName = getStringInput("Name", true, true);
		if (newName == "-1") return;

		user.name = newName;
		User::addOrUpdateUser(user);

		std::cout << std::endl << green << bright << "Profile updated!" << reset << std::endl;
		_sleep(1200);
		system("cls");
	}

	void changePhoneNO(User& user)
	{
		std::cout << std::endl << cyan << " Change Phone Number" << reset << std::endl << std::endl;

		std::string PhoneNO = getStringInput("Phone Number");
		if (PhoneNO == "-1") return;
		while (!is_digits(PhoneNO) || PhoneNO.size() != 11)
		{
			std::cout << red << "    invalid Phone Number!" << reset << std::endl;
			PhoneNO = getStringInput("Phone Number");
			if (PhoneNO == "-1") return;
		}

		user.phoneNO = PhoneNO;
		User::addOrUpdateUser(user);

		std::cout << std::endl << green << bright << "Profile updated!" << reset << std::endl;
		_sleep(1200);
		system("cls");
	}

	void changeAddress(User& user)
	{
		std::cout << std::endl << cyan << " Change Address" << reset << std::endl << std::endl;
		if (user.addressId)
		{
			Address currentAddress = Address::getAddressStruct(user.addressId);
			std::cout << green << "Current Address: " <<
				"(Country: " << currentAddress.country <<
				", City: " << currentAddress.city <<
				", Street: " << currentAddress.street <<
				", PlaqueNO: " << currentAddress.plaqueNO <<
				", Postal Code: " << currentAddress.postalCode << ")" << std::endl << std::endl;
		}

		std::string country = getStringInput("Country", false); if (country == "-1") return;

		std::string city = getStringInput("City", false); if (city == "-1") return;

		std::string street = getStringInput("Street", false); if (street == "-1") return;

		int plaqueNO = getIntInput("PlqueNO", false); if (plaqueNO == -1) return;

		int postalCode = getIntInput("Postal Code", false); if (postalCode == -1) return;

		if (user.addressId)
			Address::removeAddress(user.addressId);

		Address newAdd = newAddress(city, street, country, postalCode, plaqueNO);
		user.addressId = newAdd.id;
		User::addOrUpdateUser(user);

		std::cout << std::endl << green << bright << "Profile updated!" << reset << std::endl;
		_sleep(1200);
		system("cls");
	}

	void changePassword(User& user)
	{
		std::cout << std::endl << cyan << " Change Password" << reset << std::endl << std::endl;
		std::string currPassword = getStringInput("Current Password");
		if (currPassword == "-1") return;
		if (user.password == currPassword)
		{
			std::string newPassword = getStringInput("New Password");
			if (newPassword == "-1") return;
			user.password = newPassword;
			User::addOrUpdateUser(user);
			std::cout << std::endl << green << bright << "Password updated!" << reset << std::endl;
		}
		else
			std::cout << red << "    Password incorrect!" << reset << std::endl;
		_sleep(1200);
		system("cls");
	}
}