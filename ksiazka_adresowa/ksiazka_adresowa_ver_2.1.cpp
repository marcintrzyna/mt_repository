#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <conio.h>
#include <sstream>
#include <time.h>
#include <stdio.h>

using namespace std;

struct Uzytkownik
{
    int id_uzytkownika;
    string nazwa, haslo;

    Uzytkownik(int id_uzytkownika, string nazwa, string haslo);
};

Uzytkownik::Uzytkownik(int xid_uzytkownika, string xnazwa, string xhaslo)
    : id_uzytkownika(xid_uzytkownika)
    , nazwa(xnazwa)
    , haslo(xhaslo)
{
}

struct Rekord
{
    int id_adresata, id_uzytkownika;
    string imie, nazwisko, telefon, email, adres;

    Rekord(int id_adresata, int id_uzytkownika, string imie, string nazwisko, string telefon, string email, string adres);
};

Rekord::Rekord(int xid_adresata, int xid_uzytkownika, string ximie, string xnazwisko, string xtelefon, string xemail, string xadres)
    : id_adresata (xid_adresata)
    , id_uzytkownika (xid_uzytkownika)
    , imie(ximie)
    , nazwisko(xnazwisko)
    , telefon (xtelefon)
    , email (xemail)
    , adres (xadres)
{
}

string konwersjaIntNaString(int liczba)
{
    ostringstream ss;
    ss << liczba;
    string str = ss.str();
    return str;
}

string pobieranie_aktualnego_czasu()
{
    char bufor[ 64 ];
    time_t czas;
    time( & czas );
    tm czasTM = * localtime( & czas );

    setlocale( LC_ALL, "Polish" );
    strftime( bufor, sizeof( bufor ), "%#c", & czasTM );
    string aktualny_czas = bufor;

    return aktualny_czas;
}

void historia_zmian(string komunikat)
{
    string kolejny_log = pobieranie_aktualnego_czasu() + " " + komunikat;

    fstream plik;
    plik.open("historia_zmian.txt",ios::out | ios::app);
    plik<<kolejny_log<<endl;
    plik.close();
}

int rekord_poprawnie_zmodyfikowany(int id_do_modyfikacji)
{
    int znaleziono_rekord = 1;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout<<endl;
    cout<<"Rekord zostal zmodyfikowany poprawnie."<<endl;
    string komunikat = "Zmodyfikowano adresata o numerze id: " + konwersjaIntNaString(id_do_modyfikacji);
    historia_zmian(komunikat);

    return znaleziono_rekord;
}

void brak_adresata()
{
    cout<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout<<"Nie znaleziono w ksiazce adresowej."<<endl;
}

void brak_uprawnien()
{
    cout<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout<<"Brak uprawnien do edycji."<<endl;
}

void brak_rekordu()
{
    cout<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout<<"Ksiazka adresowa jest pusta."<<endl;
}

void brak_uzytkownika()
{
    cout<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout<<"Nie zarejetrowano zadnego uzytkownika."<<endl;
}

void ksiazka_adresowa(vector <Rekord>& dane, int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cout<<"ID: ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout<<dane[i].id_adresata<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout<<"Imie: ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout<<dane[i].imie<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout<<"Nazwisko: ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout<<dane[i].nazwisko<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout<<"Telefon: ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout<<dane[i].telefon<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout<<"e-mail: ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout<<dane[i].email<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout<<"Adres: ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout<<dane[i].adres<<endl;
}

char menu_edycji()
{
    char wybor;

    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout<<endl;
    cout<<"-------------------"<<endl;
    cout<<"MENU EDYCJI DANYCH:"<<endl;
    cout<<"-------------------"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout<<"1.Edycja imienia"<<endl;
    cout<<"2.Edycja nazwiska"<<endl;
    cout<<"3.Edycja numeru telefonu"<<endl;
    cout<<"4.Edycja email"<<endl;
    cout<<"5.Edycja adresu"<<endl;
    cout<<"6.Powrot do menu glownego"<<endl;
    cout<<endl;
    cout<<"Twoj wybor: ";
    cin>>wybor;

    return wybor;
}

