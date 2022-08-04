
#include <iostream>
#include <vector>
#include <conio.h>
#include <algorithm>
#include <fstream>
#include <windows.h>
#define DATA 10

using namespace std;
struct pacjent{
    string imie;
    string nazwisko;
    string pesel;
    string pantomogram;
    string data;
    string powod;
    int koszt;
    };
void menu2();
vector <pacjent> tab;
vector <pacjent> tab2;

string pobierz_tekst(string pytanie){
    string napis;
    do{
        cout<<pytanie;
        cin>>napis;
    }while (napis==" ");
    return napis;
}
string pobierz_pesel(string pytanie, vector<pacjent> t)
{
    string napis;
    int ret;
    do{
        cout<<pytanie;
        cin>>napis;
        ret=1;
        for(int i=0;i<t.size();i++)
            if(t[i].pesel==napis)
        {
            ret=0;
            cout<<"Pesel znajduje sie w bazie pacjentow. Podaj jeszcze raz"<<endl;
            break;
        }
         if(napis.length() != 11)
        {
            ret = 0;
            cout<<"Niepoprawna ilosc cyfr w peselu. Podaj jeszcze raz (PESEL = 11 ZNAKOW)"<<endl;
            continue;
        }
    }while(napis==" "||ret==0);
    return napis;
}

string pobierz_date(string pytanie)
{
    string napis, tmp;
    int ret;
    do
    {
        ret = 1;
        napis = pobierz_tekst(pytanie);
        if (napis.length() != DATA)
        {
            cout << "Podaj poprawny format daty (XX.XX.XXXX)" << endl;
            ret = 0;
            continue;
        }
    }
    while (ret == 0);
    return napis;
}
int pobierz_kwota(string pytanie)
{
    int napis;


        cout << pytanie;
        cin >> napis;

    return napis;
}


pacjent dodaj(){
    pacjent st;
    st.imie=pobierz_tekst("Imie: ");
    st.nazwisko=pobierz_tekst("Nazwisko: ");
    st.pantomogram=pobierz_tekst("Pantomogram: ");
    st.pesel=pobierz_pesel("Pesel: ",tab);
    st.data=pobierz_date("Data: ");
    st.powod=pobierz_tekst("Powod: ");
    st.koszt=pobierz_kwota("Koszt leczenia: ");
    return st;
    }


void wyswietl(pacjent st)
{

    cout<<"-"<<"Imie: "<<st.imie<<" / Nazwisko: "<<st.nazwisko<<" / Pesel:"<<st.pesel<<" / Czy byl wykonywany pantomogram: "<<st.pantomogram<<" / Data ostatniej wizyty: "<<st.data<<" /Powod ostatniej wizyty: "<<st.powod<<endl<<" Calkowity koszt leczenia: "<<st.koszt << " zl"<<endl;
}

void wyswietl_2(pacjent st)
{
    cout<<"Imie: "<<st.imie<<" / Nazwisko: "<<st.nazwisko<<" / Pesel:"<<st.pesel<<" / Czy byl wykonywany pantomogram: "<<st.pantomogram<<endl;
}

void wyswietl_3(pacjent st)
{
    cout<<"Kwota przed zmiana: "<< st.koszt<< " zl"<<endl;
}

int wyszukaj(vector<pacjent>t,string pesel, int &ret)
{
    ret=0;
    for(int i=0;i<tab.size();i++)
        if(t[i].pesel==pesel)
    {
        ret=1;
        return i;
    }
    return NULL;
}


vector <string> splitString(string linia, string sep)
{
    vector <string> result;
    sep=' ';
    string wyraz = "";
    string znak;
    linia = linia+sep;
    for(int i=0;i<linia.length();i++)
    {
        znak = linia[i];
        if(znak==sep)
        {
            result.push_back(wyraz);
            wyraz = "";
            continue;
        }
        wyraz = wyraz+znak;
    }
    return result;
}

