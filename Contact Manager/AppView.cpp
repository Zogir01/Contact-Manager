#include "AppView.h"

/**
 * @brief metoda inicjalizująca widok aplikacji.
 * 
 * Inicjalizuje okna powiązane z biblioteką pdcurses nadając im zdefiniowane w preprocessorze parametry 
 * wysokosci i szerokosci okien. @n Następnie następuje inicjalizacja nazw, 
 * tytułów oraz obramowań okien aplikacji. Ustawiane są także klawisze specjalne
 * w celu poprawnego przechwytywania danych z wejścia od użytkownika. @n
 * Na końcu znajduje się inicjalizacja typowych ustawień dla biblioteki pdcurses.@n
 * Ze względu na mnogość różnych inicjalizacji pól klasy do przeprowadzenia, 
 * zrezygnowano do implementowania ich w konstruktorze. 
 *
 */
void AppView::init()
{
    // inicjalizacja okien
    this->wMain.handle = initscr(); // glowne okno - cala konsola
    this->wMenu.handle = subwin(this->wMain.handle, MENU_WIN_HEIGHT, MENU_WIN_WIDTH, 0, 0);
    this->wDisplay.handle = subwin(this->wMain.handle, DISPLAY_WIN_HEIGHT, DISPLAY_WIN_WIDTH, MENU_WIN_HEIGHT, 0);
    this->wInput.handle = subwin(this->wMain.handle, INPUT_WIN_HEIGHT, INPUT_WIN_WIDTH, 0, MENU_WIN_WIDTH);
    this->wStatus.handle = subwin(this->wMain.handle, STATUS_WIN_HEIGHT, STATUS_WIN_WIDTH, 0, MENU_WIN_WIDTH + INPUT_WIN_WIDTH);
    this->wMenuDesc.handle = subwin(this->wMain.handle, MENUDESC_WIN_HEIGHT, MENUDESC_WIN_WIDTH, MENU_WIN_HEIGHT + DISPLAY_WIN_HEIGHT, 0);
    
    // inicjalizacja nazw okien
    this->wMenu.name = "KONSOLA";
    this->wMain.name = "MENU GLOWNE";
    this->wDisplay.name = "WYSWIETLANIE";
    this->wInput.name = "INTERAKCJA";
    this->wStatus.name = "KOMUNIKATY";
    this->wMenuDesc.name = "OPIS";

    // dodawanie obramowania dla okien
    box(this->wMenu.handle, 0, 0);
    box(this->wDisplay.handle, 0, 0);
    box(this->wInput.handle, 0, 0);
    box(this->wStatus.handle, 0, 0);
    box(this->wMenuDesc.handle, 0, 0);

    // ustawienia klawiszy spejalnych dla okien
    keypad(this->wMenu.handle, TRUE);
    keypad(this->wDisplay.handle, TRUE);
    keypad(this->wInput.handle, TRUE);
    keypad(this->wStatus.handle, TRUE);
    keypad(this->wMenuDesc.handle, TRUE);

    // rysowanie tytulow dla okien 
    mvwprintw(this->wMenu.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wMenu.name.c_str());
    mvwprintw(this->wInput.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wInput.name.c_str());
    mvwprintw(this->wDisplay.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wDisplay.name.c_str());
    mvwprintw(this->wStatus.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wStatus.name.c_str());
    mvwprintw(this->wMenuDesc.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wMenuDesc.name.c_str());

    // od�wie�anie okien na ekranie
    refresh();
    wrefresh(this->wMenu.handle);
    wrefresh(this->wDisplay.handle);
    wrefresh(this->wInput.handle);
    wrefresh(this->wStatus.handle);
    wrefresh(this->wMenuDesc.handle);

    // dodatkowe ustawienia pdcurses // halfdelay(10); // nodelay(this->wBody, TRUE); // keypad(stdscr, TRUE);
    cbreak();
    noecho();
    curs_set(0);
}