void menu_ksiazka_adresowa()
{
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout<<endl;
    cout<<"-----------------"<<endl;
    cout<<"KSIAZKA ADRESOWA:"<<endl;
    cout<<"-----------------"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}

string buforowanie_ksiazka_adresowa()
{
    string bufor, linia;
    fstream plik_ksiazka_adresowa;
    plik_ksiazka_adresowa.open("ksiazka_adresowa.txt", ios::out | ios::in);

    while(!plik_ksiazka_adresowa.eof())
    {
        getline(plik_ksiazka_adresowa,linia);
        bufor = bufor + linia;
    }
    plik_ksiazka_adresowa.close();

    return bufor;
}

void nowe_zapisywanie_zmian_do_pliku(vector <Rekord>& dane, int id_do_modyfikacji, int i)
{
    int id_adresata, id_uzytkownika;
    string imie, nazwisko, telefon, email, adres;
    string bufor;

    fstream plik_ksiazka_adresowa_tym;
    plik_ksiazka_adresowa_tym.open("ksiazka_adresowa_tym.txt",ios::out | ios::app);

    bufor = buforowanie_ksiazka_adresowa();

    for (int j=0; j<bufor.size(); j++)
    {
        size_t pozycja = bufor.find("|");
        string element = bufor.substr(0,pozycja);
        int dlugosc = element.length();
        id_adresata = atof(element.c_str());
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        id_uzytkownika = atof(element.c_str());
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        imie = element;
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        nazwisko = element;
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        telefon = element;
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        email = element;
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        adres = element;
        bufor = bufor.erase(0,dlugosc+1);

        if (id_adresata == id_do_modyfikacji)
            plik_ksiazka_adresowa_tym<<dane[i].id_adresata<<"|"<<dane[i].id_uzytkownika<<"|"<<dane[i].imie<<"|"<<dane[i].nazwisko<<"|"<<dane[i].telefon<<"|"<<dane[i].email<<"|"<<dane[i].adres<<"|"<<endl;
        else
            plik_ksiazka_adresowa_tym<<id_adresata<<"|"<<id_uzytkownika<<"|"<<imie<<"|"<<nazwisko<<"|"<<telefon<<"|"<<email<<"|"<<adres<<"|"<<endl;
    }
    plik_ksiazka_adresowa_tym.close();
    remove( "ksiazka_adresowa.txt" );
    rename( "ksiazka_adresowa_tym.txt", "ksiazka_adresowa.txt" );
}

