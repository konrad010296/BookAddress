#include <iostream>
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct DaneAdresata {
    string imie;
    string nazwisko;
    string nrTel;
    string adresEmail;
    string korespondecja;
    int numerIdAdresata;
    int idUzytkownika;
};

struct DaneUzytkownika {
    string login;
    string haslo;
    int numerIdUzytkownika;
};

string pobierzLinie() {
    string linia;
    cin.sync();
    getline(cin,linia);

    return linia;
}

int ostatniNrIdUzytkownika(vector <DaneUzytkownika> &zarejestrowniUzytkownicy) {
    vector <DaneUzytkownika> :: iterator it;
    int numerIdOstatniegoUzytkownika = 0;

    for(it = zarejestrowniUzytkownicy.begin() ; it != zarejestrowniUzytkownicy.end() ; ++it) {
        numerIdOstatniegoUzytkownika = (*it).numerIdUzytkownika;
    }
    return numerIdOstatniegoUzytkownika;
}

void zaladujPlikUzytkownicy(vector <DaneUzytkownika> &zarejestrowniUzytkownicy) {

    DaneUzytkownika uzytkownik;
    string zmiennaPomocnicza = "";
    string linia;
    int nr_linii = 1;
    fstream plikUzytkownicy;

    zarejestrowniUzytkownicy.clear();
    plikUzytkownicy.open("ListaUzytkownikow.txt", ios::in);
    if(plikUzytkownicy.good() == false) {
        cout << "Brak uzytkownikow w bazie !" << endl;
        Sleep(2000);
        system("CLS");
    }
    else {
        while(getline(plikUzytkownicy,linia)) {
            for (unsigned int i = 0 ; i < linia.length(); i++) {

                if (linia[i] != '|') {
                    zmiennaPomocnicza += linia[i];
                }

                else {
                    switch(nr_linii) {
                    case 1:
                        uzytkownik.numerIdUzytkownika = atoi(zmiennaPomocnicza.c_str());
                        break;
                    case 2:
                        uzytkownik.login = zmiennaPomocnicza;
                        break;
                    case 3:
                        uzytkownik.haslo = zmiennaPomocnicza;
                        break;
                    }
                    zmiennaPomocnicza = "";
                    nr_linii++;
                }
                if(nr_linii == 4) {
                    nr_linii = 1;
                }
            }
            zarejestrowniUzytkownicy.push_back(uzytkownik);
        }
    }
    plikUzytkownicy.close();
}


void dodajUzytkownikaDoPliku(vector <DaneUzytkownika> &zarejestrowniUzytkownicy)

{
    fstream plikUzytkownicy;
    vector <DaneUzytkownika> :: iterator it;

    remove("ListaUzytkownikow.txt");

    plikUzytkownicy.open("ListaUzytkownikow.txt", ios::out | ios::app);
    for(it = zarejestrowniUzytkownicy.begin() ; it != zarejestrowniUzytkownicy.end() ; ++it) {
        plikUzytkownicy << (*it).numerIdUzytkownika << "|" << (*it).login << "|" << (*it).haslo << "|" <<  endl;
    }
    zarejestrowniUzytkownicy.clear();
    plikUzytkownicy.close();
}

void rejestracja(vector <DaneUzytkownika> &zarejestrowniUzytkownicy) {

    DaneUzytkownika uzytkownik;
    string powotrzHaslo = "";
    int iloscProb = 3;
    int ostatniUzytkownik = ostatniNrIdUzytkownika(zarejestrowniUzytkownicy);
    system("CLS");

    cout << "Witaj w panelu rejestracyjnym !" << endl;
    cout << "Podaj swoj login: " << endl;
    uzytkownik.login = pobierzLinie();
    system("CLS");

    cout << "Podaj Haslo: " << endl;
    uzytkownik.haslo = pobierzLinie();
    system("CLS");

    while((uzytkownik.haslo != powotrzHaslo) || (iloscProb == 0)) {
        cout << "Powtorz haslo: " << endl;
        powotrzHaslo = pobierzLinie();
        system("CLS");

        if((uzytkownik.haslo != powotrzHaslo)) {
            iloscProb--;
            cout << "Hasla roznia sie ! Pozostaly ci " << iloscProb << " proby!" << endl;
            Sleep(2000);
            system("CLS");

        } else {
            cout << "Zostales poprawnie zarejestrowany !" << endl;
            uzytkownik.numerIdUzytkownika = ostatniUzytkownik + 1;
            zarejestrowniUzytkownicy.push_back(uzytkownik);
            dodajUzytkownikaDoPliku(zarejestrowniUzytkownicy);
            Sleep(2000);
            system("CLS");
        }
        if(iloscProb == 0) {
            cout << "Skonczyl sie twoj limit prob, sprobuj pozniej !" << endl;
            Sleep(2000);
            system("CLS");
            return;
        }
    }
}