/**
 * @brief Rysuje menu w oknie @link wMenu @endlink .
 * 
 * Przed wyrysowaniem menu, okno zostaje wyczyszczone, 
 * a następnie na nowo zostaje rysowanie obramowanie okna. Po wyrysowaniu
 * menu w oknie, następuje konieczne odświeżenie.
 * Rysowaniem menu i przechwytywaniem opcji w menu zajmuję się metoda 
 * @link selectMenuOption @endlink .
 * @param title Tytuł menu.
 * @param fields Wektor pól w menu w formie tekstowej.
 */
void AppView::drawMenu(const std::string title, const std::vector<std::string>& fields)
{
    wclear(this->wMenu.handle);
    box(this->wMenu.handle, 0, 0);

    mvwprintw(this->wMenu.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, title.c_str());
    for (int i = 0; i < fields.size(); i++)
    {
        mvwprintw(this->wMenu.handle, WINDOW_NAMES_Y + MENU_WIN_HEIGHT / fields.size() + i,
            MENU_WIN_WIDTH / 2 - fields[i].length() / 2, fields[i].c_str());
    }

    wrefresh(wMenu.handle);
}

/**
 * @brief Rysuje menu oraz sprawdza wybór użytkownika w oknie @link wMenu @endlink .
 * 
 * Przed wyrysowaniem menu, okno zostaje wyczyszczone,
 * a następnie na nowo zostaje rysowanie obramowanie okna. Po wyrysowaniu
 * menu w oknie, następuje konieczne odświeżenie. @n
 * Metoda przechwytuje wprowadzane klawisze przez użytkownika. Jeśli użytkownik zatwierdził opcje enterem,
 * zwraca index wybranej opcji. W przypadku wciśnięcia klawisza escape, zwraca index -1.
 * Index -1 powinien zostać sprawdzony podczas wywoływania metody w klasie @link AppController @endlink . 
 * @param title Tytuł menu.
 * @param fields Wektor pól wyboru w menu w formie tekstowej.
 * @param desc Wektor opisów menu w formie tekstowej.
 * @return Index wybranej opcji w menu.
 */
int AppView::selectMenuOption(const std::string title, const std::vector<std::string>& fields, const std::vector<std::string>& desc)
{
    int selected_option = 0; // zmienna przechowujaca wybrana opcje w menu
    int ch = 0; // zmienna przechowujaca wcisniety znak

    wclear(this->wMenu.handle);
    box(this->wMenu.handle, 0, 0);


    while (ch != 27 && ch != '\n')
    {
        mvwprintw(this->wMenu.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, title.c_str());
        for (int i = 0; i < fields.size(); i++)
        {
            if (selected_option == i) {
                wattron(this->wMenu.handle, A_REVERSE);

                mvwprintw(this->wMenu.handle, WINDOW_NAMES_Y + MENU_WIN_HEIGHT / fields.size() + i,
                    MENU_WIN_WIDTH / 2 - fields[i].length() / 2, fields[i].c_str());

                wattroff(this->wMenu.handle, A_REVERSE);

                this->printLnMenuDesc(desc[i]);
            }
            else {
                mvwprintw(this->wMenu.handle, WINDOW_NAMES_Y + MENU_WIN_HEIGHT / fields.size() + i,
                    MENU_WIN_WIDTH / 2 - fields[i].length() / 2, fields[i].c_str());
            }
        }
        // wrefresh(this->wMenu.handle);
        ch = wgetch(this->wMenu.handle);

        switch (ch)
        {
        case KEY_UP: {
            if (selected_option > 0)
                selected_option--;
            else selected_option = fields.size() - 1;
            break;
        }
        case KEY_DOWN: {
            if (selected_option < fields.size() - 1)
                selected_option++;
            else selected_option = 0;
            break;
        }
        case 27: {
            selected_option = -1;
        }
        default: {
            break;
        }
        }
    }
    return selected_option;
}

