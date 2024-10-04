#include "AppController.h" 

/**
 * \brief bezparametryczny konstruktor klasy AppController.
 *
 * Ma na celu inicjalizacje pól klasy. Pełni ważną rolę podczas inicjalizacji obiektów Menu.
 * Najpierw tworzymy obiekty MenuOption, przypisując na etapie kompilacji konkretne dane do 
 * opcji w menu. Opcjom w menu przypisujemy także odpowiednie funkcje poprzez zastosowanie
 * lambdy. Nastepnie wszystkie menu są inicjalizowane za pomocą metody @link initMenu() @endlink z klasy Menu.
 *
 */
AppController::AppController()
{
    this->openBookIndex = -1;
    this->searchInput = "";
    this->searchFormula= "not-set";

    std::vector<MenuOption> mainMenuOptions = {
        MenuOption("KSIAZKI", "OPERACJE NA KSIAZKACH", [this]() { this->enterBooksMenu(); }),
        MenuOption("USTAWIENIA", "ZMIEN USTAWIENIA", [this]() { this->enterSettingsMenu(); }),
        MenuOption("WYJDZ", "WYBIERZ ABY WYJSC Z PROGRAMU", [this]() { this->testowa(); })
    };

    std::vector<MenuOption> booksMenuOptions = {
        MenuOption("OTWORZ KSIAZKE", "WYBIERZ KSIAZKE ABY JA OTWORZYC", [this]() { this->showBook(); }),
        MenuOption("DODAJ KSIAZKE", "DODAJ NOWA KSIAZKE", [this]() { this->addBook(); }),
        MenuOption("USUN KSIAZKE", "WYBIERZ KSIAZKE KTORA CHCESZ USUNAC", [this]() { this->deleteBook(); }),
        MenuOption("EDYTUJ KSIAZKE", "WYBIERZ KSIAZKE ABY ZMIENIC TYTUL", [this]() { this->editBook(); }),
        MenuOption("COFNIJ", "COFNIJ DO MENU GLOWNEGO", [this]() {this->enterMainMenu(); })
    };

    std::vector<MenuOption> bookEnterMenuOptions = {
        MenuOption("WYSZUKAJ KONTAKTY", "WYBIERZ ABY WYSZUKAC KONTAKTY", [this]() { this->enterSearchMenu(); }),
        MenuOption("SORTUJ KONTAKTY", "WYBIERZ ABY POSORTOWAC KONTAKTY", [this]() { this->enterSortMenu(); }),
        MenuOption("DODAJ KONTAKT", "WYBIERZ ABY DODAC NOWY KONTAKT", [this]() { this->addContact(); }),
        MenuOption("USUN KONTAKT", "WYBIERZ KONTAKT KTORY CHCESZ USUNAC", [this]() { this->deleteContact(); }),
        MenuOption("EDYTUJ KONTAKT", "WYBIERZ KONTAKT KTORY CHCESZ EDYTOWAC", [this]() { this->editContacts(); }),
        MenuOption("COFNIJ", "COFNIJ DO MENU KSIAZEK", [this]() {this->enterBooksMenu(); })
    };

    std::vector<MenuOption> searchMenuOptions = {
        MenuOption("WYSZUKAJ PO IMIENIU", "WYBIERZ ABY WYSZUKAC KONTAKTY", [this]() { this->searchContacts("byName"); }),
        MenuOption("WYSZUKAJ PO NAZWISKU", "WYBIERZ ABY POSORTOWAC KONTAKTY", [this]() { this->searchContacts("byLastName"); }),
        MenuOption("WYSZUKAJ PO NUMERZE TELEFONU", "WYBIERZ ABY DODAC NOWY KONTAKT", [this]() { this->searchContacts("byPhoneNumber"); }),
        MenuOption("COFNIJ", "COFNIJ DO MENU KONTAKTOW", [this]() {this->enterBooksMenu(); })
    };

    std::vector<MenuOption> settingsMenuOptions = {
        MenuOption("ZMIEN KOLORY", "WYBIERZ ABY ZMIENIC USTAWIENIA KOLOROW", [this]() { this->changeColor(); }),
        MenuOption("USTAW CZCIONKE", "WYBIERZ ABY USTAWIC CZCIONKE KONSOLI", [this]() { this->changeFont(); }),
        MenuOption("OPCJE ZAPISU", "WYBIERZ OPCJE ZAPISYWANIA DANYCH", [this]() { this->saveToFileOptions(); }),
        MenuOption("COFNIJ", "COFNIJ DO GLOWNEGO MENU", [this]() { this->enterSettingsMenu(); })
    };

    std::vector<MenuOption> sortMenuOptions = {
        MenuOption("ALFABETYCZNIE (IMIE)", "SORTUJ ALFABETYCZNIE PO IMIENIU", [this]() { this->sortContacts("byName"); }),
        MenuOption("ALFABETYCZNIE (NAZWISKO)", "SORTUJ ALFABETYCZNIE PO NAZWISKU", [this]() { this->sortContacts("byLastName"); }),
        MenuOption("PO ID (ROSNACO)", "SORTUJ PO ID ROSNACO", [this]() { this->sortContacts("byIdAsc"); }),
        MenuOption("PO ID (MALEJACO)", "SORTUJ PO ID MALEJACO", [this]() { this->sortContacts("byIdDesc"); }),
        MenuOption("COFNIJ", "COFNIJ DO GLOWNEGO MENU", [this]() { this->enterMainMenu(); })
    };

    mainMenu.initMenu("MENU GLOWNE", mainMenuOptions);
    booksMenu.initMenu("TWOJE KSIAZKI", booksMenuOptions);
    bookEnterMenu.initMenu("TWOJE KONTAKTY", bookEnterMenuOptions);
    settingsMenu.initMenu("USTAWIENIA", settingsMenuOptions);
    sortMenu.initMenu("WYBIERZ SORTOWANIE", sortMenuOptions);
    searchMenu.initMenu("WYBIERZ OPCJE WYSZUKIWANIA", searchMenuOptions);
}

