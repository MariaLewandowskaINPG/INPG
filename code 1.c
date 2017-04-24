/*Przy pomocy struktur zaimplementować prostą 'bazę danych', przechowywaną tylko w pamięci komputera w postaci
tablicy struktur. 'Baza danych' ma stanowić prostą książkę telefoniczną (Imię, Nazwisko jako napisy, Numer
telefonu jako liczba typu long). Program musi pozwalać (poprzez funkcje) na dodanie, usunięcie i przeglądanie
wpisów. Dane powinny być przechowywane w tablicy dynamicznej. Należy napisać funkcje:
- dodającą do tablicy jeden rekord bazy (czyli powiększającą tablicę o jeden element - można wzorować się na
zadaniu "Powiększanie tablicy" z tematu "Dynamiczna alokacja pamięci"),
- wyszukującą w bazie (tablicy) rekord o podanym polu Numer (zwracającą indeks znalezionego rekordu lub -1)
- wypisującą element tablicy - tu proszę, aby funkcja otrzymywała adres (wskaźnik) wypisywanego elementu.
- oraz nadobowiązkowo funkcję usuwającą rekord o podanym indeksie tablicy (np. zwróconym przez funkcję
   wyszukującą) poprzez realokację tablicy (przy przepisywaniu należy pominąć rekord o podanym indeksie).
W programie proszę nie używać zmiennych globalnych. W wersji nadobowiązkowej pisane funkcje jako parametry
powinny otrzymywać nie struktury tylko adresy struktur.
*/
#include <stdio.h>
#include <stdlib.h>
#define SIZE 20

struct phonebook{
    char firstName[SIZE];
    char surname[SIZE];
    long number;
};

void newRecord(struct phonebook** , int);
int search(struct phonebook**, int);
void putRecord(struct phonebook*);
void allRecords(struct phonebook**, int);
void deleteRecord(struct phonebook**, int, int);

int main(void){
    int index, activity, size = 0;
    struct phonebook *database = NULL;
    for(;;system("cls")){                                                                           //Dla Linuxa: system("clear");
        printf("\nPHONEBOOK\n\n1. Add new record.\n2. Search by number.\n3. Put all numbers.\n"
               "4. Delete a record.\nTo complete enter any letter.\n\nChoose your activity:\n");
        if(scanf("%d", &activity) == 0){
            free(database);
            database = NULL;
            return -1;
        }
        switch (activity){
            case 1:
                newRecord(&database, size++);
                break;
            case 2:
                index = search(&database, size);
                if (index != -1){
                    putRecord(database + index);
                }
                break;
            case 3:
                allRecords(&database, size);
                break;
            case 4:
                index = search(&database, size);
                if (index != -1)
                    deleteRecord(&database, size--, index);
                break;
            default:
                printf("\nIncorrect character. Try one more time.\n");
                getch();
                continue;
        }
    }
    free(database);
    database = NULL;
    return 0;
}

void newRecord(struct phonebook **ptab, int n){
    int i;
    struct phonebook newRecord_elem, *tmp;
    printf("\nAdd a new record.\nEnter first name: ");
    scanf("%s" , newRecord_elem.firstName);
    printf("Enter surname: ");
    scanf("%s" , newRecord_elem.surname);
    printf("Enter phone number: ");
    scanf("%ld" , &newRecord_elem.number);

    tmp = (struct phonebook*) malloc((n+1) * sizeof(struct phonebook));
    if (tmp == NULL)
        return;
    if (*ptab != NULL)
        for(i=0; i<n; i++)
            tmp[i] = (*ptab)[i];
    tmp[n] = newRecord_elem;
    free(*ptab);
    *ptab = tmp;
    printf("\nNew record has been added. Press any key to continue.");
    getch();
    return;
}

int search(struct phonebook **ptab, int n){
    int i, index = -1;
    long nr;
    printf("\nWhat number do you want to search for? ");
    scanf("%ld", &nr);
    for(i=0; i<n; i++)
        if ((*ptab)[i].number == nr){
            index = i;
            break;
        }
    if (index == -1){
        printf("\nCannot find the owner of %ld number.\nPress any key to continue.", nr);
        getch();
    }
    return index;
}

void putRecord(struct phonebook* ptab){
    printf("\n%s %s %ld\n",ptab->firstName, ptab->surname, ptab->number);
    printf("\nPress any key to continue.");
    getch();
    return;
}

void allRecords(struct phonebook **ptab, int n){
    int i;
    printf("\n\nPHONEBOOK:\n\n Lp. | %20s | %20s | %10s\n", "First Name", "Surname", "Number");
    for(i=0; i<n; i++)
        printf("%3d. | %20s | %20s | %10ld\n",i, (*ptab)[i].firstName, (*ptab)[i].surname, (*ptab)[i].number);
    printf("\nPress any key to continue.");
    getch();
    return;
}

void deleteRecord(struct phonebook **ptab, int n, int index){
    int i;
    struct phonebook* tmp = (struct phonebook*) malloc((n-1) * sizeof(struct phonebook));
    if (tmp == NULL)
        return;
    if (*ptab != NULL){
        for(i=0; i<index; i++)
            tmp[i] = (*ptab)[i];
        for(i = index; i<n-1; i++)
            tmp[i] = (*ptab)[i+1];
    }
    free(*ptab);
    *ptab = tmp;
    printf("\nRecord has been deleted. Press any key to continue.");
    getch();
    return;
}