/**
 * @brief Rysuje tabelę danych w oknie @link wDisplay @endlink .
 * 
 * Przed wyrysowaniem tabeli, okno zostaje wyczyszczone,
 * a następnie na nowo zostaje rysowanie obramowanie okna. Kursor zostaje ustawiony
 * na niewidoczny. Po wyrysowaniu tabeli w oknie, następuje konieczne odświeżenie.
 * Rysowaniem tabeli i przechwytywaniem opcji w tabeli zajmuję się metoda
 * @link selectTableOption @endlink .
 * @param title Tytuł tabeli.
 * @param fields Wektor pól w tabeli w formie tekstowej.
 */
void AppView::drawTable(const std::vector<std::string>& fields)
{
    curs_set(0);
    wclear(this->wDisplay.handle);
    box(this->wDisplay.handle, 0, 0);
    mvwprintw(this->wDisplay.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wDisplay.name.c_str());
    for (int i = 0; i < fields.size(); i++)
    {
        mvwprintw(this->wDisplay.handle, WINDOW_NAMES_Y + i + 1, 1, fields[i].c_str());
    }
    wrefresh(wDisplay.handle);
}

/**
 * @brief Rysuje tabelę danych w oknie @link wDisplay @endlink .
 * 
 * W tym przeciązeniu metoda przyjmuje w parametrze wektor par, aby możliwe było
 * zidentyfikowanie danego pola. @n
 * Przed wyrysowaniem tabeli, okno zostaje wyczyszczone,
 * a następnie na nowo zostaje rysowanie obramowanie okna. Kursor zostaje ustawiony
 * na niewidoczny. Po wyrysowaniu tabeli w oknie, następuje konieczne odświeżenie.
 * Rysowaniem tabeli i przechwytywaniem opcji w tabeli zajmuję się metoda
 * @link selectTableOption @endlink .
 * @param title Tytuł tabeli.
 * @param fields Wektor par pól tabeli zawierających index pola oraz tekst pola.
 */
void AppView::drawTable(const std::vector<std::pair<int, std::string>>& fields)
{
    curs_set(0);
    wclear(this->wDisplay.handle);
    box(this->wDisplay.handle, 0, 0);
    mvwprintw(this->wDisplay.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wDisplay.name.c_str());
    for (int i = 0; i < fields.size(); i++)
    {
        mvwprintw(this->wDisplay.handle, WINDOW_NAMES_Y + i + 1, 1, fields[i].second.c_str());
    }
    wrefresh(wDisplay.handle);
}

/**
 * @brief Rysuje tabelę oraz sprawdza wybór użytkownika w oknie @link wTable @endlink .
 * 
 * Przed wyrysowaniem tabeli, okno zostaje wyczyszczone,
 * a następnie na nowo zostaje rysowanie obramowanie okna. Po wyrysowaniu
 * tabeli w oknie, następuje konieczne odświeżenie. @n
 * Metoda przechwytuje wprowadzane klawisze przez użytkownika. Jeśli użytkownik zatwierdził opcje enterem,
 * zwraca index wybranej opcji. W przypadku wciśnięcia klawisza escape, zwraca index -1.
 * Index -1 powinien zostać sprawdzony podczas wywoływania metody w klasie @link AppController @endlink .
 * @param title Tytuł tabeli.
 * @param fields Wektor pól wyboru w tabeli w formie tekstowej.
 * @return Index wybranej opcji w tabeli.
 */
int AppView::selectTableOption(const std::vector<std::string>& fields)
{
    curs_set(0);
    int selected_option = 0; // zmienna przechowujaca wybrana opcje w menu
    int ch = 0; // zmienna przechowujaca wcisniety znak

    // czyszczenie okna
    wclear(this->wDisplay.handle);
    box(this->wDisplay.handle, 0, 0);

    while (ch != 27 && ch != '\n') // 27 - ESC
    {
        mvwprintw(this->wDisplay.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wDisplay.name.c_str());
        for (int i = 0; i < fields.size(); i++)
        {
            if (selected_option == i) {
                // tworzenie efektu pod�wietlenia oraz wy�wietlanie danych.
                wattron(this->wDisplay.handle, A_REVERSE);
                mvwprintw(this->wDisplay.handle, WINDOW_NAMES_Y + i + 1, 1, fields[i].c_str());
                wattroff(this->wDisplay.handle, A_REVERSE);
            }
            else {
                mvwprintw(this->wDisplay.handle, WINDOW_NAMES_Y + i + 1, 1, fields[i].c_str());
            }
        }
        wrefresh(wDisplay.handle);
        ch = wgetch(this->wDisplay.handle);

        switch (ch)
        {
        case KEY_UP: {
            if (selected_option > 0)
                selected_option--;
            else selected_option = fields.size() - 1;
            break;
        }
        case KEY_DOWN: {
            if (selected_option < fields.size() - 1)
                selected_option++;
            else selected_option = 0;
            break;
        }
        case 27: {
            selected_option = -1;
        }
        default: {
            break;
        }
        }
    }
    // zwracamy wybrana opcje, dlatego w funkcjach dla menu, mozemy robic konkretne dzialania.
    return selected_option;
}

