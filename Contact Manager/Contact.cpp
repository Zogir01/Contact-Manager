#include "Contact.h"

/**
 * @brief Konstruktor klasy Contact.
 * 
 * Inicjalizuje obiekt Contact domyślnymi wartościami.
 */
Contact::Contact()
{
	this->id = 0;
	this->name = "";
	this->last_name = "";
	this->phone_number = 0;
	this->email = "";
}

/**
 * @brief Konstruktor parametryczny klasy Contact.
 * 
 * Inicjalizuje obiekt Contact z podanymi wartościami.
 * @param id Identyfikator kontaktu.
 * @param phone_number Numer telefonu.
 * @param name Imię kontaktu.
 * @param last_name Nazwisko kontaktu.
 * @param email Adres e-mail kontaktu.
 */
Contact::Contact(int id, int phone_number, std::string name, std::string last_name, std::string email)
{
	this->checkData(phone_number, name, last_name, email );
	this->id = id;
	this->name = name;
	this->last_name = last_name;
	this->phone_number = phone_number;
	this->email = email;
}

/**
 * @brief Edytuje dane kontaktu.
 * 
 * @param phone_number Nowy numer telefonu.
 * @param name Nowe imię kontaktu.
 * @param last_name Nowe nazwisko kontaktu.
 * @param email Nowy adres e-mail kontaktu.
 */
void Contact::editContact(int phone_number, std::string name, std::string last_name, std::string email)
{
	this->checkData(phone_number, name, last_name, email );
	this->name = name;
	this->last_name = last_name;
	this->phone_number = phone_number;
	this->email = email;
}

/**
 * @brief Sprawdza poprawność danych kontaktu.
 * 
 * @param phone_number Numer telefonu.
 * @param name Imię kontaktu.
 * @param last_name Nazwisko kontaktu.
 * @param email Adres e-mail kontaktu.
 * @throws std::length_error Jeśli dane kontaktu nie spełniają warunków.
 */
void Contact::checkData(int phone_number, std::string name, std::string last_name, std::string email)
{
	if(std::to_string(phone_number).length() != 9)
	   throw std::length_error("Nieprawidlowa ilosc znakow w numerze telefonu");

	if(name.length()>12 || name.length() == 0)
		throw std::length_error("Nieprawidlowa dlugosc imienia");

	if(last_name.length()>16 || last_name.length() == 0)
		throw std::length_error("Nieprawidlowa dlugosc nazwiska");

	if(email.length()>30 || email.length() == 0)
		throw std::length_error("Nieprawidlowa dlugosc adresu email");
}

/**
 * @brief Ustawia identyfikator kontaktu.
 * 
 * @param id Identyfikator kontaktu.
 */
void Contact::setId(int id)
{
	// przypisywanie id odbywa klasie ContactBook
	this->id = id;
}

/**
 * @brief Ustawia numer telefonu kontaktu.
 * 
 * @param phone_number Numer telefonu.
 * @throws std::length_error Jeśli numer telefonu ma nieprawidłową długość.
 */
void Contact::setPhoneNumber(int phone_number)
{
	if(std::to_string(phone_number).length() == 9)
		this->phone_number = phone_number;
	else throw std::length_error("Nieprawidlowa dlugosc numer telefonu");
}

/**
 * @brief Ustawia imię kontaktu.
 * 
 * @param name Imię kontaktu.
 * @throws std::length_error Jeśli imię kontaktu ma nieprawidłową długość.
 */
void Contact::setName(std::string name)
{
	if(name.length()<=12 || name.length() > 0)
		this->name = name;
	else throw std::length_error("Nieprawidlowa dlugosc imienia");
}

/**
 * @brief Ustawia nazwisko kontaktu.
 * 
 * @param last_name Nazwisko kontaktu.
 * @throws std::length_error Jeśli nazwisko kontaktu ma nieprawidłową długość.
 */
void Contact::setLastName(std::string last_name)
{
	if(last_name.length()<=16 || last_name.length() > 0)
		this->last_name = last_name;
	else throw std::length_error("Nieprawidlowa dlugosc nazwiska");
}

/**
 * @brief Ustawia adres e-mail kontaktu.
 * 
 * @param email Adres e-mail kontaktu.
 * @throws std::length_error Jeśli adres e-mail kontaktu ma nieprawidłową długość.
 */
void Contact::setEmail(std::string email)
{
	if(email.length()<=30 || email.length() > 0)
		this->email = email;
	else throw std::length_error("Nieprawidlowa dlugosc adresu email");
}

/**
 * @brief Zwraca identyfikator kontaktu.
 * 
 * @return Identyfikator kontaktu.
 */
int Contact::getId()
{
	return this->id;
}

/**
 * @brief Zwraca numer telefonu kontaktu.
 * 
 * @return Numer telefonu kontaktu.
 */
int Contact::getPhoneNumber()
{
	return this->phone_number;
}

/**
 * @brief Zwraca imię kontaktu.
 * 
 * @return Imię kontaktu.
 */
std::string Contact::getName()
{
	return this->name;
}

/**
 * @brief Zwraca nazwisko kontaktu.
 * 
 * @return Nazwisko kontaktu.
 */
std::string Contact::getLastName()
{
	return this->last_name;
}

/**
 * @brief Zwraca adres e-mail kontaktu.
 * 
 * @return Adres e-mail kontaktu.
 */
std::string Contact::getEmail()
{
	return this->email;
}

/**
* @brief Zwraca dane kontaktu w postaci tekstowej.
* 
* @return Tekst zawierający id, imię, nazwisko, numer telefonu i adres e-mail kontaktu.
*/
std::string Contact::getContactStr()
{
	return std::to_string(this->id) + ",  " + this->name + ", " + this->last_name + ", " + std::to_string(this->phone_number) + ", " + this->email;
}