void edycja_danych(vector <Rekord>& dane, int ostatniRekord, int idZalogowanegoUzytkownika)
{
    string modyfikacja;
    int id_do_modyfikacji;
    int znaleziono_rekord = 0;
    char wybor;

    if (ostatniRekord == 0)
        brak_rekordu();
    else
    {
        cout<<"Podaj id adresta, ktore chcesz modyfikowac: ";
        cin>>id_do_modyfikacji;

        for (int i=0; i<dane.size(); i++)
        {
            if (id_do_modyfikacji == dane[i].id_adresata)
            {
                if (idZalogowanegoUzytkownika == dane[i].id_uzytkownika)
                {
                    wybor = menu_edycji();
                    if (wybor != '6')
                    {
                        menu_ksiazka_adresowa();
                        ksiazka_adresowa(dane, i);
                        cout<<endl;
                    }

                    while (znaleziono_rekord != 1)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                        switch (wybor)
                        {
                        case '1':
                        {
                            cout<<"Podaj nowe imie: ";
                            cin>>modyfikacja;
                            dane[i].imie = modyfikacja;
                            nowe_zapisywanie_zmian_do_pliku(dane,id_do_modyfikacji,i);
                            znaleziono_rekord = rekord_poprawnie_zmodyfikowany(id_do_modyfikacji);
                            break;
                        }
                        case '2':
                        {
                            cout<<"Podaj nowe nazwisko: ";
                            cin>>modyfikacja;
                            dane[i].nazwisko = modyfikacja;
                            nowe_zapisywanie_zmian_do_pliku(dane,id_do_modyfikacji,i);
                            znaleziono_rekord = rekord_poprawnie_zmodyfikowany(id_do_modyfikacji);
                            break;
                        }
                        case '3':
                        {
                            cout<<"Podaj nowy numer telefonu: ";
                            cin>>modyfikacja;
                            dane[i].telefon = modyfikacja;
                            nowe_zapisywanie_zmian_do_pliku(dane,id_do_modyfikacji,i);
                            znaleziono_rekord = rekord_poprawnie_zmodyfikowany(id_do_modyfikacji);
                            break;
                        }
                        case '4':
                        {
                            cout<<"Podaj nowy adres emial: ";
                            cin>>modyfikacja;
                            dane[i].email = modyfikacja;
                            nowe_zapisywanie_zmian_do_pliku(dane,id_do_modyfikacji,i);
                            znaleziono_rekord = rekord_poprawnie_zmodyfikowany(id_do_modyfikacji);
                            break;
                        }
                        case '5':
                        {
                            cout<<"Podaj nowy adres: ";
                            cin.sync();
                            getline(cin,modyfikacja);
                            cin.sync();
                            dane[i].adres = modyfikacja;
                            nowe_zapisywanie_zmian_do_pliku(dane,id_do_modyfikacji,i);
                            znaleziono_rekord = rekord_poprawnie_zmodyfikowany(id_do_modyfikacji);
                            break;
                        }
                        case '6':
                        {
                            znaleziono_rekord = 1;
                            break;
                        }
                        }
                    };
                }
                else
                {
                    brak_uprawnien();
                    znaleziono_rekord = 1;
                }
            }
        }
        if (znaleziono_rekord == 0)
            brak_adresata();
    }
    Sleep(1000);
}

void usuwanie_z_pliku(vector <Rekord>& dane, int id_do_usuniecia, int i)
{
    int id_adresata, id_uzytkownika;
    string imie, nazwisko, telefon, email, adres;
    string bufor;

    fstream plik_ksiazka_adresowa_tym;

    plik_ksiazka_adresowa_tym.open("ksiazka_adresowa_tym.txt",ios::out | ios::app);

    bufor = buforowanie_ksiazka_adresowa();

    for (int j=0; j<bufor.size(); j++)
    {
        size_t pozycja = bufor.find("|");
        string element = bufor.substr(0,pozycja);
        int dlugosc = element.length();
        id_adresata = atof(element.c_str());
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        id_uzytkownika = atof(element.c_str());
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        imie = element;
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        nazwisko = element;
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        telefon = element;
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        email = element;
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        adres = element;
        bufor = bufor.erase(0,dlugosc+1);

        if (id_adresata == id_do_usuniecia)
        {}
        else
            plik_ksiazka_adresowa_tym<<id_adresata<<"|"<<id_uzytkownika<<"|"<<imie<<"|"<<nazwisko<<"|"<<telefon<<"|"<<email<<"|"<<adres<<"|"<<endl;
    }
    plik_ksiazka_adresowa_tym.close();
    remove( "ksiazka_adresowa.txt" );
    rename( "ksiazka_adresowa_tym.txt", "ksiazka_adresowa.txt" );
}

int sprawdzenie_ilosci_danych(int ostatniRekord)
{
    int id_adresata, id_uzytkownika;
    string imie, nazwisko, telefon, email, adres;
    string bufor;

    bufor = buforowanie_ksiazka_adresowa();

    for (int i=0; i<bufor.size(); i++)
    {
        size_t pozycja = bufor.find("|");
        string element = bufor.substr(0,pozycja);
        int dlugosc = element.length();
        id_adresata = atof(element.c_str());
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        id_uzytkownika = atof(element.c_str());
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        imie = element;
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        nazwisko = element;
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        telefon = element;
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        email = element;
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        adres = element;
        bufor = bufor.erase(0,dlugosc+1);

        ostatniRekord = id_adresata;
    }

    return ostatniRekord;
}

