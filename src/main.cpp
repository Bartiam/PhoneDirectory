#include <iostream>
#include <string>
#include <sstream>
#include <map>

bool is_correct_phone_number(const std::string& info)
{
	int countDash = 0;

	for (int i = 0; i < info.length(); ++i)
	{
		if ((info[i] < '0' || info[i] > '9') && info[i] != '-')
			return false;
		if (info[i] == '-') ++countDash;
	}

	if (countDash > 2 || countDash < 2) return false;
	if (info.length() > 8 || info.length() < 8) return false;

	return true;
}

bool is_correct_surname(const std::string& info)
{
	for (int i = 1; i < info.length(); ++i)
	{
		if (info[0] < 'A' || info[0] > 'Z' || 
			info[i] < 'a' || info[i] > 'z')
		{
			return false;
		}
	}
	return true;
}

std::string is_correct_input_data(const std::string& info)
{
	std::stringstream information(info);
	std::string surname, phoneNumber;

	information >> phoneNumber >> surname;

	if (surname.empty())
	{
		if (is_correct_phone_number(phoneNumber)) return "phonenumber";
		if (is_correct_surname(phoneNumber)) return "surname";
	}
	else
	{
		if (is_correct_phone_number(phoneNumber))
			if (is_correct_surname(surname)) return "both";
	}
	return "Error";
}

void add(std::map<std::string, std::string>& phoneDirectory, std::string& info)
{
	std::stringstream separationInfo(info);
	std::string phoneNumber, surname;

	separationInfo >> phoneNumber >> surname;

	phoneDirectory.emplace(phoneNumber, surname);
}

void find_owner_phone_number(std::map<std::string, std::string>& phoneDirectory, std::string& info)
{
	std::map<std::string, std::string>::iterator it = phoneDirectory.find(info);
	if (it == phoneDirectory.end())
		std::cerr << "There is no such contact number in the list. " << std::endl;
	else
		std::cout << "Surname this subscriber: " << it->second << std::endl;
}

void find_phone_number_by_surname(std::map<std::string, std::string>& phoneDirectory, std::string& info)
{
	for (std::map<std::string, std::string>::iterator it = phoneDirectory.begin(); 
		it != phoneDirectory.end(); ++it)
	{
		if (it->second == info) std::cout << it->first << " ";
	}
	std::cout << std::endl;
}

int main()
{
	std::string info;
	std::map<std::string, std::string> phoneDirectory;

	while (true)
	{
		std::cout << "Enter the command(X for output): ";
		std::getline(std::cin, info);

		if (info == "X" || info == "x")
			return 0;

		std::string check = is_correct_input_data(info);

		if (check == "Error")
			std::cerr << "Error! Incorrect input data. Try again. " << std::endl;
		else if (check == "both")
			add(phoneDirectory, info);
		else if (check == "phonenumber")
			find_owner_phone_number(phoneDirectory, info);
		else if (check == "surname")
			find_phone_number_by_surname(phoneDirectory, info);
	}
}
