#include<stdio.h>
#include<iostream.h>
#include <math.h>
 
//W przypadku gdy szyfrowany tekst lub haslo posiadaja dlugosc > niz 200 znakow nalezy
//powiekszyc rozmiar tablic: tablica_ASCII, haslo.
void main()
{
FILE *we, *wy;
int i, licznik;
int tablica_ASCII[200]; //przechowywane beda w niej wartosci liter odpowiadajace poszczegolnym literom w hasle
char znak;   //znak odczytany z pliku
char haslo[200]; //tablica, w ktorej przechowywane bedzie haslo
//Przed uruchomieniem programu nalezy utworzyc 2 pliki - 1. z tekstem jawnym, 2. pusty na t.zaszyfrowany
char plik_jawny[20];  //nazwa pliku z tekstem jawnym
char plik_zaszyfrowany[20];  //nazwa pliku z tekstem zaszyfrownym
for (i=0; i<200; i++)    //wypelnienie tablicy pustymi znakami
haslo[i]=42;
 
cout<<"Podaj nazwe pliku, ktorego tresc ma zostac zaszyfrowana: " ;
cin>>plik_jawny;
cout<<"Podaj nazwe pliku wynikowego: ";
cin>>plik_zaszyfrowany;
cout<<"Podaj haslo tylko duze litery, bez spacji i znakow specjalnych: " ;
cin>>haslo;
 
int pozycja=0;
for (i=0; i<200; i++)
if (haslo[pozycja]!=42)
{
tablica_ASCII[i]=haslo[pozycja];      //wypelnienie tablicy_ASCII wartosciami
pozycja++;
}
else
{
pozycja=0;                           //gdy skonczy sie haslo nalezy wczytywac je znowu od poczatku
i--;
tablica_ASCII[i]=haslo[pozycja];
pozycja++;
}
 
for (i=0; i<200; i++)           //po odjeciu wartosci 64 w tablicy_ASCII mamy wartosci o, ktore rowne sa przesunieciu jakie musi byc wykonane
tablica_ASCII[i]-=65;
 
 
licznik=0;
 
if((we=fopen(plik_jawny,"rb"))!=NULL)    //otwieranie pliku 1. do odczytu - oba pliki musza istniec
{
if((wy=fopen(plik_zaszyfrowany,"wb"))!=NULL)  //otwieranie pliku 2. do zapisu
{
while((znak=getc(we))!=EOF)   //pobieranie znaku z pliku 1. tak dlugo az nie nastapi znak konca pliku
//Kazdy odczytywany znak wg kodow ASCII jest przydzielany do 2 grup duze litery, male litery
{
if ((znak>=65)&&(znak<=90))
{
znak-=65;
znak+=tablica_ASCII[licznik];    //przesuniecie w prawo zgodnie z litera hasla
if(licznik==200)  //w przypadkugdy tekst bedzie dluzszy niz 200 znakow nalezy pobierac znaki hasla od poczatku tablicy
licznik=0;   
else
licznik++;
znak=fmod(znak,26);
znak+=65;
putc(znak,wy);
}
else if ((znak>=97)&&(znak<=122))
{
znak-=97;
znak+=tablica_ASCII[licznik];
if(licznik==200)
licznik=0;
else
licznik++;
znak=fmod(znak,26);
znak+=97;
putc(znak,wy);
}
}
 
fclose(wy);
}
fclose(we);
}
cout<<"Szyfrowanie zostalo zakonczone";
return;
}