int logowanie(vector <DaneUzytkownika> &zarejestrowniUzytkownicy) {

    vector <DaneUzytkownika> :: iterator it;
    string login = "";
    string haslo = "";
    int idZalogowanegoUzytkownika = 0;

    system("CLS");
    cout << "LOGOWANIE" << endl;

    cout << "Podaj login" << endl;
    cin >> login;
    cout << "Podaj haslo" << endl;
    cin >> haslo;

    for (it = zarejestrowniUzytkownicy.begin() ; it != zarejestrowniUzytkownicy.end() ; ++it) {
        if ((login == (*it).login) && (haslo == (*it).haslo)) {
            idZalogowanegoUzytkownika = (*it).numerIdUzytkownika;
        }
    }
    if(idZalogowanegoUzytkownika == 0) {
        system("CLS");
        cout << "Podales niepoprawny login lub haslo!" << endl;
        Sleep(2000);
        return 0;
    } else {
        system("CLS");
        cout << "Zostales poprawrawnie zalogowany !" << endl;
    }
    Sleep(2000);
    system("CLS");
    return idZalogowanegoUzytkownika;
}


int panelPowitalny(vector <DaneUzytkownika> &zarejestrowniUzytkownicy) {

    char wybor;
    int idZalogowanegoUzytkownika = 0;

    system("CLS");
    cout << "Witaj w ksiazce adresowej ! Wybierz ktora operacje chcesz wykonaæ ?" << endl;
    cout << "LOGOWANIE - 1" << endl;
    cout << "REJESTRACJA - 2" << endl;
    cout << "WYJSCIE - 3" << endl;

    wybor = getch();

    switch(wybor) {
    case '1':
        idZalogowanegoUzytkownika = logowanie(zarejestrowniUzytkownicy);
        break;
    case '2':
        rejestracja(zarejestrowniUzytkownicy);
        break;
    case '3':
        system("CLS");
        cout << "Dziekujemy za skorzystanie z ksiazki adresowej ! Do zobaczenia !" << endl;
        exit(0);
        break;
    }

    return idZalogowanegoUzytkownika;
}

int ostatniNrIdAdresata(vector <DaneAdresata> adresaci) {

    vector <DaneAdresata> :: iterator it;
    int ostatniNrIdAdresata = 0;

    for(it = adresaci.begin() ; it != adresaci.end() ; ++it)
        ostatniNrIdAdresata = (*it).numerIdAdresata;

    return ostatniNrIdAdresata;
}

int dodajAdresata(vector <DaneAdresata> &adresaci, int idZalogowanegoUzytkownika, int ostatniAdresat) {
    system("CLS");
    DaneAdresata adresat;
    fstream plikAdresaci;
    plikAdresaci.open("wspolnaAdresacja.txt", ios::out | ios::app);

    cout << "Podaj imie nowego Uzytkownika : " << endl;
    adresat.imie = pobierzLinie();

    cout << "Podaj nazwisko nowego Uzytkownika : " << endl;
    adresat.nazwisko = pobierzLinie();

    cout << "Podaj nr Tel nowego Uzytkownika : " << endl;
    adresat.nrTel = pobierzLinie();

    cout << "Podaj adres Email nowego Uzytkownika : " << endl;
    adresat.adresEmail = pobierzLinie();

    cout << "Podaj adres zamieszkania nowego Uzytkownika : " << endl;
    adresat.korespondecja = pobierzLinie();
    adresat.numerIdAdresata = ostatniAdresat + 1;

    adresaci.push_back(adresat);
    system("CLS");
    cout << "Adresat zostal dodany pomyslnie !" << endl;
    Sleep(1500);

    plikAdresaci << adresat.numerIdAdresata << "|" << idZalogowanegoUzytkownika << "|" << adresat.imie << "|" << adresat.nazwisko << "|" << adresat.nrTel << "|" <<  adresat.adresEmail << "|" << adresat.korespondecja<< "|" << endl;
    return adresat.numerIdAdresata;
}


