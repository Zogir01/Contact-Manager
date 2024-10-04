#include "ContactBookModel.h"

/**
 * @brief Dodaje nową książkę kontaktów do kontenera w modelu.
 * 
 * @param name Nazwa książki kontaktów.
 * @param desc Opis książki kontaktów.
 */
void ContactBookModel::addBook(std::string name, std::string desc) {
    ContactBook book(name, desc);
    this->books.push_back(book);
}

/**
 * @brief Zwraca wskaźnik do książki kontaktowej o podanym identyfikatorze.
 * 
 * W przypadku nie odnalezienia książki o podanym identyfikatorze, metoda
 * zwróci nullptr. Być może będzie konieczne aby metoda rzucała odpowiedni
 * wyjątek.
 * @param index Identyfikator książki kontaktów.
 * @return Wskaźnik do książki kontaktowej lub nullptr, jeśli indeks jest nieprawidłowy.
 */
ContactBook* ContactBookModel::getBook(int index) {
    if (index >= 0 && index < this->books.size()) {
        return &this->books[index];
    }
    return nullptr;
}

/**
 * @brief Zwraca wektor książek kontaktowych w formie tekstowej.
 * 
 * Zwracana forma tekstowa to zmienna typu std::string, która łączy nazwę
 * oraz opis książki kontaktów
 * @return Wektor książek kontaktów w formie tekstowej.
 */
std::vector<std::string> ContactBookModel::getBooksVstr()
{
    std::vector<std::string> vstr;

    for (auto& book : this->books)
    {
        vstr.push_back(book.getName() + ", " + book.getDesc());
    }
    return vstr;
}

/**
 * @brief Zwraca ilość książek kontaktów.
 * 
 * @return Ilość książek kontaktów.
 */
int ContactBookModel::getNumBooks() {
    return books.size();
}

/**
 * @brief Usuwa książkę kontaktów o podanym identyfikatorze.
 * 
 * Przeszukuje kontener książek kontaktów, w przypadku nie odnalezienia
 * książki o podanym identyfikatorze, zwraca false.
 * @param index Identyfikator książki kontaktów do usunięcia.
 * @return True, jeśli książka kontaktów została pomyślnie usunięta. False, jeśli identyfikator jest nieprawidłowy.
 */
bool ContactBookModel::deleteBook(int index)
{
    if (index >= 0 && index < books.size()) {
        this->books.erase(this->books.begin() + index);
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief Zapisuje dane książek kontaktowych do pliku binarnego.
 * 
 * Implementacja tej metody znajduje się w folderze projektu - "do wprowadzenia".
 * Występuje problem podczas implementacji w rozwiązaniu.
 * @param fileName Nazwa pliku.
 * @throws std::invalid_argument Jeśli nie można otworzyć pliku.
 * @attention Metoda niedokończona.
 */
void ContactBookModel::saveDataToFile(std::string fileName)
{
    std::ofstream file(fileName, std::ios::binary | std::ios::trunc);

    if (!file.is_open()) {
        throw std::invalid_argument("Nie można otworzyć pliku");
    }

    size_t size = this->books.size();
    file.write(reinterpret_cast<char*>(&size), sizeof(size));

    for (auto& book : this->books) {
        file.write(reinterpret_cast<const char*>(&book), sizeof(book));
    }

    file.close();
}

/**
 * @brief Wczytuje dane książek kontaktowych z pliku binarnego.
 * 
 * Implementacja tej metody znajduje się w folderze projektu - "do wprowadzenia".
 * Występuje problem podczas implementacji w rozwiązaniu.
 * @param fileName Nazwa pliku.
 * @throws std::invalid_argument Jeśli nie można otworzyć pliku lub wystąpił błąd odczytu liczby obiektów.
 * @attention Metoda niedokończona.
 */
void ContactBookModel::loadDataFromFile(std::string fileName)
{
    std::ifstream inputFile(fileName, std::ios::binary);

    if (!inputFile.is_open()) {
        throw std::invalid_argument("Nie można otworzyć pliku");
    }

    size_t numBooks;
    if (!inputFile.read(reinterpret_cast<char*>(&numBooks), sizeof(numBooks))) {
        throw std::invalid_argument("Błąd odczytu liczby obiektów!");
    }

    for (size_t i = 0; i < numBooks; i++) {
        ContactBook book;

        if (!inputFile.read(reinterpret_cast<char*>(&book), sizeof(book))) {
            throw std::invalid_argument("Błąd odczytu ksiazki!");
        }

        this->books.push_back(book);
    }

    inputFile.close();
}