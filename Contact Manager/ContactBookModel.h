/**
 * \brief klasa ContactBookModel
 *
 * Klasa ContactBookModel jest głównym modelem aplikacji, który odpowiada za zarządzanie kolekcją książek kontaktow. 
 * Umożliwia zapis i odczyt danych z pliku, dodawanie oraz usuwanie konkretnych ksiazek. Jest to klasa ktora jest mocno
 * powiazana z klasami ContactBook, Contact oraz AppController - głównej klasy aplikacji. 
 * Klasa AppController komunikuje się właśnie z modelem, rolą modelu jest więc komunikacja z klasami Contact
 * oraz ContactBook.
 *
 * \version alpha 0.1
 */

#pragma once

#include <vector>
#include "ContactBook.h"
#include <fstream>

// Model
class ContactBookModel {
private:
    std::vector<ContactBook> books; /**< kontener książek kontaktowych - obiektów klasy ContactBook */

public:
    void addBook(std::string name, std::string desc);
    bool deleteBook(int index);
    void saveDataToFile(std::string fileName);
    void loadDataFromFile(std::string fileName);
    ContactBook* getBook(int index);
    std::vector<std::string> getBooksVstr();
    int getNumBooks();
};

