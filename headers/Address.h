#pragma once
#include <iostream>
#include <QJsonObject>
#include "file.h"
#include "utilities.h"

struct Address
{
	int id;
	static int addressesCount;

	std::string country = "iran";
	std::string city = "";
	std::string street = "";
	int postalCode = 0;
	int plaqueNO = 0;

	static QString fileName;
	static QJsonObject getAddress(int id);
	static void addAddress(Address address);
	static void removeAddress(int id);
	static Address getAddressStruct(QJsonObject addressObj);
	static Address getAddressStruct(int id);
};

static Address newAddress(std::string city = "",
	std::string street = "",
	std::string country = "iran",
	int postalCode = 0,
	int plaqueNO = 0)
{
	Address tempAddress;
	tempAddress.id = ++Address::addressesCount;
	tempAddress.country = country;
	tempAddress.city = city;
	tempAddress.street = street;
	tempAddress.postalCode = postalCode;
	tempAddress.plaqueNO = plaqueNO;

	Address::addAddress(tempAddress);

	return tempAddress;
}