void wyszukajAdresatowPoImieniu(vector <DaneAdresata> adresaci) {
    system("CLS");
    string szukaneImie;
    vector <DaneAdresata> :: iterator it;
    bool wystapienieDaneAdresataj = false;

    cout << "Podaj Imie ktore chcesz wyszukac :" << endl;
    cin >> szukaneImie;
    system("CLS");

    for( it = adresaci.begin() ; it != adresaci.end() ; ++it) {

        if((*it).imie == szukaneImie) {
            wystapienieDaneAdresataj = true;
            cout << "Id: " << (*it).numerIdAdresata << endl;
            cout << "Imie: " << (*it).imie << endl;
            cout << "Nazwisko: " << (*it).nazwisko << endl;
            cout << "Nr Tel: " << (*it).nrTel << endl;
            cout << "Adres Email: " << (*it).adresEmail << endl;
            cout << "Adres Zam: " << (*it).korespondecja << endl;
            cout << endl;
        }
    }
    if(wystapienieDaneAdresataj == false) {
        system("CLS");
        cout << "Niestety nie ma uzytkownika o takim imieniu !!" << endl;
    }

    system("PAUSE");
}

void wyswietlWszystkichAdresatow(vector <DaneAdresata> &adresaci) {

    system("CLS");
    vector <DaneAdresata> :: iterator it;
    int powtorzeniaZmiennej = 0;
    if(adresaci.begin() < adresaci.end()) {
        for( it = adresaci.begin() ; it != adresaci.end() ; ++it) {

            if(powtorzeniaZmiennej != (*it).numerIdAdresata) {

                cout << endl;
                cout << "Id: " << (*it).numerIdAdresata << endl;
                cout << "Imie: " << (*it).imie << endl;
                cout << "Nazwisko: " << (*it).nazwisko << endl;
                cout << "Nr Tel: " << (*it).nrTel << endl;
                cout << "Adres Email: " << (*it).adresEmail << endl;
                cout << "Adres Zam: " << (*it).korespondecja << endl;
                powtorzeniaZmiennej = (*it).numerIdAdresata;
            } else {

            }
        }
        cout << endl;
    } else
        cout << "Brak uzytkownikow w ksiazce adresowej !!" << endl;
    system("PAUSE");
}

void wyszukajAdresataPoNazwisku(vector <DaneAdresata> adresaci) {

    system("CLS");
    string szukaneNazwisko;
    vector <DaneAdresata> :: iterator it;
    bool wystapienieDaneAdresataj = false;

    cout << "Podaj Nazwisko ktore chcesz wyszukac :" << endl;
    cin >> szukaneNazwisko;
    system("CLS");

    for( it = adresaci.begin() ; it != adresaci.end() ; ++it) {

        if((*it).nazwisko == szukaneNazwisko) {
            wystapienieDaneAdresataj = true;
            cout << "Id: " << (*it).numerIdAdresata << endl;
            cout << "Imie: " << (*it).imie << endl;
            cout << "Nazwisko: " << (*it).nazwisko << endl;
            cout << "Nr Tel: " << (*it).nrTel << endl;
            cout << "Adres Email: " << (*it).adresEmail << endl;
            cout << "Adres Zam: " << (*it).korespondecja << endl;
            cout << endl;
        }
    }
    if(wystapienieDaneAdresataj == false) {
        system("CLS");
        cout << "Niestety nie ma uzytkownika o takim nazwisku !!" << endl;
    }
    system("PAUSE");
}

int zaladowaniePlikuAdresaci(vector <DaneAdresata> &adresaci, int idZalogowanegoUzytkownika) {
    DaneAdresata adresat;
    int nr_linii = 1;
    string linia;
    string zmiennaPomocnicza = "";
    fstream plikAdresaci;
    int ostatniAdresat = 0;

    plikAdresaci.open("wspolnaAdresacja.txt", ios::in);
    if(plikAdresaci.good() == false) {
        cout << "Brak adresatow w ksiazce telefonicznej !!" << endl;
        system("PAUSE");
        system("CLS");
    } else {
        while(getline(plikAdresaci,linia)) {
            for (unsigned int i = 0 ; i < linia.length(); i++) {

                if (linia[i] != '|') {
                    zmiennaPomocnicza += linia[i];
                } else {
                    switch(nr_linii) {
                    case 1:
                        adresat.numerIdAdresata = atoi(zmiennaPomocnicza.c_str());
                        ostatniAdresat = adresat.numerIdAdresata;
                        break;
                    case 2:
                        adresat.idUzytkownika = atoi(zmiennaPomocnicza.c_str());
                        break;
                    case 3:
                        adresat.imie = zmiennaPomocnicza;
                        break;
                    case 4:
                        adresat.nazwisko = zmiennaPomocnicza;
                        break;
                    case 5:
                        adresat.nrTel = zmiennaPomocnicza;
                        break;
                    case 6:
                        adresat.adresEmail = zmiennaPomocnicza;
                        break;
                    case 7:
                        adresat.korespondecja = zmiennaPomocnicza;
                        break;
                    }
                    zmiennaPomocnicza = "";
                    nr_linii++;
                }
                if(nr_linii == 8) {
                    nr_linii = 1;
                }
            }
            if(adresat.idUzytkownika == idZalogowanegoUzytkownika)
                adresaci.push_back(adresat);
        }
    }
    plikAdresaci.close();

    return ostatniAdresat;
}