int usuwanie_adresata(vector <Rekord>& dane, int ostatniRekord, int idZalogowanegoUzytkownika)
{
    int id_do_usuniecia;
    int znaleziono_rekord = 0;
    char potwierdz;

    if (ostatniRekord == 0)
        brak_rekordu();
    else
    {
        cout<<"Podaj id adresta, ktore chcesz usunac: ";
        cin>>id_do_usuniecia;

        for (int i=0; i<dane.size(); i++)
        {
            if (id_do_usuniecia == dane[i].id_adresata)
            {
                if (idZalogowanegoUzytkownika == dane[i].id_uzytkownika)
                {
                    cout<<endl;
                    ksiazka_adresowa(dane, i);
                    cout<<endl;

                    while (znaleziono_rekord != 1)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                        cout<<"Czy potwierdzasz usuniecie powyzszych danych <t/n> ?: "<<endl;
                        potwierdz = getch();

                        switch (potwierdz)
                        {
                        case 't':
                        {
                            dane.erase(dane.begin() + i);
                            usuwanie_z_pliku(dane,id_do_usuniecia,i);
                            ostatniRekord = sprawdzenie_ilosci_danych(ostatniRekord);
                            znaleziono_rekord = 1;

                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                            cout<<endl;
                            cout<<"Rekord zostal usuniety poprawnie."<<endl;
                            string komunikat = "Usunieto adresata o numerze id: " + konwersjaIntNaString(id_do_usuniecia);
                            historia_zmian(komunikat);
                        }
                        case 'n':
                            znaleziono_rekord = 1;
                        }
                    };
                }
                else
                {
                    brak_uprawnien();
                    znaleziono_rekord = 1;
                }
            }
        }
        if (znaleziono_rekord == 0)
            brak_adresata();
    }
    Sleep(1000);

    return ostatniRekord;
}

void wyswietlanie_wszystkich_danych(vector <Rekord>& dane, int ostatniRekord, int idZalogowanegoUzytkownika)
{
    int znaleziono_rekord = 0;

    if (ostatniRekord == 0)
        brak_rekordu();
    else
    {
        for (int i=0; i<dane.size(); i++)
        {
            if (idZalogowanegoUzytkownika == dane[i].id_uzytkownika)
            {
                ksiazka_adresowa(dane, i);
                znaleziono_rekord = 1;
            }
        }
        if (znaleziono_rekord == 0)
            brak_rekordu();
    }

    Sleep(1000);
}

void wyszukaj_Nazwisko(vector <Rekord>& dane, int ostatniRekord, int idZalogowanegoUzytkownika)
{
    string wyszukaj;
    int znaleziono_rekord = 0;

    if (ostatniRekord == 0)
        brak_rekordu();
    else
    {
        cout<<"Podaj nazwisko, ktore chcesz odnalezc: ";
        cin>>wyszukaj;
        for (int i=0; i<dane.size(); i++)
        {
            if (wyszukaj == dane[i].nazwisko)
            {
                if (idZalogowanegoUzytkownika == dane[i].id_uzytkownika)
                {
                    ksiazka_adresowa(dane, i);
                    znaleziono_rekord = 1;
                }
                else
                {
                    brak_uprawnien();
                    znaleziono_rekord = 1;
                }
            }
        }
        if (znaleziono_rekord == 0)
            brak_adresata();
    }
    Sleep(1000);
}