/**
 * @brief główna metoda klasy, jest ona pierwszą wywolywaną funkcją.
 *
 * Inicjalizuje obiekt AppView, który jest kluczowy do poprawnego działania
 * interfejsu użytkownika oraz "przenosi" do głównego menu.
 *
 */
void AppController::start()
{
    //this->model.loadDataFromFile("plik.dat");
    view.init();
    this->enterMainMenu();
    //this->model.saveDataToFile("plik.dat");
}

/**
 * @brief metoda wywoływana podczas wejścia do głównego menu.
 *
 *  Wywoluje metode obiektu klasy AppView rysujacą menu, oraz analizujacą interakcje 
 *  uzytkownika oraz analizuje zwracany index - ktory jest wybrana opcja w menu.
 *
 * W przypadku indexu roznego od -1, wywoluje metode wybranego menu na podstawie indexu.\n
 * W przypadku indexu rownego 1 nastepuje wyjscie z aplikacji.\n
 *
 */
void AppController::enterMainMenu()
{
    view.clearTable();
    int index = this->view.selectMenuOption(this->mainMenu.getName(), this->mainMenu.getOptionsVstr(), this->mainMenu.getDescVstr());

    if (index != -1) {
        this->mainMenu.callFunction(index);
    }
}

/**
 * \brief metoda wywoływana podczas wejścia do menu książek.
 *
 *  Wywołuje metode rysujaca tabele danych, przekazujac w parametrze kontener danych tekstowych odnosnie ksiazek.
 *  Wywoluje metode obiektu klasy AppView rysujaca menu, oraz analizujaca interakcje 
 *  uzytkownika oraz analizuje zwracany index - ktory jest wybrana opcja w menu.
 *
 * W przypadku indexu roznego od -1, wywoluje metode wybranego menu na podstawie indexu.\n
 * W przypadku indexu rownego 1 nastepuje powrot do menu glownego.\n
 *
 */
void AppController::enterBooksMenu()
{
    this->view.drawTable(this->model.getBooksVstr());
    int index = this->view.selectMenuOption(this->booksMenu.getName(), this->booksMenu.getOptionsVstr(), this->booksMenu.getDescVstr());

    if (index != -1) {
        this->booksMenu.callFunction(index);
    }
    else {
        this->enterMainMenu();
    }
}

