/**
 * \brief klasa MenuOption
 *
 * Klasa MenuOption reprezentuje opcje w menu. Znajduje sie tutaj także obiekt funkcyjny std::function, 
 * który określa, jaka funkcja ma byc wykonywana przez obiekt MenuOption. 
 * Klasa ta jest mocno związana z klasą menu, gdyż obiekt klasy Menu powinien posiadać kontener obiektów
 * klasy MenuOption.
 *
 * \version alpha 0.1
 */

#pragma once

#include <iostream>
#include <functional>

class MenuOption {
private:
    std::string name; /**< nazwa opcji menu */
    std::string desc; /**< opis opcji menu */
    std::function<void()> function; /**< obiekt std::function do przechowywania dowolnej funkcji */

public:
    MenuOption(const std::string& name, const std::string& desc, const std::function<void()>& function);
    void callFunction() const;

    const std::string& getName() const;
    const std::string& getDesc() const;
    const std::function<void()>& getFunction() const;
};