vector <pacjent> odczyt_pliku(string baza)
{
    fstream plik;
    vector <pacjent> tab;
    pacjent st;
    string linia, imie, nazwisko, pesel,pantomogram, data, powod;
  string koszt;
    vector <string> v1;

 plik.open(baza.c_str(), ios::in);
    if (plik.good()==true)
    {
        while (getline(plik, linia))
        {
           v1=splitString(linia," ");
            if(v1.size() >= 6)
        {
           imie=v1[0];
           nazwisko=v1[1];
           pesel=v1[2];
           pantomogram=v1[3];
           data=v1[4];
           powod=v1[5];
           koszt=v1[6];
           st.imie=imie;
          st.nazwisko=nazwisko;
          st.pesel=pesel;
          st.pantomogram=pantomogram;
          st.data=data;
          st.powod=powod;
          st.koszt=atof(koszt.c_str());
          tab.push_back(st);
        }
        else cout<<"Program napotkal blad odczytu"<<endl;
    }

        plik.close();
        }

    else cout<<"Brak dostepu do pliku!!!"<<endl;
    return tab;
}

void zapis_pliku(vector <pacjent> tab, string baza)
{
    fstream plik;
    plik.open(baza.c_str(), ios::out);
    if (plik.good()==true)
    {
        for (int i=0;i<tab.size();i++)
        {
            plik<<tab[i].imie<<" "<<tab[i].nazwisko<<" "<<tab[i].pesel<<" "<<tab[i].pantomogram<<" "<<tab[i].data<<" "<<tab[i].powod<<" "<<tab[i].koszt<<endl;
        }
        plik.close();
    }
    else cout<<"Brak dostepu do pliku!!!"<<endl;
}
vector <pacjent> szukaj_pant(vector <pacjent> t)
{
    string znak;
    vector <pacjent> lista_pant;
    for (int i=0;i<t.size();i++)
    {
        znak=tab[i].pantomogram;
        if (znak=="+") lista_pant.push_back(t[i]);
    }
    return lista_pant;
}
int wyszukaj_data(vector<pacjent>t,string pesel, int &ret)
{
    ret=0;
    for(int i=0;i<tab.size();i++)
        if(t[i].pesel==pesel)
    {
        ret=1;
        return i;
    }
    return NULL;
}