/**
 * \brief metoda wywolywana podczas wejscia do menu ustawien.
 * 
 *  \attention NIEDOKONCZONA
 * 
 *  Metoda ta jest niedokonczona. Implementacja zmieniania ustawien nie zostala jeszcze
 *  zaimplementowana. Po ukonczeniu prac zwiazanych z dodawaniem ustawien z mozliwoscia
 *  personalizowania aplikacji, zostanie zaimplementowana metoda enterSettingsMenu.
 *
 */
void AppController::enterSettingsMenu()
{
    int index = this->view.selectMenuOption(this->settingsMenu.getName(), this->settingsMenu.getOptionsVstr(), this->settingsMenu.getDescVstr());

    if (index != -1) {
        this->settingsMenu.callFunction(index);
    }
    else {
        this->enterMainMenu();
    }
}

/**
 * \brief metoda wywolywana podczas wejscia do menu sortowania.
 *
 * \attention NIEDOKONCZONA
 * 
 *  Metoda ta jest niedokonczona. W zwiazku z problemem z sortowaniem danych, nie zostalo ono
 *  jeszcze zaimplementowane. Po ukonczeniu prac zwiazanych z sortowaniem danych, zostanie stworzona
 *  implementacja metody enterSortMenu.
 * 
 */
void AppController::enterSortMenu()
{
    int index = view.selectMenuOption(this->sortMenu.getName(), this->sortMenu.getOptionsVstr(), this->sortMenu.getDescVstr());

    if (index != -1) {
        this->sortMenu.callFunction(index);
    }
    else {
        this->enterContactsMenu();
    }
}

/**
 * \brief metoda wywolywana podczas wejscia do menu kontaktow.
 *
 *  Wywoluje metode rysujaca tabele danych, przekazujac w parametrze kontener danych tekstowych odnosnie kontaktow.
 *  Wywoluje metode obiektu klasy AppView rysujaca menu, oraz analizujaca interakcje
 *  uzytkownika oraz analizuje zwracany index - ktory jest wybrana opcja w menu.
 *
 * W przypadku indexu roznego od -1, wywoluje metode wybranego menu na podstawie indexu. \n
 * W przypadku indexu rownego 1 nastepuje powrot do menu ksiazek. \n
 *
 */
void AppController::enterContactsMenu()
{
    this->view.drawTable(this->model.getBook(this->openBookIndex)->getContactsVstr());

    int index = view.selectMenuOption(this->bookEnterMenu.getName(), this->bookEnterMenu.getOptionsVstr(), this->bookEnterMenu.getDescVstr());

    if (index != -1) {
        this->bookEnterMenu.callFunction(index);
    }
    else {
        this->enterBooksMenu();
    }
}

/**
 * \brief metoda wywolywana podczas wejscia do menu wyszukiwania.
 *
 *  Wywoluje metode obiektu klasy AppView rysujaca menu, oraz analizujaca interakcje
 *  uzytkownika oraz analizuje zwracany index - ktory jest wybrana opcja w menu.
 *
 * W przypadku indexu roznego od -1, wywoluje metode wybranego menu na podstawie indexu. \n
 * W przypadku indexu rownego 1 nastepuje powrot do menu glownego.\n
 *
 */
void AppController::enterSearchMenu()
{
    this->view.drawMenu(this->bookEnterMenu.getName(), this->bookEnterMenu.getOptionsVstr());

    int index = this->view.selectMenuOption(this->searchMenu.getName(), this->searchMenu.getOptionsVstr(), this->searchMenu.getDescVstr());
    
    if (index != -1) {
        this->view.drawMenu(this->bookEnterMenu.getName(), this->bookEnterMenu.getOptionsVstr());
        this->searchMenu.callFunction(index);
    }

    this->enterContactsMenu();
}

/**
 * \brief metoda umozliwiajaca wybor ksiazki w menu.
 *
 *  Sprawdza czy istnieja utworzone ksiazki i na tej podstawie wykonuje dalsze operacje.
 *  
 *  W przypadku braku ksiazek - nastepuje powrot do menu ksiazek.\n
 *  W przypadku wystapienia ksiazki - wywoluje metode rysujaca tabele danych z ksiazkami, a nastepnie analizuje zwracany index.\n
 *             W przypadku indexu roznego od -1, ustawia index wybranej ksiazki w polu klasy, oraz przechodzi menu kontaktow.\n
 *             W przypadku indexu rownego 1 nastepuje powrot do menu ksiazek.\n
 *
 */
