/**
 * \brief klasa ContactBook
 *
 * Klasa ContactBook reprezentuje książkę kontaktów, która przechowuje kolekcję kontaktów - obiektow
 * klasy Contact. Służy do zarządzania kontaktami - dodawania, usuwania, sortowania i wyszukiwania.
 * Aby poprawnie z niej korzystać, potrzebna jest implementacja konteneru obiektów ContactBook 
 * w klasie ContactBookModel.
 * 
 * \version alpha 0.1
 */

#pragma once

#include "Contact.h"

#include <iostream>
#include <vector>
#include <string>

class ContactBook
{
private:
	std::string name; /**< nazwa książki */
	std::string desc; /**< opis książki */
	std::vector<Contact> contacts; /**< kontener kontaktów - obiektów klasy Contact */
	std::string sort_type; /**< typ sortowania */

public:
	ContactBook();
	ContactBook(std::string name, std::string desc);
	~ContactBook();

	void checkData(std::string name, std::string desc);

	void editBook(std::string name, std::string desc);

	void addContact(int phone_number, std::string name, std::string last_name, std::string email);
	void removeContact(int id);
	void sortContacts();
	std::vector <std::pair<int, std::string>> searchContacts(std::string input, std::string formula);
	
	// gettery
	std::vector <std::string> getContactsVstr();
	std::vector <std::pair<int, std::string>> getContactPairs();
	std::string getName();
	std::string getDesc();
	Contact* getContact(int id);
	std::vector<Contact> getContacts();
	int getNumContacts();

	// settery
	void setName(std::string name);
	void setDesc(std::string desc);
};