void wyszukaj_Imie(vector <Rekord>& dane, int ostatniRekord, int idZalogowanegoUzytkownika)
{
    string wyszukaj;
    int znaleziono_rekord = 0;

    if (ostatniRekord == 0)
        brak_rekordu();
    else
    {
        cout<<"Podaj imie, ktore chcesz odnalezc: ";
        cin>>wyszukaj;
        for (int i=0; i<dane.size(); i++)
        {
            if (wyszukaj == dane[i].imie)
            {
                if (idZalogowanegoUzytkownika == dane[i].id_uzytkownika)
                {
                    ksiazka_adresowa(dane, i);
                    znaleziono_rekord = 1;
                }
                else
                {
                    brak_uprawnien();
                    znaleziono_rekord = 1;
                }
            }
        }
        if (znaleziono_rekord == 0)
            brak_adresata();
    }
    Sleep(1000);
}

int dodawanie_adresata(vector <Rekord>& dane, int ostatniRekord, int idZalogowanegoUzytkownika)
{
    string imie, nazwisko, telefon, email, adres;

    cout<<"Podaj imie: ";
    cin>>imie;
    cout<<"Podaj nazwisko: ";
    cin>>nazwisko;
    cout<<"Podaj nr telefonu: ";
    cin>>telefon;
    cout<<"Podaj adres e-mail: ";
    cin>>email;
    cout<<"Podaj adres zamieszkania: ";
    cin.sync();
    getline(cin,adres);
    cin.sync();

    dane.push_back(Rekord(ostatniRekord+1, idZalogowanegoUzytkownika, imie, nazwisko, telefon, email, adres));

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout<<endl;
    cout<<"Rekord zalozony poprawnie."<<endl;
    string komunikat = "Dodano adresata o numerze id: " + konwersjaIntNaString(ostatniRekord+1);
    historia_zmian(komunikat);
    Sleep(1000);

    fstream plik;
    plik.open("ksiazka_adresowa.txt",ios::out | ios::app);
    plik<<ostatniRekord+1<<"|"<<idZalogowanegoUzytkownika<<"|"<<imie<<"|"<<nazwisko<<"|"<<telefon<<"|"<<email<<"|"<<adres<<"|"<<endl;
    plik.close();

    return ostatniRekord+1;
}


void wczytywanie_danych_z_pliku(vector <Rekord>& dane, int idZalogowanegoUzytkownika)
{
    int id_adresata, id_uzytkownika, IloscRekordow = 0;
    string imie, nazwisko, telefon, email, adres;
    string bufor;

    bufor = buforowanie_ksiazka_adresowa();

    for (int i=0; i<bufor.size(); i++)
    {
        size_t pozycja = bufor.find("|");
        string element = bufor.substr(0,pozycja);
        int dlugosc = element.length();
        id_adresata = atof(element.c_str());
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        id_uzytkownika = atof(element.c_str());
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        imie = element;
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        nazwisko = element;
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        telefon = element;
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        email = element;
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        adres = element;
        bufor = bufor.erase(0,dlugosc+1);

        if (id_uzytkownika == idZalogowanegoUzytkownika)
        {
            dane.push_back(Rekord(id_adresata, id_uzytkownika, imie, nazwisko, telefon, email, adres));
            IloscRekordow++;
        }
    }

    if (IloscRekordow == 1)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        cout<<endl;
        cout<<"Poprawnie zaimportowano: "<<konwersjaIntNaString(IloscRekordow)<<" adresata"<<endl;
        string komunikat = "Poprawnie zaimportowano: " + konwersjaIntNaString(IloscRekordow) + " adresata";
        historia_zmian(komunikat);
        Sleep(1000);
    }
    if (IloscRekordow > 1)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        cout<<endl;
        cout<<"Poprawnie zaimportowano: "<<konwersjaIntNaString(IloscRekordow)<<" adresatow"<<endl;
        string komunikat = "Poprawnie zaimportowano: " + konwersjaIntNaString(IloscRekordow) + " adresatow";
        historia_zmian(komunikat);
        Sleep(1000);
    }
}