void AppController::showBook()
{
    if (model.getNumBooks() > 0) {
        int index = this->view.selectTableOption(this->model.getBooksVstr());
      
        if (index != -1) {
            this->openBookIndex = index;
            this->enterContactsMenu();
        }
    }

    this->enterBooksMenu();
}

/**
 * \brief Dodaje nowa ksiazke do kolekcji ksiazek w modelu.
 *
 *  Metoda umozliwiajaca dodanie nowej ksiazki poprzez wyswietlenie formularza.
 *  Metoda wyswietlajaca formularz przyjmuje wskaznik na zmienna "key" typu int, 
 *  ktora przechowuje informacje o wcisnietym klawiszu.
 * 
 *  Jesli zmienna key jest rowna 27 (klawisz escape), nastepuje wyjscie z petli. \n
 *      Jesli zmienna key jest rowna '\n' (klawisz enter), nastepuje proba dodania 
 *      ksiazki na podstawie zwroconych danych metoda wyswietlajaca formularz.\n
 *          Jesli proba dodania ksiazki sie powiedzie, wyswietla informacje o pomyslnym dodaniu ksiazki.\n
 *          jesli Jesli proba dodania ksiazki sie nie powiedzie, wyswietla komunikaty o napotkanym bledzie. \n
 *
 *  Po zakonczeniu operacji, metoda czysci formularz i tabele danych, a nastepnie ponownie rysuje tabele ksiazek oraz
 * przechodzi do menu ksiazek.
 */
void AppController::addBook()
{
    std::vector<std::pair<std::string, std::string>> data = {
    std::make_pair("Nazwa", ""),
    std::make_pair("Opis", ""),
    };

    std::vector<std::string> results; 
    int key = 0; // zmienna, ktorej adres przekazujemy do drawInputBox. 
    bool close = false;

    while (!close) {
        key = 0;
        results = this->view.drawInputBox(data, &key); // pobierz rezultaty z formularza

        if (key == '\n') { // jesli w formularzu kliknelismy klawisz enter
            try {
                this->model.addBook(results[0], results[1]); // sprobuj dodac ksiazke
                this->view.printLnStatus("Pomyslnie dodano nowa ksiazke!");
                close = true; // jesli sie uda to wyjdz z petli
            }
            catch (const std::invalid_argument& e) { // wylapuj ewentualne bledy
                this->view.printLnStatus("Podano zle dane! Sprawdz poprawnosc danych.");
            }
            catch (const std::length_error& e) {
                this->view.printLnStatus(e.what());
            }
            catch (const std::exception& e) {
                this->view.printLnStatus("Wystapil nieoczekiwany blad! Prosimy o zgloszenie bledu w naszym formularzu kontaktowym.");
            }

            if (close == false) { // jesli pojawil sie blad - do nastepnego formularza przekaz dane, ktore wpisywales wczesniej
                for (int i = 0; i < data.size(); i++) {
                    data[i].second = results[i];
                }
            }
        }
        else if (key == 27) {
            close = true;
        }
    }

    this->view.clearInput();
    this->view.clearTable();
    this->view.drawTable(model.getBooksVstr());
    this->enterBooksMenu();
}

/**
 * \brief Edytuje istniejaca ksiazke w kolekcji ksiazek w modelu.
 *
 * Metoda umozliwia edycje istniejacej ksiazki poprzez wyswietlenie formularza.
 * Metoda wyswietlajaca formularz przyjmuje wskaznik na zmienna "key" typu int, 
 * ktora przechowuje informacje o wcisnietym klawiszu.
 * 
 * Jesli zmienna key jest rowna 27 (klawisz escape), nastepuje wyjscie z petli. \n
 * Jesli zmienna key jest rowna '\n' (klawisz enter), nastepuje proba edycji 
 *            ksiazki na podstawie zwroconych danych metoda wyswietlajaca formularz.\n
 *            Jesli proba edycji ksiazki sie powiedzie, wyswietla informacje o pomyslnej edycji ksiazki.\n
 *            jesli Jesli proba edycji ksiazki sie nie powiedzie, wyswietla komunikaty o napotkanym bledzie. \n
 *
 * Po zakonczeniu operacji, metoda czysci formularz i tabele danych, a nastepnie ponownie rysuje tabele ksiazek oraz
 * przechodzi do menu ksiazek.
 * 
 */
