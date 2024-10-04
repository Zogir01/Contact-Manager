#pragma once

#include "Appview.h"
#include "ContactBookModel.h"
#include "Menu.h"

/**
 * @brief klasa AppController
 *
 * główna klasa programu obsługująca logiczną stronę aplikacji. Klasa ta jest pośrednikiem między innymi klasami.
 * Zgodnie z wzorcem projektowym MVC, klasa ta jest odpowiedzialna za wykonywanie najważniejszych funkcji z innych klas
 * takich jak ContactBookModel i AppView. Glownym celem tej klasy jest obsłuzenie wyborów w menu, poprzez tworzenie
 * obiektow klasy menu, oraz przypisanie konkretnych funkcji obiektom MenuOption. Klasa AppController zawiera
 * wyłacznie takie funkcje zgodnie z jej zamysłem.
 *
 * \version alpha 0.1
 */
class AppController {
private:

	AppView view; /**< obiekt klasy @link AppView @endlink .*/
	ContactBookModel model; /**< obiekt klasy @link ContactBookModel @endlink .*/
	Menu mainMenu; /**< Główne menu aplikacji. */
	Menu booksMenu; /**< Menu operacji na książkach. */
	Menu bookEnterMenu; /**< Menu operacji na kontaktach */
	Menu settingsMenu; /**< Menu ustawień aplikacji. */
	Menu sortMenu; /**< Menu ustawień / wyboru sortowania. */
	Menu searchMenu; /**< Menu wyboru frazy wyszukań. */

	int openBookIndex; /**< indeks aktualnie otwartej książki */
	std::string searchInput; /**< wpisany tekst do wyszukania */
	std::string searchFormula; /**< formuła wyszukiwania */

	void enterMainMenu();
	void enterBooksMenu();
	void enterSettingsMenu();
	void enterSortMenu();
	void enterContactsMenu();
	void enterSearchMenu();

	void showBook();
	void addBook();
	void editBook();
	void deleteBook();

	void addContact();
	void deleteContact();
	void editContacts();
	void searchContacts(std::string formula);
	
	void sortContacts(std::string);
	void changeColor();
	void changeFont();
	void saveToFileOptions();

	void testowa();
	
public:
	AppController();
	void start();
};
