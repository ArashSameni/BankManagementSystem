#pragma once
#include <iostream>

struct Address
{
    int id;
    static int addressesCount;

    std::string country = "iran";
    std::string city = "";
    std::string street = "";
    int postalCode = 0;
    int plaqueNO = 0;
};

static Address newAddress(std::string city = "",
                          std::string street = "",
                          std::string country = "iran")
{
    Address tempAddress;
    tempAddress.id = ++Address::addressesCount;
    tempAddress.country = country;
    tempAddress.city = city;
    tempAddress.street = street;

    return tempAddress;
}