void zmienHaslo(vector <DaneUzytkownika> &zarejestrowniUzytkownicy, int idZalogowanegoUzytkownika) {

    vector <DaneUzytkownika> :: iterator it;
    string noweHaslo = "";
    string powtorzHaslo = "";
    cout << "Podaj nowe haslo : " << endl;
    cin >> noweHaslo;

    cout << "Powtorz haslo : " << endl;
    cin >> powtorzHaslo;

    if(noweHaslo == powtorzHaslo) {
        for (it = zarejestrowniUzytkownicy.begin() ; it != zarejestrowniUzytkownicy.end() ; ++it) {
            if(idZalogowanegoUzytkownika == (*it).numerIdUzytkownika)  {
                (*it).haslo = noweHaslo;
                cout << "Haslo zostalo zmienione pomyslnie !" << endl;
                remove("ListaUzytkownikow.txt");
                dodajUzytkownikaDoPliku(zarejestrowniUzytkownicy);
                zaladujPlikUzytkownicy(zarejestrowniUzytkownicy);
                Sleep(1000);
                return;
            }
        }
    } else {
        cout << "Hasla roznia sie !" << endl;
    }
    Sleep(2000);
}

bool czyUsunacAdresata() {

    bool potwierdzenie = false;
    string wybor;

    cout << "Czy na pewno usunac uzytkownika? y/n" << endl;

    cin >> wybor;
    system("CLS");

    if(wybor == "y") {
        potwierdzenie = true;
        cout << "Uzytkownik zostal usuniety !" << endl;
    } else if (wybor == "n") {
        potwierdzenie = false;
        cout << "Uzytkownik nie zostal usuniety !" << endl;
    }
    Sleep(2000);

    return potwierdzenie;
}

void zapisanieZmianPoUsunieciuDoPliku(int idUsunietego) {
    DaneAdresata adresat;
    int nr_linii = 1;
    string linia;
    string zmiennaPomocnicza = "";
    fstream plikAdresaci;
    fstream plikAdresaciTymczasowi;
    vector <DaneAdresata> :: iterator it;

    plikAdresaci.open("wspolnaAdresacja.txt", ios::in);
    plikAdresaciTymczasowi.open("wspolnaAdresacjaTymczasowa.txt", ios::out);

    while(getline(plikAdresaci,linia)) {
        for (unsigned int i = 0 ; i < linia.length(); i++) {

            if (linia[i] != '|') {
                zmiennaPomocnicza += linia[i];
                cout << zmiennaPomocnicza << endl;
            } else {
                switch(nr_linii) {
                case 1:
                    adresat.numerIdAdresata = atoi(zmiennaPomocnicza.c_str());
                    break;
                case 2:
                    adresat.idUzytkownika = atoi(zmiennaPomocnicza.c_str());
                    break;
                case 3:
                    adresat.imie = zmiennaPomocnicza;
                    break;
                case 4:
                    adresat.nazwisko = zmiennaPomocnicza;
                    break;
                case 5:
                    adresat.nrTel = zmiennaPomocnicza;
                    break;
                case 6:
                    adresat.adresEmail = zmiennaPomocnicza;
                    break;
                case 7:
                    adresat.korespondecja = zmiennaPomocnicza;
                    break;
                }
                zmiennaPomocnicza = "";
                nr_linii++;
            }
            if(nr_linii == 8) {
                nr_linii = 1;
            }
        }

        if(adresat.numerIdAdresata != idUsunietego)
            plikAdresaciTymczasowi << adresat.numerIdAdresata << "|" << adresat.idUzytkownika << "|" << adresat.imie << "|" << adresat.nazwisko << "|" << adresat.nrTel << "|" << adresat.adresEmail << "|" << adresat.korespondecja << "|" << endl;
        else
            continue;
    }

    plikAdresaci.close();
    plikAdresaciTymczasowi.close();

    remove("wspolnaAdresacja.txt");
    rename("wspolnaAdresacjaTymczasowa.txt", "wspolnaAdresacja.txt");

}