void AppController::editBook()
{
    int index = this->view.selectTableOption(this->model.getBooksVstr());

    if (index != -1) {
        ContactBook* book = this->model.getBook(index);

        std::vector<std::pair<std::string, std::string>> data = {
        std::make_pair("Nazwa", book->getName()),
        std::make_pair("Opis", book->getDesc()),
        };

        std::vector<std::string> results;
        int key = 0; // zmienna, ktorej adres przekazujemy do drawInputBox. 
        bool close = false;

        while (!close) {
            key = 0;
            results = this->view.drawInputBox(data, &key); // pobierz rezultaty z formularza

            if (key == '\n') { // jesli w formularzu kliknelismy klawisz enter
                try {
                    book->editBook(results[0], results[1]); // sprobuj dodac kontakt
                    this->view.printLnStatus("Pomyslnie edytowano ksiazke!");
                    close = true; // jesli sie uda to wyjdz z petli
                }
                catch (const std::invalid_argument& e) { // wylapuj ewentualne bledy
                    this->view.printLnStatus("Podano zle dane! Sprawdz poprawnosc danych.");
                }
                catch (const std::length_error& e) {
                    this->view.printLnStatus(e.what());
                }
                catch (const std::exception& e) {
                    this->view.printLnStatus("Wystapil nieoczekiwany blad! Prosimy o zgloszenie bledu w naszym formularzu kontaktowym.");
                }

                if (close == false) { // jesli pojawil sie blad - do nastepnego formularza przekaz dane, ktore wpisywales wczesniej
                    for (int i = 0; i < data.size(); i++) {
                        data[i].second = results[i];
                    }
                }
            }
            else if (key == 27) {
                close = true;
            }
        }
        this->view.clearInput();
        this->view.clearTable();
        this->view.drawTable(model.getBooksVstr());
    }
    this->enterBooksMenu();
}

/**
 * @brief Usuwa ksiazke z kolekcji ksiazek w modelu.
 * 
 * Metoda umożliwia usuniecie istniejacej ksiazki poprzez wybor jej w tabeli.
 * Wywoluje metode rysujaca tabele danych, przekazujac w parametrze kontener danych tekstowych odnosnie ksiazek.
 * Analizuje zwracany index - ktory jest wybrana ksiazka z tabeli.
 *
 * W przypadku indexu roznego od -1, wywoluje metode wybranego menu na podstawie indexu.\n
 * W przypadku indexu rownego 1 nastepuje powrot do menu ksiazek.\n
 *
 */
void AppController::deleteBook()
{
    int index = this->view.selectTableOption(this->model.getBooksVstr());

    if (index != -1) {
        model.deleteBook(index);
        this->view.drawTable(model.getBooksVstr());
    }
    this->enterBooksMenu();
}

void AppController::addContact()
{
    ContactBook* book = model.getBook(this->openBookIndex);
    // tworzymy puste pary - bedziemy wyswietlac w formie: imie: (pusty string) z mozliwoscia edycji
    std::vector<std::pair<std::string, std::string>> data = {
    std::make_pair("Imie", ""),
    std::make_pair("Nazwisko", ""),
    std::make_pair("Nr. Telefonu", ""),
    std::make_pair("Adres email", "")
    };
   
    std::vector<std::string> results; // wektor rezultatow

    int key = 0; // zmienna, ktorej adres przekazujemy do drawInputBox. 

    bool close = false;

    while (!close) 
    {
        key = 0;

        // pobierz rezultaty z formularza
        results = this->view.drawInputBox(data, &key);
        
        // jesli w formularzu kliknelismy klawisz enter
        if (key == '\n') {
            try {
                book->addContact(std::stoi(results[2]), results[0], results[1], results[3]); // sprobuj dodac kontakt
                this->view.printLnStatus("Pomyslnie dodano nowy kontakt!");
                close = true; // jesli sie uda to wyjdz z petli
            }
            catch (const std::invalid_argument& e) { // wylapuj ewentualne bledy
                this->view.printLnStatus("Podano zle dane! Sprawdz poprawnosc danych.");
            }
            catch (const std::length_error& e) {
                this->view.printLnStatus(e.what());
            }
            catch (const std::exception& e) {
                this->view.printLnStatus("Wystapil nieoczekiwany blad! Prosimy o zgloszenie bledu w naszym formularzu kontaktowym.");
            }

            if (close == false) { // jesli pojawil sie blad - do nastepnego formularza przekaz dane, ktore wpisywales wczesniej
                for (int i = 0; i < data.size(); i++) {
                    data[i].second = results[i];
                }
            }
        }
        else if (key == 27) {
            close = true;
        }
    }

    this->view.clearInput();
    this->view.clearTable();
    this->view.drawTable(book->getContactsVstr());
    this->enterContactsMenu();
}


