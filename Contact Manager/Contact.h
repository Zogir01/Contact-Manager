/**
 * \brief klasa Contact
 *
 * Klasa Contact jest reprezentacją kontaktu w aplikacji. Służy do przechowywania informacji o 
 * konkretnym kontakcie, takich jak identyfikator, numer telefonu, imię, nazwisko i adres e-mail.
 * Jest to najbardziej zagnieżdżona z klas. Aby poprawnie z niej korzystać, potrzebna jest implementacja
 * konteneru obiektów Contact w klasie ContactBook, która następnie jest mocno powiązana z klasą
 * ContactBookModel.
 * 
 * \version alpha 0.1
 */

#pragma once

#include <iostream>
#include <string>

class Contact
{
private:
	int id; /**< identyfikator kontaktu */
	int phone_number; /**< numer telefonu */
	std::string name; /**< imie */
	std::string last_name; /**< nazwisko */
	std::string email; /**< adres e-mail */

public:
	Contact();
	Contact(int id, int phone_number, std::string name,
		std::string last_name, std::string email);

	void checkData(int phone_number, std::string name, std::string last_name, std::string email);
	void editContact(int phone_number, std::string name, std::string last_name, std::string email);

	// gettery
	int getId();
	int getPhoneNumber();
	std::string getName();
	std::string getLastName();
	std::string getEmail();
	std::string getContactStr();

	// settery
	void setId(int id);
	void setPhoneNumber(int phone_number);
	void setName(std::string name);
	void setLastName(std::string last_name);
	void setEmail(std::string email);
};

