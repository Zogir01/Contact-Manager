#include <curses.h>
#include <vector>
#include <functional>
#include <iostream>
#include <tuple>

#include "ContactBook.h"

#define MENU_WIN_HEIGHT LINES / 3 /**< definicja preprocesora wysokosci menu */    
#define MENU_WIN_WIDTH COLS / 4 /**< definicja preprocesora szerokosci menu */   

#define INPUT_WIN_HEIGHT LINES / 3 /**< definicja preprocesora wysokosci okna wyszukiwania */     
#define INPUT_WIN_WIDTH COLS / 2 /**< definicja preprocesora szerokosci okna wyszukiwania */   

#define STATUS_WIN_HEIGHT LINES / 3 /**< definicja preprocesora wysokosci okna statusu */   
#define STATUS_WIN_WIDTH COLS / 4 /**< definicja preprocesora szerokosci okna statusu */   

#define MENUDESC_WIN_HEIGHT 3 /**< definicja preprocesora wysokosci okna opisu menu */   
#define MENUDESC_WIN_WIDTH COLS /**< definicja preprocesora szerokosci okna opisu menu */   

#define DISPLAY_WIN_HEIGHT LINES - MENU_WIN_HEIGHT - MENUDESC_WIN_HEIGHT /**< definicja preprocesora wysokosci menu wyswietlania */   
#define DISPLAY_WIN_WIDTH COLS /**< definicja preprocesora szerokosci menu wyswietlania */   


// POLOZENIE NAZWY OKIEN W KONSOLI
#define WINDOW_NAMES_Y 0 /**< definicja preprocesora odstepu od ramki okna (wysokosc) */   
#define WINDOW_NAMES_X 2 /**< definicja preprocesora odstepu od ramki okna (szerokosc) */   

/**
 * \brief klasa AppView
 *
 * Klasa AppView jest odpowiedzialna za graficzną interakcję pomiędzy użytkownikiem a aplikacją. Jest to jedyna klasa,
 * ktora pozwala na obsłużenie interakcji z użytkownikiem oraz rysowanie konkretnych okien, menu czy tez
 * danych w konsoli. Klasa ta jest sprawnie połączona z AppController. Znajdują sie tu metody, ktore przyjmuja
 * konkretne dane, najczęściej w postaci std::string, co jest ważnym elementem tej klasy - aby wypisać dane na ekranie,
 * pobierane są one w argumentach jako tekst.
 *
 * Korzystanie z biblioteki curses.h tylko w tej klasie, pozwala zapobiec błędom z nieświadomą interakcją z użytkownikiem
 * w innych klasach do tego nieprzeznaczonych. Gdy raz zaincjalizujemy bibliotekę i stworzymy główne okno aplikacji
 * z pomocą curses, to standardowy strumień c++ nie będzie działać w zadnej klasie aplikacji. Jedynym wyjątkiem jest
 * wykorzystanie tego strumienia na innym wątku/procesie.
 *
 * \version alpha 0.1
 */
class AppView {
public:
	struct Window {
		std::string name; /** nazwa okna */
		WINDOW* handle; /** uchwyt do okna z biblioteki pdcurses */
	} 
	wMain /** Główne okno aplikacji. */  
	, wMenu /** Okno przeznaczone dla menu. */  
	, wDisplay /** Okno dla wyświetliwanych danych. */  
	, wInput /** Okno przeznaczone do wpisywania danych przez użytkownika. */  
	, wStatus /** Okno przeznaczone do wyświetlania statusu aplikacji */  
	, wMenuDesc /** Okno przeznaczone do wypisywania opisów menu w celu łatwiejszego poruszania się po aplikacji. */;

	void drawMenu(const std::string title, const std::vector<std::string>& fields);
	int selectMenuOption(const std::string title, const std::vector<std::string>& fields, const std::vector<std::string>& desc);
	
	void drawTable(const std::vector<std::string>& fields);
	void drawTable(const std::vector <std::pair<int, std::string>>& fields);
	int selectTableOption(const std::vector<std::string>& fields);
	int selectTableOption(const std::vector<std::pair<int, std::string>>& fields);

	void printLnMenuDesc(std::string str);
	void printLnStatus(std::string str);

	void clearStatus();
	void clearTable();
	void clearInput();

	void redrawWindow(const Window& win);
	void redrawWindows();

	int handleInput(std::string *input);
	std::vector<std::string> drawInputBox(std::vector<std::pair<std::string, std::string>> labels, int *key);

public:
	void init();
};