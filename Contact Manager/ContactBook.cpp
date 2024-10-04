#include "ContactBook.h"

/**
 * @brief Konstruktor klasy ContactBook.
 * 
 * Inicjalizuje obiekt ContactBook z domyślnymi wartościami.
 */
ContactBook::ContactBook()
{
	this->name = "";
	this->desc = "";
	this->sort_type = "";
	//this->contacts = {};
}

/**
 * @brief Konstruktor klasy ContactBook. 
 * 
 * Inicjalizuje obiekt ContactBook z podanymi wartościami.
 * @param name Nazwa książki kontaktów.
 * @param desc Opis książki kontaktów.
 */
ContactBook::ContactBook(std::string name, std::string desc)
{
	this->checkData(name, desc);
	this->name = name;
	this->desc = desc;
	this->sort_type = "";
	contacts = {};
}

/**
 * @brief Edytuje dane książki kontaktów. 
 * 
 * Wykorzystuje metodę @link checkData() w celu sprawdzenia poprawności
 * parametrów metody.
 * @param name Nowa nazwa książki kontaktów.
 * @param desc Nowy opis książki kontaktów.
 */
void ContactBook::editBook(std::string name, std::string desc)
{
	this->checkData(name, desc);
	this->name = name;
	this->desc= desc;
	this->sort_type = "";
}

/**
 * @brief Sprawdza poprawność danych książki kontaktów.
 * 
 * @param name Nazwa książki kontaktowej.
 * @param desc Opis książki kontaktowej.
 * @throws std::length_error Jeśli dane książki kontaktów są nieprawidłowe.
 */
void ContactBook::checkData(std::string name, std::string desc)
{
	if (name.length() > 12 || name.length() == 0)
		throw std::length_error("Nieprawidlowa dlugosc imienia");

	if (desc.length() > 50 || desc.length() == 0)
		throw std::length_error("Nieprawidlowa dlugosc nazwiska");
}

/**
 * @brief Destruktor klasy ContactBook.
 */
ContactBook::~ContactBook()
{

}

/**
 * @brief Dodaje kontakt do książki kontaktów. 
 * 
 * Przed dodaniem kontaktu do książki, generuje unikatowe id na bazie aktualnych
 * kontaktów. Przeszukuję id kontaktów i wybiera najmniejsze niewystępujące id.
 * @param phone_number Numer telefonu kontaktu.
 * @param name Imię kontaktu.
 * @param last_name Nazwisko kontaktu.
 * @param email Adres e-mail kontaktu.
 */
void ContactBook::addContact(int phone_number, std::string name, std::string last_name, std::string email)
{
	int id = 0; // ustalanie unikatowego id
	int len = this->contacts.size();
	int resultVal = -1;
	bool isIn = false;

	// najpierw rosnąco iteruje
	for (int i = 1; i <= len + 1; i++)
	{
		isIn = false; // resetuje zmienną przed każdą iteracją
		for (int j = 0; j < len; j++)
		{
			// jeśli znajduje się dany indeks i
			if (this->contacts[j].getId() == i)
			{
				isIn = true;
				break;
			}
		}
		// jeśli nie znajdzie id
		if (!isIn)
		{
			resultVal = i;
			break;
		}
	}

	Contact cnt(resultVal, phone_number, name, last_name, email);
	this->contacts.push_back(cnt);
}

/**
 * @brief Usuwa kontakt z książki kontaktowej. 
 * 
 * Najpierw przeszukuje kontakty w celu sprawdzenia czy kontakt o podanym
 * identyfikatorze istnieje.
 * @param id Identyfikator kontaktu.
 * @throws std::invalid_argument Jeśli nie można znaleźć kontaktu o podanym identyfikatorze.
 */
void ContactBook::removeContact(int id)
{
	bool found = false;

	for (int i = 0; i < this->contacts.size(); i++) {
		if (id == this->contacts[i].getId()) {
			this->contacts.erase(this->contacts.begin() + i);
			found = true;
		}	
	}

	if (!found) {
		throw std::invalid_argument("Usuwanie nie powiodlo sie, nie ma takiego kontaktu w bazie!");
	}
}

/**
 * @brief Sortuje kontakty w książce kontaktowej.
 * 
 * @attention Metoda niedokończona.
 */
void ContactBook::sortContacts()
{

}

/**
 * @brief Wyszukuje kontakty w książce kontaktów na podstawie podanego wejścia i formuły.
 * 
 * Sprawdza poprawność formuły. Do wyboru są trzy formuły: "byName", "byLastName", "byPhoneNumber".
 * Przeszukuję kontener wszystkich kontaktów i w zależności od wybranej formuły ustawia zmienną to_find na zmienną
 * do porównania. Następnie porównuje frazę do wyszukania z ustawioną zmienną.
 * Jeśli frazy nie uda się odnaleźć, zwróci pusty kontener.
 * @param input Fraza do wyszukania.
 * @param formula Formuła wyszukiwania: "byName" (według imienia), "byLastName" (według nazwiska) lub "byPhoneNumber" (według numeru telefonu).
 * @return Wektor par zawierających identyfikator kontaktu i tekstową reprezentację kontaktu.
 * @throws std::invalid_argument Jeśli podano nieprawidłową formułę wyszukiwania.
 * @attention W metodzie znajduje się zmienna exactMatch, 
 */