int wczytywanie_Uzytkownikow_z_pliku(vector <Uzytkownik>& uzytkownicy, int IloscUzytkownikow)
{
    int id_uzytkownika;
    string nazwa, haslo;
    string bufor;
    string linia;

    fstream plik_uzytkownicy;
    plik_uzytkownicy.open("uzytkownicy.txt", ios::out | ios::in);
    while(!plik_uzytkownicy.eof())
    {
        getline(plik_uzytkownicy,linia);
        bufor = bufor + linia;
    }
    plik_uzytkownicy.close();

    for (int i=0; i<bufor.size(); i++)
    {
        size_t pozycja = bufor.find("|");
        string element = bufor.substr(0,pozycja);
        int dlugosc = element.length();
        id_uzytkownika = atof(element.c_str());
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        nazwa = element;
        bufor = bufor.erase(0,dlugosc+1);

        pozycja = bufor.find("|");
        element = bufor.substr(0,pozycja);
        dlugosc = element.length();
        haslo = element;
        bufor = bufor.erase(0,dlugosc+1);

        uzytkownicy.push_back(Uzytkownik(id_uzytkownika, nazwa, haslo));
        IloscUzytkownikow++;
    }

    if (uzytkownicy.empty() == true)
        IloscUzytkownikow = 0;
    else
    {
        if (IloscUzytkownikow == 1)
        {
            cout<<"Poprawnie zaimportowano: "<<konwersjaIntNaString(IloscUzytkownikow)<<" uzytkownika"<<endl;
            string komunikat = "Poprawnie zaimportowano: " + konwersjaIntNaString(IloscUzytkownikow) + " uzytkownika";
            historia_zmian(komunikat);
            Sleep(1000);
        }
        else
        {
            cout<<"Poprawnie zaimportowano: "<<konwersjaIntNaString(IloscUzytkownikow)<<" uzytkownikow"<<endl;
            string komunikat = "Poprawnie zaimportowano: " + konwersjaIntNaString(IloscUzytkownikow) + " uzytkownikow";
            historia_zmian(komunikat);
            Sleep(1000);
        }
    }

    return IloscUzytkownikow;
}

void zmianaHasla(vector <Uzytkownik>& uzytkownicy, int IloscUzytkownikow, int idZalogowanegoUzytkownika)
{
    string haslo;
    cout<<"Podaj nowe haslo: ";
    cin>>haslo;

    for (int i=0; i<idZalogowanegoUzytkownika; i++)
    {
        if (uzytkownicy[i].id_uzytkownika == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo = haslo;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout<<endl;
            cout<<"Haslo poprawnie zmienione."<<endl;
            Sleep(1000);

            remove( "uzytkownicy.txt" );
            fstream plik;
            plik.open("uzytkownicy.txt",ios::out | ios::app);

            for (int i=0; i<uzytkownicy.size(); i++)
            {
                plik<<uzytkownicy[i].id_uzytkownika<<"|"<<uzytkownicy[i].nazwa<<"|"<<uzytkownicy[i].haslo<<"|"<<endl;
            }
            plik.close();

            string komunikat = "Haslo uzytkowania: " + uzytkownicy[i].nazwa + " zostalo zmienione.";
            historia_zmian(komunikat);
        }
    }
}

