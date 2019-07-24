#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <conio.h>
#include <sstream>
#include <time.h>

using namespace std;

struct Rekord
{
    int id;
    string imie, nazwisko, telefon, email, adres;

    Rekord(int id, string imie, string nazwisko, string telefon, string email, string adres);
};

Rekord::Rekord( int xid, string ximie, string xnazwisko, string xtelefon, string xemail, string xadres)
    : id (xid)
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
    cout<<"Brak adresata w bazie danych."<<endl;
}

void brak_rekordu()
{
    cout<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout<<"Brak rekordow w bazie danych"<<endl;
}

void ksiazka_adresowa(vector <Rekord>& dane, int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cout<<"ID: ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout<<dane[i].id<<endl;
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

void zapisywanie_zmian_do_pliku(vector <Rekord>& dane)
{
    remove( "ksiazka_adresowa.txt" );
    fstream plik;
    plik.open("ksiazka_adresowa.txt",ios::out | ios::app);

    for (int i=0; i<dane.size(); i++)
    {
        plik<<dane[i].id<<"|"<<dane[i].imie<<"|"<<dane[i].nazwisko<<"|"<<dane[i].telefon<<"|"<<dane[i].email<<"|"<<dane[i].adres<<"|"<<endl;
    }
    plik.close();
}

void edycja_danych(vector <Rekord>& dane, int IloscRekordow)
{
    string modyfikacja;
    int id_do_modyfikacji;
    int znaleziono_rekord = 0;
    char wybor;

    if (IloscRekordow == 0)
    {
        brak_rekordu();
    }

    else
    {
        cout<<"Podaj id adresta, ktore chcesz modyfikowac: ";
        cin>>id_do_modyfikacji;

        for (int i=0; i<dane.size(); i++)
        {
            if (id_do_modyfikacji == dane[i].id)
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
                        zapisywanie_zmian_do_pliku(dane);
                        znaleziono_rekord = rekord_poprawnie_zmodyfikowany(id_do_modyfikacji);
                        break;
                    }
                    case '2':
                    {
                        cout<<"Podaj nowe nazwisko: ";
                        cin>>modyfikacja;
                        dane[i].nazwisko = modyfikacja;
                        zapisywanie_zmian_do_pliku(dane);
                        znaleziono_rekord = rekord_poprawnie_zmodyfikowany(id_do_modyfikacji);
                        break;
                    }
                    case '3':
                    {
                        cout<<"Podaj nowy numer telefonu: ";
                        cin>>modyfikacja;
                        dane[i].telefon = modyfikacja;
                        zapisywanie_zmian_do_pliku(dane);
                        znaleziono_rekord = rekord_poprawnie_zmodyfikowany(id_do_modyfikacji);
                        break;
                    }
                    case '4':
                    {
                        cout<<"Podaj nowy adres emial: ";
                        cin>>modyfikacja;
                        dane[i].email = modyfikacja;
                        zapisywanie_zmian_do_pliku(dane);
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
                        zapisywanie_zmian_do_pliku(dane);
                        znaleziono_rekord = rekord_poprawnie_zmodyfikowany(id_do_modyfikacji);
                        break;
                    }
                    case '6':
                    {
                        znaleziono_rekord = 1;
                        break;
                    }
                    }
                }
            }
        }
        if (znaleziono_rekord == 0)
            brak_adresata();
    }
    Sleep(1000);
}