void menu(void)
{
    int klawisz,ind,ink,ret=0;
    string pantomogram;
    string pesel;
    string data;
    pacjent st;

    do{
        system("cls");
        cout<<"        MENU    "<<endl;
        cout<<"------------------"<<endl;
        cout<<"Wybierz klawisz"<<endl;
        cout<<"1 Dodaj pacjenta"<<endl;
        cout<<"2 Wyswietl baze pacjentow"<<endl;
        cout<<"3 Wyszukaj pacjenta"<<endl;
        cout<<"4 Lista osob, u ktorych wykonywany byl pantomogram"<<endl;
        cout<<"5 Zmien date ostatniej wizyty"<<endl;
        cout<<"6 Zmien calkowity koszt leczenia"<<endl;
        cout<<"7 Zamkniecie bazy danych"<<endl;
        cout<<"Wybrales polecenie nr: ";
        cin>>klawisz;
        switch (klawisz)
        {
        case 1: cout<<" Dodaj pacjenta"<<endl;
            st=dodaj();
            tab.push_back(st);
            cout<<"--------------------------"<<endl;
            cout<<"Dodano pacjenta do bazy!"<<endl;
            getch();break;

        case 2: cout<<"Wyswietlanie danych pacjenta"<<endl;
            for(int i=0;i<tab.size();i++) wyswietl(tab[i]);
            getch();break;

        case 3: cout<<"Wyszukanie danych pacjenta"<<endl;
            cout<<"Podaj pesel do wyszukania: ";
            cin>>pesel;
            ind = wyszukaj(tab,pesel,ret);
            if(ret==0) cout<<"Brak pacjenta w bazie"<<endl;
            else wyswietl(tab[ind]);
            cout<<"Nacisnij dowolny klawisz"<<endl;
            getch();break;

         case 4: cout<<"Lista osob z pantomogramem:"<<endl;
            tab2=szukaj_pant(tab);
            for (int i=0;i<tab2.size();i++)
            wyswietl_2(tab2[i]);
            getch();break;

        case 5: cout<<"Zmiana daty ostatniej wizyty"<<endl;
            cout<<"Podaj pesel osoby, u ktorej chcesz zmienic date: ";
            cin>>pesel;
            ink = wyszukaj_data(tab,pesel,ret);
            if(ret==0) cout<<"Brak pacjenta w bazie"<<endl;
            else wyswietl(tab[ink]);
            data=pobierz_date("Aktualna data ostatniej wizyty: ");
            tab[ink].data=data;
            cout<<"Data ostatniej wizyty zostala zmieniona!"<<endl;
            zapis_pliku(tab,"baza.txt");
            getch();break;
        case 6:
         menu2();
        getch();break;
        case 7:zapis_pliku(tab,"baza.txt");
                    break;
           default:  break;


        }
    }while(klawisz!=7);

}
void menu2 (void)
{
 int klawisz2,ind,ret;
 string pesel;
 int koszt, kwota_niestandardowa,kwota_niestandardowa2 ;


do
{
    system("cls");

            string pesel;
            cout<<"MENU ZMIANY CALKOWITEGO KOSZTU WIZYTY"<<endl;
            cout<<"-------------------------------------"<<endl;
            cout<<"1 Dodaj koszt wykonania pantomogramu"<<endl;
            cout<<"2 Dodaj koszt wizyty kontrolnej"<<endl;
            cout<<"3 Dodaj kwote niestandardowa"<<endl;
            cout<<"4 Odejmij wpisana kwote"<<endl;
            cout<<"5 Wroc do MENU GLOWNEGO"<<endl;
            cout<<"--------------------------------------"<<endl;
            cout<<"Wybierz polecenie: "<<endl;
            cin>>klawisz2;
            switch(klawisz2)
            {
            case 1:
                cout<<"Podaj pesel osoby, u ktorej chcesz dokonac zmian: ";
                cin>>pesel;
                ind = wyszukaj(tab,pesel,ret);
                if(ret==0) cout<<"Brak pacjenta w bazie"<<endl;
                else wyswietl_3(tab[ind]);
                koszt=tab[ind].koszt;
                koszt+=150;
                tab[ind].koszt=koszt;
                zapis_pliku(tab,"baza.txt");
                cout<<"Kwota po dodaniu kosztu wykonania pontomogramu: "<< koszt<< " zl"<<endl;
                getch();break;

            case 2: cout<<"Podaj pesel osoby, u ktorej chcesz dokonac zmian: ";
                cin>>pesel;
                ind = wyszukaj(tab,pesel,ret);
                if(ret==0) cout<<"Brak pacjenta w bazie"<<endl;
                else wyswietl_3(tab[ind]);
                koszt=tab[ind].koszt;
                koszt+=100;
                tab[ind].koszt=koszt;
                zapis_pliku(tab,"baza.txt");
                cout<<"Kwota po dodaniu kosztu wizyty kontrolnej: "<< koszt<< " zl"<<endl;
                getch();break;


            case 3:
                cout<<"Podaj pesel osoby, u ktorej chcesz dokonac zmian: ";
                cin>>pesel;
                ind = wyszukaj(tab,pesel,ret);
                if(ret==0) cout<<"Brak pacjenta w bazie"<<endl;
                else wyswietl_3(tab[ind]);
                koszt=tab[ind].koszt;
                cout<<"Podaj wartosc kwoty niestandardowej: ";
                cin>>kwota_niestandardowa;
                koszt+=kwota_niestandardowa;
                tab[ind].koszt=koszt;
                zapis_pliku(tab,"baza.txt");
                cout<<"Kwota po dodaniu wpisanej wartosci: "<< koszt<< " zl"<<endl;
                getch();break;
            case 4:
                cout<<"Podaj pesel osoby, u ktorej chcesz dokonac zmian: ";
                cin>>pesel;
                ind = wyszukaj(tab,pesel,ret);
                if(ret==0) cout<<"Brak pacjenta w bazie"<<endl;
                else wyswietl_3(tab[ind]);
                koszt=tab[ind].koszt;
                cout<<"Podaj wartosc kwoty, ktora chcesz odjac: ";
                cin>>kwota_niestandardowa2;
                koszt-=kwota_niestandardowa2;
                tab[ind].koszt=koszt;
                zapis_pliku(tab,"baza.txt");
                cout<<"Kwota po odjeciu wpisanej wartosci: "<< koszt<< " zl"<<endl;
                getch();break;
            case 5:default:break;
            }
            }while(klawisz2!=5);

}


int main()
{
    tab = odczyt_pliku("baza.txt");
    menu();
    return 0;
}