int logowanie(vector <Uzytkownik>& uzytkownicy, int IloscUzytkownikow)
{
    string nazwa, haslo, komunikat;
    if (IloscUzytkownikow == 0)
    {
        brak_uzytkownika();
        Sleep(1000);
    }
    else
    {
        cout<<"Podaj nazwe uzytkownika: ";
        cin>>nazwa;

        int i = 0;
        while (i < IloscUzytkownikow)
        {
            if (uzytkownicy[i].nazwa == nazwa)
            {
                for (int j=0; j<3; j++)
                {
                    cout<<"Podaj haslo: ";
                    cin>>haslo;
                    if (uzytkownicy[i].haslo == haslo)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        cout<<endl;
                        cout<<"Zalogowales sie poprawnie."<<endl;
                        komunikat = "Zalogowano poprawnie uzytkownika: " + uzytkownicy[i].nazwa;
                        historia_zmian(komunikat);
                        Sleep(1000);

                        return uzytkownicy[i].id_uzytkownika;
                    }
                    else
                    {
                        cout<<"Bledne haslo. Sprobuj ponownie."<<endl;
                        komunikat = "Bledne haslo podczas logowania uzytkowania: " + uzytkownicy[i].nazwa + ". Proba logowania: " + konwersjaIntNaString(j+1);
                        historia_zmian(komunikat);
                        Sleep(1000);
                    }
                }
                cout<<endl;
                cout<<"Podales 3x bledne haslo. Nastapi powrot do MENU LOGOWANIA."<<endl;
                komunikat = "Podano 3x bledne haslo podczas logowania. Automatycznie powrocono do MENU LOGOWANIA";
                historia_zmian(komunikat);
                Sleep(1500);
                return 0;
            }
            i++;
        }
        cout<<endl;
        cout<<"Nie znaleziono uzytkownika: "<<nazwa<<endl;
        komunikat = "Nie znaleziono uzytkownika: " + nazwa;
        historia_zmian(komunikat);
        Sleep(2000);
    }
    return 0;
}

int rejestracja(vector <Uzytkownik>& uzytkownicy, int IloscUzytkownikow)
{
    string nazwa, haslo, komunikat;
    cout<<"Podaj nazwe uzytkownika: ";
    cin>>nazwa;

    int i = 0;
    while (i < IloscUzytkownikow)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            cout<<"Podana nazwa juz istnieje. Wybierz inna nazwe: ";
            cin>>nazwa;
            komunikat = "Podano istniejaca nazwe uzytkownika: " + nazwa;
            historia_zmian(komunikat);
            i=0;
        }
        else
            i++;
    }
    cout<<"Podaj haslo: ";
    cin>>haslo;
    uzytkownicy.push_back(Uzytkownik(IloscUzytkownikow + 1, nazwa, haslo));

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout<<endl;
    cout<<"Konto zalozone poprawnie."<<endl;
    komunikat = "Zarejestrowano uzytkownika: " + nazwa + " o numerze id: " + konwersjaIntNaString(IloscUzytkownikow+1);
    historia_zmian(komunikat);
    Sleep(1000);

    fstream plik;
    plik.open("uzytkownicy.txt",ios::out | ios::app);
    plik<<uzytkownicy[IloscUzytkownikow].id_uzytkownika<<"|"<<uzytkownicy[IloscUzytkownikow].nazwa<<"|"<<uzytkownicy[IloscUzytkownikow].haslo<<"|"<<endl;
    plik.close();

    return IloscUzytkownikow + 1;
}