int usuwanie_adresata(vector <Rekord>& dane, int IloscRekordow)
{
    int id_do_usuniecia;
    int ostatnie_id = 0;
    int znaleziono_rekord = 0;
    char potwierdz;

    if (IloscRekordow == 0)
    {
        brak_rekordu();
    }

    else
    {
        cout<<"Podaj id adresta, ktore chcesz usunac: ";
        cin>>id_do_usuniecia;

        for (int i=0; i<dane.size(); i++)
        {
            if (id_do_usuniecia == dane[i].id)
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
                        remove( "ksiazka_adresowa.txt" );
                        ofstream nowyPlik;
                        nowyPlik.open ("ksiazka_adresowa.txt");
                        nowyPlik.close();
                        fstream plik;
                        plik.open("ksiazka_adresowa.txt",ios::out | ios::app);

                        for (int i=0; i<dane.size(); i++)
                        {
                            plik<<dane[i].id<<"|"<<dane[i].imie<<"|"<<dane[i].nazwisko<<"|"<<dane[i].telefon<<"|"<<dane[i].email<<"|"<<dane[i].adres<<"|"<<endl;
                            ostatnie_id = dane[i].id;
                        }
                        plik.close();

                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        cout<<endl;
                        cout<<"Rekord zostal usuniety poprawnie."<<endl;
                        string komunikat = "Usunieto adresata o numerze id: " + konwersjaIntNaString(id_do_usuniecia);
                        historia_zmian(komunikat);

                        IloscRekordow--;
                        znaleziono_rekord = 1;
                    }
                    case 'n':
                        znaleziono_rekord = 1;
                    }
                };
            }
        }
        if (znaleziono_rekord == 0)
            brak_adresata();
    }
    Sleep(1000);

    return IloscRekordow;
}

void wyswietlanie_wszystkich_danych(vector <Rekord>& dane, int IloscRekordow)
{
    if (IloscRekordow == 0)
        brak_rekordu();

    for (int i=0; i<dane.size(); i++)
        ksiazka_adresowa(dane, i);

    Sleep(1000);
}

void wyszukaj_Nazwisko(vector <Rekord>& dane, int IloscRekordow)
{
    string wyszukaj;
    int znaleziono_rekord = 0;

    if (IloscRekordow == 0)
        brak_rekordu();
    else
    {
        cout<<"Podaj nazwisko, ktore chcesz odnalezc: ";
        cin>>wyszukaj;
        for (int i=0; i<dane.size(); i++)
        {
            if (wyszukaj == dane[i].nazwisko)
            {
                ksiazka_adresowa(dane, i);
                znaleziono_rekord = 1;
            }
        }
        if (znaleziono_rekord == 0)
            brak_adresata();
    }
    Sleep(1000);
}

void wyszukaj_Imie(vector <Rekord>& dane, int IloscRekordow)
{
    string wyszukaj;
    int znaleziono_rekord = 0;

    if (IloscRekordow == 0)
        brak_rekordu();
    else
    {
        cout<<"Podaj imie, ktore chcesz odnalezc: ";
        cin>>wyszukaj;
        for (int i=0; i<dane.size(); i++)
        {
            if (wyszukaj == dane[i].imie)
            {
                ksiazka_adresowa(dane, i);
                znaleziono_rekord = 1;
            }
        }
        if (znaleziono_rekord == 0)
            brak_adresata();
    }
    Sleep(1000);
}

int dodawanie_adresata(vector <Rekord>& dane, int IloscRekordow)
{
    string imie, nazwisko, telefon, email, adres;
    int ostatnie_id=0;

    for (int i=0; i<dane.size(); i++)
    {
        ostatnie_id = dane[i].id;
    }

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

    dane.push_back(Rekord(ostatnie_id+1, imie, nazwisko, telefon, email, adres));

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout<<endl;
    cout<<"Rekord zalozony poprawnie."<<endl;
    string komunikat = "Dodano adresata o numerze id: " + konwersjaIntNaString(ostatnie_id+1);
    historia_zmian(komunikat);
    Sleep(1000);

    fstream plik;
    plik.open("ksiazka_adresowa.txt",ios::out | ios::app);
    plik<<dane[IloscRekordow].id<<"|"<<dane[IloscRekordow].imie<<"|"<<dane[IloscRekordow].nazwisko<<"|"<<dane[IloscRekordow].telefon<<"|"<<dane[IloscRekordow].email<<"|"<<dane[IloscRekordow].adres<<"|"<<endl;
    plik.close();

    return IloscRekordow+1;
}

