/**
 * \brief klasa Menu
 *
 * Klasa Menu jest odpowiedzialna za tworzenie menu w uporz¹dkowany sposob. Obiekty tej klasy sa 
 * wykorzystywane stricte w klasie AppController. W klasie Menu znajduje sie kontener zawierajacy obiekty 
 * klasy MenuOption. 
 * Klasa ta nie posiada konstruktora, a wiêc konieczne jest zainjalizowanie obiektu klasy Menu kontenerem 
 * obiektów klasy MenuOption poprzez wywo³anie funkcji initMenu().
 *
 * \version alpha 0.1
 */

#pragma once

#include "MenuOption.h"

#include <iostream>
#include <functional>
#include <vector>

class Menu {
private:
    std::string name; /**< nazwa menu */
    std::vector<MenuOption> menu_options; /**< kontener opcji menu - obiektow klasy MenuOption */

public:
    void initMenu(const std::string& name, const std::vector<MenuOption> menu_options);
    void callFunction(int index);

   const std::string& getName() const;
   const std::vector<MenuOption>& getOptions() const;
   std::vector<std::string> getOptionsVstr();
   std::vector<std::string> getDescVstr();
   int getNumOptions();
};