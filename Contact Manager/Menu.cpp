#include "Menu.h"

/**
 * @brief Inicjalizuje obiekt menu.
 * 
 * Powodem wprowadzenia metody inicjalizującej jest struktura klas Menu oraz MenuOption
 * w aplikacji. Ważne jest aby nie inicjalizować obiektu tej klasy na etapie kompilacji,
 * tylko na etapie działania programu. @n
 * Metoda ta jest wykorzystywana w konstruktorze klasy @link AppController @endlink .
 * 
 * @param name Nazwa menu.
 * @param menu_options Wektor obiektów menu_options.
 */
void Menu::initMenu(const std::string& name, const std::vector<MenuOption> menu_options)
{
	this-> name = name;
	this->menu_options = menu_options;
}

/**
 * @brief Wywołuje funkcję przypisaną do opcji menu o podanym indeksie.
 * 
 * Wywołuje metodę @link MenuOption::callFunction() @endlink w celu wywołania 
 * funkcji, która znajduje się w klasie @link MenuOption @endlink .
 * 
 * @param index Indeks opcji menu.
 * @attention Nie zostaje sprawdzana poprawność wprowadzonego indexu.
 */
void Menu::callFunction(int index) {
	this->menu_options[index].callFunction();
}

/**
 * @brief Zwraca nazwę menu.
 * 
 * @return Nazwa menu.
 */
const std::string& Menu::getName() const
{ 
    return name; 
}

/**
 * @brief Zwraca wektor opcji menu.
 * 
 * @return Wektor obiektów MenuOption.
 */
const std::vector<MenuOption>& Menu::getOptions() const
{ 
    return this->menu_options; 
}

/**
 * @brief Zwraca wektor nazw opcji menu w formie tekstowej.
 * 
 * @return Wektor nazw opcji menu w formie tekstowej.
 */
std::vector<std::string> Menu::getOptionsVstr()
{ 
    std::vector<std::string> vstr;

    for (auto& option : this->menu_options)
    {
        vstr.push_back(option.getName());
    }
    return vstr;
}

/**
 * @brief Zwraca wektor opisów opcji menu w formie tekstowej.
 * 
 * @return Wektor opisów opcji menu w formie tekstowej.
 */
std::vector<std::string> Menu::getDescVstr()
{
    std::vector<std::string> vstr;

    for (auto& option : this->menu_options)
    {
        vstr.push_back(option.getDesc());
    }
    return vstr;
}

/**
 * @brief Zwraca liczbę opcji menu.
 * 
 * @return Liczba opcji menu.
 */
int Menu::getNumOptions() 
{ 
    return this->menu_options.size();
}