void usunAdresata(vector <DaneAdresata> &adresaci) {

    vector <DaneAdresata> :: iterator it;
    int idAdresata = 0;
    cout << "Podaj numer ID Adresata, ktorego chcesz usunac : ";
    cin >> idAdresata;

    for(it = adresaci.begin() ; it != adresaci.end() ; ++it) {
        if((*it).numerIdAdresata == idAdresata) {
            if(czyUsunacAdresata()) {
                adresaci.erase(it);
                zapisanieZmianPoUsunieciuDoPliku(idAdresata);
                return;
            }
        }
    }
    system("CLS");
    cout << "Brak Adresata o takim numerze ID" << endl;
    Sleep(2000);
}

void zapisanieZmianPoEdycjiDoPliku(vector <DaneAdresata> &adresaci, int idEdytowanegoAdresata) {
    DaneAdresata adresat;
    int nr_linii = 1;
    string linia;
    string zmiennaPomocnicza = "";
    fstream plikAdresaci;
    fstream plikAdresaciTymczasowi;
    vector <DaneAdresata> :: iterator it;

    plikAdresaci.open("wspolnaAdresacja.txt", ios::in);
    plikAdresaciTymczasowi.open("wspolnaAdresacjaTymczasowa.txt", ios::out);

    while(getline(plikAdresaci,linia)) {
        for (unsigned int i = 0 ; i < linia.length(); i++) {

            if (linia[i] != '|') {
                zmiennaPomocnicza += linia[i];
            } else {
                switch(nr_linii) {
                case 1:
                    adresat.numerIdAdresata = atoi(zmiennaPomocnicza.c_str());
                    break;
                case 2:
                    adresat.idUzytkownika = atoi(zmiennaPomocnicza.c_str());
                    break;
                case 3:
                    adresat.imie = zmiennaPomocnicza;
                    break;
                case 4:
                    adresat.nazwisko = zmiennaPomocnicza;
                    break;
                case 5:
                    adresat.nrTel = zmiennaPomocnicza;
                    break;
                case 6:
                    adresat.adresEmail = zmiennaPomocnicza;
                    break;
                case 7:
                    adresat.korespondecja = zmiennaPomocnicza;
                    break;
                }
                zmiennaPomocnicza = "";
                nr_linii++;
            }
            if(nr_linii == 8) {
                nr_linii = 1;
            }
        }

        if(adresat.numerIdAdresata != idEdytowanegoAdresata)
            plikAdresaciTymczasowi << adresat.numerIdAdresata << "|" << adresat.idUzytkownika << "|" << adresat.imie << "|" << adresat.nazwisko << "|" << adresat.nrTel << "|" << adresat.adresEmail << "|" << adresat.korespondecja << "|" << endl;
        else {
            for( it = adresaci.begin() ; it != adresaci.end() ; ++it) {
                if((*it).numerIdAdresata  == idEdytowanegoAdresata) {
                    plikAdresaciTymczasowi << (*it).numerIdAdresata << "|" << adresat.idUzytkownika << "|" << (*it).imie << "|" << (*it).nazwisko << "|" << (*it).nrTel << "|" << (*it).adresEmail << "|" << (*it).korespondecja << "|" << endl;
                }
            }
        }
    }
    plikAdresaci.close();
    plikAdresaciTymczasowi.close();

    remove("wspolnaAdresacja.txt");
    rename("wspolnaAdresacjaTymczasowa.txt", "wspolnaAdresacja.txt");

}