/**
 * @brief Rysuje tabelę oraz sprawdza wybór użytkownika w oknie @link wTable @endlink .
 * 
 * W tym przeciązeniu metoda przyjmuje w parametrze wektor par, aby możliwe było
 * zidentyfikowanie danego pola. @n
 * Przed wyrysowaniem tabeli, okno zostaje wyczyszczone,
 * a następnie na nowo zostaje rysowanie obramowanie okna. Po wyrysowaniu
 * tabeli w oknie, następuje konieczne odświeżenie. @n
 * Metoda przechwytuje wprowadzane klawisze przez użytkownika. Jeśli użytkownik zatwierdził opcje enterem,
 * zwraca index wybranej opcji. W przypadku wciśnięcia klawisza escape, zwraca index -1.
 * Index -1 powinien zostać sprawdzony podczas wywoływania metody w klasie @link AppController @endlink .
 * @param title Tytuł tabeli.
 * @param fields Wektor par pól tabeli zawierających index pola oraz tekst pola.
 * @return Index wybranej opcji w tabeli.
 */
int AppView::selectTableOption(const std::vector<std::pair<int, std::string>>& fields)
{
    curs_set(0);
    int selected_option = 0; // zmienna przechowujaca wybrana opcje w menu
    int ch = 0; // zmienna przechowujaca wcisniety znak

    this->printLnStatus(std::to_string(fields.size()));

    // czyszczenie okna
    wclear(this->wDisplay.handle);
    box(this->wDisplay.handle, 0, 0);

    while (ch != 27 && ch != '\n') // 27 - ESC
    {
        mvwprintw(this->wDisplay.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wDisplay.name.c_str());
        for (int i = 0; i < fields.size(); i++)
        {
            if (selected_option == i) {
                // tworzenie efektu pod�wietlenia oraz wy�wietlanie danych.
                wattron(this->wDisplay.handle, A_REVERSE);
                mvwprintw(this->wDisplay.handle, WINDOW_NAMES_Y + i + 1, 1, fields[i].second.c_str());
                wattroff(this->wDisplay.handle, A_REVERSE);
            }
            else {
                mvwprintw(this->wDisplay.handle, WINDOW_NAMES_Y + i + 1, 1, fields[i].second.c_str());
            }
        }
        wrefresh(wDisplay.handle);
        ch = wgetch(this->wDisplay.handle);

        switch (ch)
        {
        case KEY_UP: {
            if (selected_option > 0)
                selected_option--;
            else selected_option = fields.size() - 1;
            break;
        }
        case KEY_DOWN: {
            if (selected_option < fields.size() - 1)
                selected_option++;
            else selected_option = 0;
            break;
        }
        case 27: {
            selected_option = -1;
        }
        default: {
            break;
        }
        }
    }
    if (selected_option != -1)
        return fields[selected_option].first;
    return selected_option;
    // zwracamy id wybranej opcji
}

/**
 * @brief Wypisuje opis menu / opis opcji w menu w oknie @link wMenuDesc @endlink .
 * 
 * Przed wypisaniem tekstu, okno zostaje wyczyszczone oraz występuje ponowne rysowanie obramowania.
 * Na nowo zostaje wypisywany opis okna. @n
 * Następnie po przeładowaniu okna, opis menu może zostać wypisany. Konieczne jest odświeżenie okna.
 * @param str Opis opcji w menu / opis menu.
 */