int main()
{
    vector <Rekord> dane;
    vector <Uzytkownik> uzytkownicy;
    string komunikat;
    int idZalogowanegoUzytkownika = 0;
    int ostatniRekord = 0;
    int IloscUzytkownikow = 0;
    char wybor;

    komunikat = "Uruchomiono program";
    historia_zmian(komunikat);

    fstream plik_historia_zmian;
    plik_historia_zmian.open("historia_zmian.txt");
    if(plik_historia_zmian.good() == false)
    {
        ofstream utworz_historia_zmian;
        utworz_historia_zmian.open ("historia_zmian.txt");
        utworz_historia_zmian.close();
    }
    plik_historia_zmian.close();

    fstream plik_uzytkownicy;
    plik_uzytkownicy.open("uzytkownicy.txt");
    if(plik_uzytkownicy.good() == false)
    {
        ofstream utworz_uzytkownicy;
        utworz_uzytkownicy.open ("uzytkownicy.txt");
        utworz_uzytkownicy.close();
        komunikat = "Utworzono plik: uzytkownicy.txt";
        historia_zmian(komunikat);
    }
    plik_uzytkownicy.close();

    fstream plik_ksiazka_adresowa;
    plik_ksiazka_adresowa.open("ksiazka_adresowa.txt");
    if(plik_ksiazka_adresowa.good() == false)
    {
        ofstream utworz_ksiazka_adresowa;
        utworz_ksiazka_adresowa.open ("ksiazka_adresowa.txt");
        utworz_ksiazka_adresowa.close();
        komunikat = "Utworzono plik: ksiazka_adresowa.txt";
        historia_zmian(komunikat);
    }
    plik_ksiazka_adresowa.close();

    IloscUzytkownikow = wczytywanie_Uzytkownikow_z_pliku(uzytkownicy,IloscUzytkownikow);
    ostatniRekord = sprawdzenie_ilosci_danych(ostatniRekord);

    while (true)
    {
        if (idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
            cout<<endl;
            cout<<"----------------"<<endl;
            cout<<"KSIAZKA ADRESOWA"<<endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            cout<<"   LOGOWANIE"<<endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
            cout<<"-----------------"<<endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            cout<<"1.Logowanie"<<endl;
            cout<<"2.Rejestracja"<<endl;
            cout<<"3.Zakoncz program"<<endl;
            cout<<endl;
            cout<<"Twoj wybor: ";
            cin>>wybor;

            if (wybor == '1')
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY);
                idZalogowanegoUzytkownika = logowanie(uzytkownicy,IloscUzytkownikow);
                wczytywanie_danych_z_pliku(dane, idZalogowanegoUzytkownika);
            }
            else if (wybor == '2')
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY);
                IloscUzytkownikow = rejestracja(uzytkownicy,IloscUzytkownikow);
            }
            else if (wybor == '3')
            {
                komunikat = "Zamknieto program";
                historia_zmian(komunikat);
                exit(0);
            }
        }
        if (idZalogowanegoUzytkownika != 0)
        {
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
            cout<<endl;
            cout<<"-----------------"<<endl;
            cout<<"KSIAZKA ADRESOWA:"<<endl;
            cout<<"-----------------"<<endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            cout<<"1.Dodaj adresata"<<endl;
            cout<<"2.Wyszukaj po imieniu"<<endl;
            cout<<"3.Wyszukaj po nazwisku"<<endl;
            cout<<"4.Wyswietl wszystkich adresatow"<<endl;
            cout<<"5.Usun adresata"<<endl;
            cout<<"6.Edytuj adresata"<<endl;
            cout<<"7.Zmien haslo"<<endl;
            cout<<"9.Wyloguj sie"<<endl;
            cout<<endl;
            cout<<"Twoj wybor: ";
            cin>>wybor;

            if (wybor == '1')
            {
                menu_ksiazka_adresowa();
                ostatniRekord = dodawanie_adresata(dane,ostatniRekord,idZalogowanegoUzytkownika);
            }
            else if (wybor == '2')
            {
                menu_ksiazka_adresowa();
                wyszukaj_Imie(dane, ostatniRekord, idZalogowanegoUzytkownika);
            }
            else if (wybor == '3')
            {
                menu_ksiazka_adresowa();
                wyszukaj_Nazwisko(dane, ostatniRekord, idZalogowanegoUzytkownika);
            }
            else if (wybor == '4')
            {
                menu_ksiazka_adresowa();
                wyswietlanie_wszystkich_danych(dane, ostatniRekord, idZalogowanegoUzytkownika);
            }
            else if (wybor == '5')
            {
                menu_ksiazka_adresowa();
                ostatniRekord = usuwanie_adresata(dane, ostatniRekord, idZalogowanegoUzytkownika);
            }
            else if (wybor == '6')
            {
                menu_ksiazka_adresowa();
                edycja_danych(dane, ostatniRekord, idZalogowanegoUzytkownika);
            }
            else if (wybor == '7')
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY);
                zmianaHasla(uzytkownicy, IloscUzytkownikow, idZalogowanegoUzytkownika);
            }
            else if (wybor == '9')
            {
                komunikat = "Poprawnie wylogowano uzytkownika: " + uzytkownicy[idZalogowanegoUzytkownika-1].nazwa;
                historia_zmian(komunikat);
                dane.clear();
                idZalogowanegoUzytkownika = 0;
            }
        }
    }
    return 0;
}