void edytujAdresata(vector <DaneAdresata> &adresaci) {

    char wybor;
    int id;
    bool wystapienieDaneAdresataj = false;
    vector <DaneAdresata> :: iterator it;

    system("CLS");

    cout << "Podaj nr ID uzytkownika ktorego chcesz edytowac : " << endl;
    cin >>id;

    for( it = adresaci.begin() ; it != adresaci.end() ; ++it) {

        if((*it).numerIdAdresata  == id) {

            wystapienieDaneAdresataj = true;
            cout << "Id: " << (*it).numerIdAdresata << endl;
            cout << "Imie: " << (*it).imie << endl;
            cout << "Nazwisko: " << (*it).nazwisko << endl;
            cout << "Nr Tel: " << (*it).nrTel << endl;
            cout << "Adres Email: " << (*it).adresEmail << endl;
            cout << "Adres Zam: " << (*it).korespondecja << endl;
            cout << endl;

            cout << "Ktory wariant chcialbys edytowac? " << endl;

            cout << " 1 - Imie" << endl;
            cout << " 2 - Nazwisko" << endl;
            cout << " 3 - Nr Tel" << endl;
            cout << " 4 - Adres Email" << endl;
            cout << " 5 - Adres Zam" << endl;

            wybor = getch();
            system("CLS");

            if(wybor < '6' ) {
                switch(wybor) {
                case '1' :
                    cout << "Podaj Imie:" << endl;
                    (*it).imie = pobierzLinie();
                    break;
                case '2' :
                    cout << "Podaj Nazwisko:" << endl;
                    (*it).nazwisko = pobierzLinie();
                    break;
                case '3' :
                    cout << "Podaj Nr Tel:" << endl;
                    (*it).nrTel = pobierzLinie();
                    break;
                case '4' :
                    cout << "Podaj Adres Email:" << endl;
                    (*it).adresEmail = pobierzLinie();
                    break;
                case '5' :
                    cout << "Podaj Adres Zamieszkania:" << endl;
                    (*it).korespondecja = pobierzLinie();
                    break;
                }

                system("CLS");
                cout << "Dane Adresata zostaly poprawnie zmienione !!" << endl;
                zapisanieZmianPoEdycjiDoPliku(adresaci, id);
            } else
                cout << "Nie ma takiej opcji !!" << endl;
        }
    }
    if(wystapienieDaneAdresataj == false) {
        system("CLS");
        cout << "Podany numer ID nie istnieje!!" << endl;
    }
    system("PAUSE");
    }


    int wyloguj(vector <DaneAdresata> &adresaci) {
        adresaci.clear();
        return 0;
    }

int main() {
    vector <DaneUzytkownika> zarejestrowniUzytkownicy;
    vector <DaneAdresata> adresaci;
    char wyborOpcji;
    int idZalogowanegoUzytkownika = 0;
    int ostatniAdresat = 0;
    for(;;) {
        do {
            zaladujPlikUzytkownicy(zarejestrowniUzytkownicy);
            idZalogowanegoUzytkownika = panelPowitalny(zarejestrowniUzytkownicy);
        } while(idZalogowanegoUzytkownika == 0);
        ostatniAdresat = zaladowaniePlikuAdresaci(adresaci,idZalogowanegoUzytkownika);
        while(idZalogowanegoUzytkownika != 0) {
            cout << "Witaj w ksiazce Adresowej !" << endl;

            cout << "1 - Dodaj nowego Uzytkownika" << endl;
            cout << "2 - Wyszukaj po Imieniu" << endl;
            cout << "3 - Wyszukaj po Nazwisku" << endl;
            cout << "4 - Wyswietl wszystkie osoby" << endl;
            cout << "5 - Usun adresata" << endl;
            cout << "6 - Edytuj adresata" << endl;
            cout << "7 - Zmien Haslo" << endl;
            cout << "8 - Wyloguj sie" << endl;
            cout << "9 - Opusc program" << endl;

            wyborOpcji = getch();
            adresaci.size();
            switch(wyborOpcji) {
            case '1' :
                ostatniAdresat = dodajAdresata(adresaci, idZalogowanegoUzytkownika, ostatniAdresat);
                break;
            case '2' :
                wyszukajAdresatowPoImieniu(adresaci);
                break;
            case '3' :
                wyszukajAdresataPoNazwisku(adresaci);
                break;
            case '4' :
                wyswietlWszystkichAdresatow(adresaci);
                break;
            case '5' :
                usunAdresata(adresaci);
                break;
            case '6' :
                edytujAdresata(adresaci);
                break;
            case '7' :
                zmienHaslo(zarejestrowniUzytkownicy, idZalogowanegoUzytkownika);
                break;
            case '8' :
                idZalogowanegoUzytkownika = wyloguj(adresaci);
                break;
            case '9' :
                exit(0);
                break;
            }
            system("CLS");
        }
    }
    return 0;
}