void AppView::printLnMenuDesc(std::string str)
{
    wclear(this->wMenuDesc.handle);
    box(this->wMenuDesc.handle, 0, 0);
    mvwprintw(this->wMenuDesc.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wMenuDesc.name.c_str());

    mvwaddstr(this->wMenuDesc.handle, WINDOW_NAMES_Y + 1, 2, str.c_str());
    wrefresh(this->wMenuDesc.handle);
}

/**
 * @brief Wyświetla komunikat statusowy na ekranie w oknie @link wStatus @endlink .
 *
 * Metoda czyszczi zawartość okna i rysuje ponownie obramowanie.
 * Następnie wyświetla nazwę okna w lewym górnym rogu.
 * Komunikat statusowy przekazany jako parametr `str` zostaje wyświetlony
 * w lewym górnym rogu okna "wStatus", pod nazwą okna.
 * Na koniec odświeżane jest okno "wStatus", aby zmiany były widoczne na ekranie.
 *
 * @param str komunikat statusowy do wyświetlenia
 */
void AppView::printLnStatus(std::string str)
{

    wclear(this->wStatus.handle);
    box(this->wStatus.handle, 0, 0);
    mvwprintw(this->wStatus.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wStatus.name.c_str());

    mvwaddstr(this->wStatus.handle, 1 + WINDOW_NAMES_Y + 1, 2, str.c_str());
    wrefresh(this->wStatus.handle);
}

/**
 * @brief Czyści zawartość okna @link wStatus @endlink .
 *
 * Metoda usuwa wszystkie zawartości znajdujące się w oknie @link wStatus @endlink
 * poprzez wyczyszczenie go oraz ponownie narysowanie obramowania.
 * Następnie wyświetla nazwę okna w lewym górnym rogu.
 * Na koniec okno jest odświeżane, aby zmiany były widoczne na ekranie.
 */
void AppView::clearStatus()
{
    wclear(this->wStatus.handle);
    box(this->wStatus.handle, 0, 0);
    mvwprintw(this->wStatus.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wStatus.name.c_str());
    wrefresh(this->wStatus.handle);
}

/**
 * @brief Czyści zawartość okna @link wDisplay @endlink .
 *
 * Metoda usuwa wszystkie zawartości znajdujące się w oknie @link wDisplay @endlink
 * poprzez wyczyszczenie go oraz ponownie narysowanie obramowania.
 * Następnie wyświetla nazwę okna w lewym górnym rogu.
 * Na koniec okno jest odświeżane, aby zmiany były widoczne na ekranie.
 */
void AppView::clearTable()
{
    wclear(this->wDisplay.handle);
    box(this->wDisplay.handle, 0, 0);
    mvwprintw(this->wDisplay.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wDisplay.name.c_str());
    wrefresh(this->wDisplay.handle);
}

/**
 * @brief Czyści zawartość okna @link wInput @endlink .
 *
 * Metoda usuwa wszystkie zawartości znajdujące się w oknie @link wInput @endlink
 * poprzez wyczyszczenie go oraz ponownie narysowanie obramowania.
 * Następnie wyświetla nazwę okna w lewym górnym rogu.
 * Na koniec okno jest odświeżane, aby zmiany były widoczne na ekranie.
 */
void AppView::clearInput()
{
    wclear(this->wInput.handle);
    box(this->wInput.handle, 0, 0);
    mvwprintw(this->wInput.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wInput.name.c_str());
    wrefresh(this->wInput.handle);
}

/**
 * @brief Przerysowuje od nowa okno.
 * 
 * Metoda na nowo rysuje obramowanie oraz nazwę okna przekazanego
 * w parametrze `win`. @n
 * Po zakończeniu tych operacji konieczne jest odświeżenie ekranu,
 * aby wprowadzone zmiany były widoczne dla użytkownika.
 * @param win okno, które ma zostać odświeżone.
 */