int wczytywanie_danych_z_pliku(vector <Rekord>& dane, int IloscRekordow)
{
    int id, ostatnie_id;
    string imie, nazwisko, telefon, email, adres;
    string bufor;
    string linia;

    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::out | ios::in);
    while(!plik.eof())
    {
        getline(plik,linia);
        bufor = bufor + linia;
    }
    plik.close();

    for (int i=0; i<bufor.size(); i++)
    {
        size_t pozycja = bufor.find("|");
        string element = bufor.substr(0,pozycja);
        int dlugosc = element.length();
        id = atof(element.c_str());
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

        dane.push_back(Rekord(id, imie, nazwisko, telefon, email, adres));
        IloscRekordow++;
    }

    if (dane.empty() == true)
        IloscRekordow = 0;
    else
    {
        cout<<"Dane zostaly wczytane poprawnie"<<endl;
        string komunikat = "Poprawnie zaimportowano adresatow: " + konwersjaIntNaString(IloscRekordow);
        historia_zmian(komunikat);
        Sleep(1000);
    }

    return IloscRekordow;
}

int main()
{
    vector <Rekord> dane;
    int IloscRekordow = 0;
    char wybor;
    fstream plik_historia_zmian;

    plik_historia_zmian.open("historia_zmian.txt");
    if(plik_historia_zmian.good() == false)
    {
        ofstream utworz_historia_zmian;
        utworz_historia_zmian.open ("historia_zmian.txt");
        utworz_historia_zmian.close();
    }
    plik_historia_zmian.close();

    string komunikat = "Uruchomiono program";
    historia_zmian(komunikat);

    fstream plik_ksiazka_adresowa;
    plik_ksiazka_adresowa.open("ksiazka_adresowa.txt");
    if(plik_ksiazka_adresowa.good() == false)
    {
        ofstream utworz_ksiazka_adresowa;
        utworz_ksiazka_adresowa.open ("ksiazka_adresowa.txt");
        utworz_ksiazka_adresowa.close();
        string komunikat = "Utworzono plik: ksiazka_adresowa.txt";
        historia_zmian(komunikat);
    }
    plik_ksiazka_adresowa.close();

    IloscRekordow = wczytywanie_danych_z_pliku(dane,IloscRekordow);

    while (true)
    {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
        cout<<endl;
        cout<<"-----------------"<<endl;
        cout<<"KSIAZKA ADRESOWA:"<<endl;
        cout<<"-----------------"<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        cout<<"1.Dodaj rekord"<<endl;
        cout<<"2.Wyszukaj po imieniu"<<endl;
        cout<<"3.Wyszukaj po nazwisku"<<endl;
        cout<<"4.Wyswietl wszystkich adresatow"<<endl;
        cout<<"5.Usun adresata"<<endl;
        cout<<"6.Edytuj adresata"<<endl;
        cout<<"9.Zakoncz program"<<endl;
        cout<<endl;
        cout<<"Twoj wybor: ";
        cin>>wybor;

        if (wybor == '1')
        {
            menu_ksiazka_adresowa();
            IloscRekordow = dodawanie_adresata(dane,IloscRekordow);
        }
        else if (wybor == '2')
        {
            menu_ksiazka_adresowa();
            wyszukaj_Imie(dane, IloscRekordow);
        }
        else if (wybor == '3')
        {
            menu_ksiazka_adresowa();
            wyszukaj_Nazwisko(dane, IloscRekordow);
        }
        else if (wybor == '4')
        {
            menu_ksiazka_adresowa();
            wyswietlanie_wszystkich_danych(dane, IloscRekordow);
        }
        else if (wybor == '5')
        {
            menu_ksiazka_adresowa();
            IloscRekordow = usuwanie_adresata(dane, IloscRekordow);
        }
        else if (wybor == '6')
        {
            menu_ksiazka_adresowa();
            edycja_danych(dane, IloscRekordow);
        }
        else if (wybor == '9')
            exit(0);
    }
    return 0;
}