std::vector<std::pair<int, std::string>> ContactBook::searchContacts(std::string input, std::string formula)
{
	bool exactMatch = false;
	if (formula != "byName" && formula != "byLastName" && formula != "byPhoneNumber") {
		throw std::invalid_argument("Podano zla formule wyszukania!");
	}

	std::vector <std::pair<int, std::string>> contactsFound;
	std::string to_find;

	for (auto& contact : this->contacts)
	{
		if (formula == "byName")
			to_find = contact.getName();

		else if (formula == "byLastName")
			to_find = contact.getLastName();

		else if (formula == "byPhoneNumber")
			to_find = contact.getPhoneNumber();

		if (to_find.find(input) != std::string::npos) {
			contactsFound.push_back(std::make_pair(contact.getId(), contact.getContactStr()));
		}
	}

	return contactsFound;
}

/**
 * @brief Zwraca kontakty w książce kontaktów jako wektor tekstowych danych kontaktów.
 * 
 * @return Wektor tekstowych danych kontaktów.
 */
std::vector <std::string> ContactBook::getContactsVstr()
{
	std::vector<std::string> vstr;

	for (auto& cnt : this->contacts) {
		vstr.push_back(cnt.getContactStr());
	}

	return vstr;
}

/**
 * @brief Zwraca nazwę książki kontaktów.
 * 
 * @return Nazwa książki kontaktów.
 */
std::string ContactBook::getName()
{
	return this->name;
}

/**
 * @brief Zwraca opis książki kontaktów.
 * 
 * @return Opis książki kontaktów.
 */
std::string ContactBook::getDesc()
{
	return this->desc;
}

/**
 * @brief Ustawia nazwę książki kontaktów.
 * 
 * @param name Nazwa książki kontaktów.
 * @throws std::length_error Jeśli nowa nazwa książki kontaktów jest nieprawidłowa.
 */
void ContactBook::setName(std::string name)
{
	if (this->name.length() <= 12 || this->name.length() > 0)
		this->name = name;
	else throw std::length_error("Nieprawidlowa dlugosc nazwy ksiazki!");
}

/**
 * @brief Ustawia opis książki kontaktów.
 * 
 * @param desc Opis książki kontaktów.
 * @throws std::length_error Jeśli opis książki kontaktów jest nieprawidłowy.
 */
void ContactBook::setDesc(std::string desc)
{
	if (this->desc.length() <= 50 || this->desc.length() > 0)
		this->desc = desc;
	else throw std::length_error("Nieprawidlowa dlugosc opisu ksiazki!");
}

/**
 * @brief Zwraca kontener obiektów kontaktów.
 * 
 * @return Wektor obiektów Contact reprezentujących kontakty.
 */
std::vector<Contact> ContactBook::getContacts()
{
	return this->contacts;
}

/**
 * @brief Zwraca kontener kontaktów jako wektor par.
 * 
 * Wektor par kontaktów ma duże znaczenie podczas korzystania z klasy AppView.
 * @return Wektor par zawierających identyfikator kontaktu i tekstową reprezentację kontaktu.
 */
std::vector <std::pair<int, std::string>> ContactBook::getContactPairs()
{
	std::vector <std::pair<int, std::string>> contactPairs;

	for (int i = 0; i < this->contacts.size(); i++) {
		contactPairs.push_back(std::make_pair(this->contacts[i].getId(), this->contacts[i].getContactStr()));
	}
	return contactPairs;
}

/**
 * @brief Zwraca liczbę kontaktów w książce kontaktowej.
 * 
 * @return Liczba kontaktów.
 */
int ContactBook::getNumContacts()
{
	return this->contacts.size();
}

/**
 * @brief Zwraca wskaźnik do kontaktu o podanym identyfikatorze.
 * 
 * Przeszukuje kontener kontaktów w celu odnalezenia kontaktu o podanym
 * identyfikatorze. W przypadku nie odnalezienia kontaktu rzuca wyjątek.
 * @param id Identyfikator kontaktu.
 * @return Wskaźnik do kontaktu.
 * @throws std::invalid_argument Jeśli nie można oznaleźć kontaktu o podanym identyfikatorze.
 */
Contact* ContactBook::getContact(int id)
{
	for (int i = 0; i < this->contacts.size(); i++) {
		if (id == this->contacts[i].getId()) {
			return &this->contacts[i];
		}
	}

	throw std::invalid_argument("Usuwanie nie powiodlo sie, nie ma takiego kontaktu w bazie!");
	return nullptr;
}