void AppView::redrawWindow(const Window& win)
{
    box(win.handle, 0, 0);
    mvwprintw(win.handle, 0, 2, win.name.c_str());
    refresh();
    wrefresh(win.handle);
}

/**
 * @brief Przerysowuje wszystkie okna aplikacji.
 * 
 * Metoda na nowo rysuje obramowania oraz nazwy wszystkich okien aplikacji.@n
 * Po zakończeniu tych operacji konieczne jest odświeżenie ekranu,
 * aby wprowadzone zmiany były widoczne dla użytkownika.
 * @param win okno, które ma zostać odświeżone.
 */
void AppView::redrawWindows()
{
    box(wMenu.handle, 0, 0);
    box(wDisplay.handle, 0, 0);
    box(wInput.handle, 0, 0);
    box(wStatus.handle, 0, 0);

    mvwprintw(this->wMenu.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wMenu.name.c_str());
    mvwprintw(this->wInput.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wInput.name.c_str());
    mvwprintw(this->wDisplay.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wDisplay.name.c_str());
    mvwprintw(this->wStatus.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wStatus.name.c_str());
    mvwprintw(this->wMenuDesc.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wMenuDesc.name.c_str());

    refresh();
    wrefresh(this->wMenu.handle);
    wrefresh(this->wDisplay.handle);
    wrefresh(this->wInput.handle);
    wrefresh(this->wStatus.handle);
}

/**
 * @brief Przechwytuje wprowadzane klawisze przez użytkownika.
 * 
 * Metoda przechwytuje wejście użytkownika. Na biężąco zmienia wartość na adresie przekazywanym
 * w parametrze `input` co pozwala na analizę całości wprowadzanego tekstu.
 * W warunku wprowadzany znak zostaje sprawdzany czy jet odpowiednim znakiem typu ascii.
 * W przypadku wciśnięcia klawisza backspace, zostaje usunięty ostatni znak wprowadzanego tekstu. @n
* Po zakończeniu tych operacji konieczne jest odświeżenie ekranu,
 * aby wprowadzone zmiany były widoczne dla użytkownika.
 * @param input wskaźnik na zmienną wprowadzanego tekstu.
 * @return Kod wprowadzonego znaku.
 */
int AppView::handleInput(std::string* input)
{
    curs_set(1);
    std::string toShow = "Wyszukaj: " + *input;
    mvwaddstr(this->wInput.handle, 2, 2, toShow.c_str());
    int key = wgetch(this->wInput.handle);

    if (key == '\b') {
        if (input->length() > 0) {
            input->pop_back();
        }
    }
    else if (key >= 0 && key <= 255) { 
        if (isprint(key)) {
            *input += key; 
        }
    }

    wclear(this->wInput.handle);
    box(this->wInput.handle, 0, 0);
    mvwprintw(this->wInput.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wInput.name.c_str());
    wrefresh(this->wInput.handle);
    toShow = "Wyszukaj: " + *input;
    mvwaddstr(this->wInput.handle, 2, 2, toShow.c_str());

    return key;
}

/**
 * @brief Rysuje obszar wpisywania danych oraz przechwytuje wprowadzane przez użytkownika klawisze.
 * 
 * ---------- DO NAPISANIA ----------- @n
 * Po zakończeniu tych operacji konieczne jest odświeżenie ekranu,
 * aby wprowadzone zmiany były widoczne dla użytkownika.
 * @param 
 * @return Kod wprowadzonego znaku.
 */