void AppController::deleteContact()
{
    ContactBook* book = this->model.getBook(this->openBookIndex);

    if (book->getNumContacts() > 0) {
        int id;
        if (this->searchInput.length() > 0) {
            id = this->view.selectTableOption(book->searchContacts(this->searchInput, this->searchFormula)); 
            this->searchInput = "";
        }
        else {
            id = this->view.selectTableOption(book->getContactPairs());
        }
        
        if (id != -1) {
            try {
                book->removeContact(id);
            }
            catch (std::invalid_argument& e) {
                this->view.printLnStatus(e.what());
            }

            this->view.drawTable(book->getContactsVstr());
            this->view.clearInput();
        }
    }
    this->enterContactsMenu();
}

void AppController::editContacts()
{
    ContactBook* book = this->model.getBook(this->openBookIndex);

    if (book->getNumContacts() > 0) {
        int id;
        if (this->searchInput.length() > 0) {
            id =  this->view.selectTableOption(book->searchContacts(this->searchInput, this->searchFormula));
            this->searchInput = "";
        }
        else {
            id = this->view.selectTableOption(book->getContactPairs());
        }

        if (id != -1) {
            int key = 0;
            bool close = false;
            Contact* cnt = book->getContact(id);

            std::vector<std::string> results;
            std::vector<std::pair<std::string, std::string>> data = {
                std::make_pair("Imie", cnt->getName()),
                std::make_pair("Nazwisko", cnt->getLastName()),
                std::make_pair("Nr. Telefonu", std::to_string(cnt->getPhoneNumber())),
                std::make_pair("Adres email", cnt->getEmail())
            };

            while (!close)
            {
                key = 0;
 
                results = this->view.drawInputBox(data, &key);
                if (key == '\n') {
                    try {
                        cnt->editContact(std::stoi(results[2]), results[0], results[1], results[3]);
                        this->view.printLnStatus("Pomyslnie edytowano kontakt!");
                        close = true;
                    }
                    catch (const std::invalid_argument& e) {
                        this->view.printLnStatus("Podano zle dane! Sprawdz poprawnosc danych.");
                    }
                    catch (const std::length_error& e) {
                        this->view.printLnStatus(e.what());
                    }
                    catch (const std::exception& e) {
                        this->view.printLnStatus("Wystapil nieoczekiwany blad! Prosimy o zgloszenie bledu w naszym formularzu kontaktowym.");
                    }

                    if (close == false) {
                        for (int i = 0; i < data.size(); i++) {
                            data[i].second = results[i];
                        }
                    }
                }
                else if (key == 27) {
                    close = true;
                }
            }
         
            this->view.clearTable();
            this->view.clearInput();
            this->view.drawTable(book->getContactsVstr());
        }
    }
    this->enterContactsMenu();
}

void AppController::searchContacts(std::string formula)
{
    std::string input;
    int key = 0;
    int windowSelection = 1;
    ContactBook* book = this->model.getBook(this->openBookIndex);

    while (key != 27 && key != '\n') {
        key = this->view.handleInput(&input); // przechwytuj klawisz
        this->view.drawTable(book->searchContacts(input, formula)); // na biezaco odswiezaj okno, szukajac kontaktow
        
        if (key == '\n') {
            int index = view.selectMenuOption(this->bookEnterMenu.getName(), this->bookEnterMenu.getOptionsVstr(), this->bookEnterMenu.getDescVstr());

            if (index != -1) {
                this->searchInput = input;
                this->searchFormula = formula;
                this->bookEnterMenu.callFunction(index);
            }
        }
    }
    this->enterContactsMenu();
}

void AppController::sortContacts(std::string)
{

}

void AppController::changeColor()
{

}

void AppController::changeFont()
{

}

void AppController::saveToFileOptions()
{

}

void AppController::testowa()
{

}