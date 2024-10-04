#include "MenuOption.h"

/**
 * @brief Konstruktor klasy.
 * 
 * Inicjalizuje obiekt MenuOption domyślnymi wartościami.
 * @param name Nazwa opcji menu.
 * @param desc Opis opcji menu.
 * @param function Funkcja wywoływana po wybraniu opcji menu.
 */
MenuOption::MenuOption(const std::string& name, const std::string& desc, const std::function<void()>& function)
{
	this->name = name;
	this->desc = desc;
	this->function = function;
}

/**
 * @brief Wywołuje funkcję przypisaną do opcji menu.
 * 
 */
void MenuOption::callFunction() const {
	this->function();
}

/**
 * @brief Zwraca nazwę opcji menu.
 * 
 * @return Nazwa opcji menu.
 */
const std::string& MenuOption::getName() const 
{ 
	return this->name; 
}

/**
 * @brief Zwraca opis opcji menu.
 * 
 * @return Opis opcji menu.
 */
const std::string& MenuOption::getDesc() const 
{ 
	return this->desc; 
}

/**
 * @brief Zwraca funkcję przypisaną do opcji menu.
 * 
 * Zwraca adres funkcji przez referencję jako stała aby zapewnić,
 * że funkcja nie będzie w żaden sposób modyfikowana.
 * @return Funkcja przypisana do opcji menu.
 */
const std::function<void()>& MenuOption::getFunction() const 
{ 
	return this->function; 
}