std::vector<std::string> AppView::drawInputBox(std::vector<std::pair<std::string, std::string>> labels, int* ch)
{
    int numOfFields = labels.size();
    int activeField = 0;  // Indeks aktualnie aktywnego pola edycji
    int cursorPos = labels[activeField].second.length(); // indeks kursora w pojedynczym stringu

    std::vector<std::string> results; // wektor rezultatow 

    // zapisz rezultaty, aby w przypadku wyjscia zwrocic te same dane;
    for(auto& label : labels) {
        results.push_back(label.second);
    }

    cbreak();  // Włączenie trybu "cbreak" - znaki wpisywane przez uzytkownika sa natychmiast przekazywane do programu
    noecho();  // Włączenie trybu "noecho" - znaki wpisywane przez uzytkownika nie sa wyświetlane na ekranie
    curs_set(1); // ustawienie wskaznika kursora na widoczny

    this->printLnMenuDesc("NACISNIJ (ENTER) - BY ZAAKCEPTOWAC ZMIANY, (ESC) - ABY ANULOWAC EDYCJE");

    while (*ch != 27 && *ch != '\n') { // KEY_ESCAPE, KEY_ENTER
        // Wyczyszczenie ekranu, oraz ponowne rysowanie obramowania oraz tytulu
        wclear(this->wInput.handle);
        box(this->wInput.handle, 0, 0);
        mvwprintw(this->wInput.handle, WINDOW_NAMES_Y, WINDOW_NAMES_X, this->wInput.name.c_str());
        wrefresh(this->wInput.handle);

        // Wyświetlenie wszystkich pól edycji
        for (int i = 0; i < numOfFields; i++) {
            // sprawdzanie pola (labels.first), czy je podswietlic metoda wattron
            if (i == activeField) {
                wattron(this->wInput.handle, A_REVERSE);
                mvwprintw(this->wInput.handle, i + WINDOW_NAMES_Y + 2, 2, labels[i].first.c_str()); 
                wattroff(this->wInput.handle, A_REVERSE);
                mvwprintw(this->wInput.handle, i + WINDOW_NAMES_Y + 2, 2 + labels[i].first.length(), ": "); 
            }
            else {
                mvwprintw(this->wInput.handle, i + WINDOW_NAMES_Y + 2, 2, "%s: ", labels[i].first.c_str()); 
            }
            // wyswietla wartosc pola bez podswietlenia (labels.second)
            mvwprintw(this->wInput.handle, i + WINDOW_NAMES_Y + 2, labels[i].first.length() + 4, labels[i].second.c_str());
            
        }
        
        // przesuniecie wskaznika kursora
        wmove(this->wInput.handle, activeField + WINDOW_NAMES_Y + 2, labels[activeField].first.length() + 4 + cursorPos);
        wrefresh(this->wInput.handle);  // Odświeżenie ekranu

        // Oczekiwanie na wejście użytkownika
        *ch = wgetch(this->wInput.handle);
        switch (*ch) {
            case KEY_UP:  // Przejście do poprzedniego pola edycji
                if (activeField > 0) {
                    activeField--;
                    cursorPos = labels[activeField].second.length();
                }
                break;
            case KEY_DOWN:  // Przejście do następnego pola edycji
                if (activeField < numOfFields - 1) {
                    activeField++;
                    cursorPos = labels[activeField].second.length();
                }
                break;
            case '\b':  // Usunięcie znaku z aktualnego pola edycji na aktualnej pozycji kursora
                if (cursorPos > 0) {
                    labels[activeField].second.erase(cursorPos - 1, 1);
                    cursorPos--;
                }
                break;
            case KEY_LEFT: { // przejscie wskaznikiem kursora w lewo
                if (cursorPos > 0) {
                    cursorPos--;
                }
            } 
            break;
            case KEY_RIGHT: { // przejscie wskaznikiem kursora w prawo, sprawdzamy czy nie wychodzimy poza zakres
                if (cursorPos < labels[activeField].second.length()) {
                    cursorPos++;
                }
                break;
            }     
            case '\n': { // w przypadku enter - zapis nowych rezultatow
                results.clear();
                for(auto& label : labels) {
                    results.push_back(label.second);
                }
               
            } 
            default:  // Dodanie wpisanego znaku do aktualnego pola edycji na aktualnej pozycji kursora
                if (isprint(*ch)) { // sprawdzenie znaku, czy jest to litera, cyfra, lub znak specjalny
                    if (cursorPos < INPUT_WIN_WIDTH / 2) {
                        labels[activeField].second.insert(cursorPos, 1, static_cast<char>(*ch));
                        cursorPos++;
                    }
                }
            break;
        }
    }

    return results;
}